#include <v8.h>
#include <sstream>

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include <js_common.h>
#include <js_macros.h>

#ifndef HAVE_SLEEP
#	include <windows.h>
#	define sleep(num) { Sleep(num * 1000); }
#endif

JS_METHOD(_stdin) {
	v8::HandleScope handle_scope;

	size_t count = 0;
	if (args.Length() && args[0]->IsNumber()) {
		count = args[0]->IntegerValue();
	}
	
	char * data = NULL;
	size_t size = afread(&data, count, stdin);
	if (args.Length() > 1 && args[1]->IsTrue()) {
		return char2array(data, size);
	} else {
		return char2string(data, size);
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
//		printf("%s", *str);
		fwrite(*str, sizeof(char), str.length(), stdout);
	}
	return v8::Undefined();
}

JS_METHOD(_system) {
	v8::HandleScope handle_scope;
	if (args.Length() != 1) {
		return JS_EXCEPTION("Wrong argument count. Use System.system(\"command\")");
	}
	
	v8::String::Utf8Value cmd(args[0]);
	int result = system(*cmd);
	return JS_INT(result);
}


JS_METHOD(_sleep) {
	v8::HandleScope handle_scope;
	int num = args[0]->Int32Value();
	sleep(num);
	return v8::Undefined();
}

/* 

JS_METHOD(_usleep) {
	v8::HandleScope handle_scope;
	int num = args[0]->Int32Value();
	usleep(num);
	return v8::Undefined();
}

*/
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
	system->Set(JS_STR("sleep"), v8::FunctionTemplate::New(_sleep)->GetFunction());
//	system->Set(JS_STR("usleep"), v8::FunctionTemplate::New(_usleep)->GetFunction());
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
