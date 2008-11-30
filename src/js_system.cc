#include <v8.h>
#include <sstream>
#include <js_common.h>

JS_METHOD(_stdin) {
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
		data = (char *)	malloc(count + sizeof(char));
		fread(data,sizeof(char),count,stdin);
		data[count] = '\0';
	}
	if (args.Length() > 1 && args[1]->IsTrue()) {
		return char2array(data, count);
	} else {
		return char2string(data, count);
	}
}

JS_METHOD(_stdout) {
	v8::HandleScope handle_scope;
	if (args[0]->IsArray()) {
		v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
		uint32_t len = arr->Length();
		for (unsigned int i=0;i<len;i++) {
			printf("%c", (char) arr->Get(JS_INT(i))->IntegerValue());
		}
	} else {
		v8::String::Utf8Value str(args[0]);
		printf("%s", *str);
	}
	return v8::Undefined();
}

JS_METHOD(_system) {
	v8::HandleScope handle_scope;
	if (args.Length() != 1) {
		return v8::ThrowException(JS_STR("Wrong argument count. Use System.system(\"command\")"));
	}
	
	v8::String::Utf8Value cmd(args[0]);
	int result = system(*cmd);
	return JS_INT(result);
}

void setup_system(char ** envp, v8::Handle<v8::Object> global) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::ObjectTemplate> systemt = v8::ObjectTemplate::New();
	v8::Handle<v8::Object> system = systemt->NewInstance();

	v8::Handle<v8::ObjectTemplate> envt = v8::ObjectTemplate::New();
	v8::Handle<v8::Object> env = envt->NewInstance();

	global->Set(JS_STR("System"), system);
	system->Set(JS_STR("stdin"), v8::FunctionTemplate::New(_stdin)->GetFunction());
	system->Set(JS_STR("stdout"), v8::FunctionTemplate::New(_stdout)->GetFunction());
	system->Set(JS_STR("system"), v8::FunctionTemplate::New(_system)->GetFunction());
	system->Set(JS_STR("env"), env);
	
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
		env->Set(JS_STR(name.c_str()), JS_STR(value.c_str()));
	}
}
