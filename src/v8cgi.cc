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

void RunShell(v8::Handle<v8::Context> context);
bool ExecuteString(v8::Handle<v8::String> source,
                   v8::Handle<v8::Value> name,
                   bool print_result,
                   bool report_exceptions);
v8::Handle<v8::String> ReadFile(const char* name);
void ReportException(v8::TryCatch* handler);

v8::Handle<v8::Array> onexit;

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
    
    if (!ExecuteString(source, v8::String::New(*file), false, true)) {
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


void RunShell(v8::Handle<v8::Context> context) {
  static const int kBufferSize = 256;
  while (true) {
    char buffer[kBufferSize];
    printf("> ");
    char* str = fgets(buffer, kBufferSize, stdin);
    if (str == NULL) break;
    v8::HandleScope handle_scope;
    ExecuteString(v8::String::New(str),
                  v8::String::New("(shell)"),
                  true,
                  true);
  }
  printf("\n");
}

bool ExecuteString(v8::Handle<v8::String> source,
                   v8::Handle<v8::Value> name,
                   bool print_result,
                   bool report_exceptions) {
  v8::HandleScope handle_scope;
  v8::TryCatch try_catch;
  v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
  if (script.IsEmpty()) {
    // Print errors that happened during compilation.
    if (report_exceptions)
      ReportException(&try_catch);
    return false;
  } else {
    v8::Handle<v8::Value> result = script->Run();
    if (result.IsEmpty()) {
      // Print errors that happened during execution.
      if (report_exceptions)
        ReportException(&try_catch);
      return false;
    } else {
      if (print_result && !result->IsUndefined()) {
        // If all went well and the result wasn't undefined then print
        // the returned value.
        v8::String::Utf8Value str(result);
        printf("%s\n", *str);
      }
      return true;
    }
  }
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
    context = v8::Context::GetCurrent()->Global()->Get(v8::String::New("system"));
    fun = v8::Local<v8::Function>::Cast(context->ToObject()->Get(v8::String::New("stdout")));
  }
  
  v8::Handle<v8::Value> data[1];
  data[0] = v8::String::New(msgstring.c_str());
  fun->Call(context->ToObject(), 1, data);
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

  SetupSys(envp, context->Global());
  SetupIo(context->Global());  
  SetupMysql(context->Global());  

  bool run_shell = (argc == 1);
  for (int i = 1; i < argc; i++) {
    const char* str = argv[i];
    if (strcmp(str, "--shell") == 0) {
      run_shell = true;
    } else if (strcmp(str, "-f") == 0) {
      // Ignore any -f flags for compatibility with the other stand-
      // alone JavaScript engines.
      continue;
    } else if (strncmp(str, "--", 2) == 0) {
      printf("Warning: unknown flag %s.\n", str);
    } else {
      // Use all other arguments as names of files to load and run.
      v8::HandleScope handle_scope;
      v8::Handle<v8::String> file_name = v8::String::New(str);
      v8::Handle<v8::String> source = ReadFile(str);
      if (source.IsEmpty()) {
        printf("Error reading '%s'\n", str);
        die(1);
      }
      if (!ExecuteString(source, file_name, false, true))
        die(1);
    }
  }
  
  
  if (run_shell) RunShell(context);
  die(0);
}
