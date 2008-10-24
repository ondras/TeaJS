/* 
 * v8cgi main file. Based on V8's "shell" sample app
 */

#include <v8.h>
#include <system.h>
#include <io.h>
#include <jsmysql.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sstream>

v8::Handle<v8::Array> onexit;

v8::Handle<v8::String> ReadFile(const char* name) {
  FILE* file = fopen(name, "rb");
  if (file == NULL) return v8::Handle<v8::String>();

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  char* chars = new char[size + 1];
  chars[size] = '\0';
  for (int i = 0; i < size;) {
    int read = fread(&chars[i], 1, size - i, file);
    i += read;
  }
  fclose(file);

  /* remove shebang line */  
  std::string str = chars;
  if ( str.find('#',0) == 0 && str.find('!',1) == 1 ) {
    int pfix = str.find('\n',0);
    str.erase(0,pfix);
  };
  
  v8::Handle<v8::String> result = v8::String::New(str.c_str(), str.size());
  delete[] chars;
  return result;
}

void ReportException(v8::TryCatch* try_catch) {
  v8::HandleScope handle_scope;
  v8::String::Utf8Value exception(try_catch->Exception());
  v8::Handle<v8::Message> message = try_catch->Message();

  char * msg;
  std::string msgstring = "";

  if (message.IsEmpty()) {
    asprintf(&msg, "%s\n", *exception);
    msgstring += msg;
  } else {
    // Print (filename):(line number): (message).
    v8::String::Utf8Value filename(message->GetScriptResourceName());
    int linenum = message->GetLineNumber();
    asprintf(&msg, "%s:%i: %s\n", *filename, linenum, *exception);
    msgstring += msg;
    // Print line of source code.
    v8::String::Utf8Value sourceline(message->GetSourceLine());
    asprintf(&msg, "%s\n", *sourceline);
    msgstring += msg;

    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn();
    for (int i = 0; i < start; i++) {
      msgstring += " ";
    }
    int end = message->GetEndColumn();
    for (int i = start; i < end; i++) {
      msgstring += "^";
    }
    msgstring += "\n";
  }
  
  int cgi = 0;
  v8::Local<v8::Function> fun;
  v8::Local<v8::Value> context = v8::Context::GetCurrent()->Global()->Get(v8::String::New("response"));
  if (context->IsObject()) {
    v8::Local<v8::Value> print = context->ToObject()->Get(v8::String::New("error"));
    if (print->IsObject()) {
	fun = v8::Local<v8::Function>::Cast(print);
	cgi = 1;
    }
  }
  if (!cgi) {
    context = v8::Context::GetCurrent()->Global()->Get(v8::String::New("System"));
    fun = v8::Local<v8::Function>::Cast(context->ToObject()->Get(v8::String::New("stdout")));
  }
  
  v8::Handle<v8::Value> data[1];
  data[0] = v8::String::New(msgstring.c_str());
  fun->Call(context->ToObject(), 1, data);
}

bool ExecuteString(v8::Handle<v8::String> source, v8::Handle<v8::Value> name) {
  v8::HandleScope handle_scope;
  v8::TryCatch try_catch;
  v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
  if (script.IsEmpty()) {
    ReportException(&try_catch);
    return false;
  } else {
    v8::Handle<v8::Value> result = script->Run();
    if (result.IsEmpty()) {
      ReportException(&try_catch);
      return false;
    }
  }
  return true;
}

void die(int code) {
    int max = onexit->Length();
    v8::Handle<v8::Function> fun;
    for (int i=0;i<max;i++) {
	fun = v8::Handle<v8::Function>::Cast(onexit->Get(v8::Integer::New(i)));
	fun->Call(v8::Context::GetCurrent()->Global(), 0, NULL);
    }
    exit(code);
}

v8::Handle<v8::Value> _include(const v8::Arguments& args) {
  for (int i = 0; i < args.Length(); i++) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value file(args[i]);
    v8::Handle<v8::String> source = ReadFile(*file);
    if (source.IsEmpty()) {
      return v8::ThrowException(v8::String::New("Error loading file"));
    }
    
    if (!ExecuteString(source, v8::String::New(*file))) {
      return v8::ThrowException(v8::String::New("Error executing file"));
    }
  }
  return v8::Undefined();
}


v8::Handle<v8::Value> _exit(const v8::Arguments& args) {
  die(args[0]->Int32Value());
  return v8::Undefined();
}

v8::Handle<v8::Value> _onexit(const v8::Arguments& args) {
  onexit->Set(v8::Integer::New(onexit->Length()), args[0]);
  return v8::Undefined();
}


int main(int argc, char ** argv, char ** envp) {
  v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
  v8::HandleScope handle_scope;

  v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
  v8::Handle<v8::Context> context = v8::Context::New(NULL, global);
  v8::Context::Scope context_scope(context);

  onexit = v8::Array::New();
  context->Global()->Set(v8::String::New("include"), v8::FunctionTemplate::New(_include)->GetFunction());
  context->Global()->Set(v8::String::New("exit"), v8::FunctionTemplate::New(_exit)->GetFunction());
  context->Global()->Set(v8::String::New("onexit"), v8::FunctionTemplate::New(_onexit)->GetFunction());
  context->Global()->Set(v8::String::New("global"), context->Global());

  SetupSys(envp, context->Global());
  SetupIo(context->Global());  
  
  #ifdef HAVE_MYSQL
    SetupMysql(context->Global());  
  #endif
  
  if (argc == 1) {
    printf("Nothing to do.\n");
  } else {
    char* str = argv[1];
    v8::Handle<v8::String> name = v8::String::New(str);
    v8::Handle<v8::String> source = ReadFile(str);
    if (source.IsEmpty()) {
	printf("Error reading '%s'\n", str);
        die(1);
    }
    
    int result = ExecuteString(source, name);
    if (result) { die(result); }
  }
  die(0);
}
