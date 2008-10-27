#include <v8.h>
#include <sstream>
#include <js_common.h>

v8::Handle<v8::Value> _stdin(const v8::Arguments&args) {
    v8::HandleScope handle_scope;
    
    size_t count = args[0]->Int32Value();
    char * data;
    if (count == 0) {
	data = (char *) malloc(sizeof(char));
	char * ch = (char *) malloc(sizeof(char));
	ch[0] = '\0';
	
	do {
	    count++;
	    fread(ch, sizeof(char), 1, stdin);
	    data = (char *) realloc(data, count+1);
	    data[count-1] = ch[0];
	    data[count] = '\0';
	} while (ch[0] != '\n');
    } else {
	data = (char *)  malloc(count + sizeof(char));
	fread(data,sizeof(char),count,stdin);
	data[count] = '\0';
    }
    if (args.Length() > 1 && args[1]->IsTrue()) {
	return char2array(data, count);
    } else {
	return char2string(data, count);
    }
}

v8::Handle<v8::Value> _stdout(const v8::Arguments&args) {
    v8::HandleScope handle_scope;
    if (args[0]->IsArray()) {
	v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
	uint32_t len = arr->Length();
	for (unsigned int i=0;i<len;i++) {
	    printf("%c", (char) arr->Get(v8::Integer::New(i))->IntegerValue());
	}
    } else {
	v8::String::Utf8Value str(args[0]);
	printf("%s", *str);
    }
    return v8::Undefined();
}

void setup_system(char ** envp, v8::Handle<v8::Object> global) {
  v8::HandleScope handle_scope;
  v8::Handle<v8::ObjectTemplate> systemt = v8::ObjectTemplate::New();
  v8::Handle<v8::Object> system = systemt->NewInstance();

  v8::Handle<v8::ObjectTemplate> envt = v8::ObjectTemplate::New();
  v8::Handle<v8::Object> env = envt->NewInstance();

  global->Set(v8::String::New("System"), system);
  system->Set(v8::String::New("stdin"), v8::FunctionTemplate::New(_stdin)->GetFunction());
  system->Set(v8::String::New("stdout"), v8::FunctionTemplate::New(_stdout)->GetFunction());
  
  system->Set(v8::String::New("env"), env);
  
  std::string name, value;
  bool done;
  int i,j;
  char ch;
  
  for(i = 0; envp[i] != NULL; i++) {
    done = false;
    name = "";
    value = "";
    for (j = 0; envp[i][j] != '\0'; j++) {
	ch = envp[i][j];
	if (!done) {
	    if (ch == '=') {
		done = true;
	    } else {
    		name += ch;
	    }
	} else {
	    value += ch;
	}
    }
    env->Set(v8::String::New(name.c_str()), v8::String::New(value.c_str()));
  }
}

