/*
 * v8cgi main file. Loosely based on V8's "shell" sample app.
 */

#include <v8.h>
#include "js_system.h"
#include "js_io.h"
#include "js_common.h"
#include "js_macros.h"
#include <dlfcn.h>

#include <sstream>

#define _STRING(x) #x
#define STRING(x) _STRING(x)

// chdir()
#ifndef HAVE_CHDIR
#	include <direct.h>
#       define chdir(name) _chdir(name)
#endif

// getcwd()
#ifndef HAVE_GETCWD
#	include <direct.h>
#       define getcwd(name, bytes) _getcwd(name, bytes)
#endif

v8::Handle<v8::Array> __onexit;

void die(int code) {
	uint32_t max = __onexit->Length();
	v8::Handle<v8::Function> fun;
	for (unsigned int i=0;i<max;i++) {
		fun = v8::Handle<v8::Function>::Cast(__onexit->Get(JS_INT(i)));
		fun->Call(v8::Context::GetCurrent()->Global(), 0, NULL);
	}
	exit(code);
}

v8::Handle<v8::String> read_file(const char* name) {
	FILE* file = fopen(name, "rb");
	if (file == NULL) return v8::Handle<v8::String>();

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	char* chars = new char[size + 1];
	chars[size] = '\0';
	for (unsigned int i = 0; i < size;) {
		size_t read = fread(&chars[i], 1, size - i, file);
		i += read;
	}
	fclose(file);

	/* remove shebang line */	
	std::string str = chars;
	if ( str.find('#',0) == 0 && str.find('!',1) == 1 ) {
		unsigned int pfix = str.find('\n',0);
		str.erase(0,pfix);
	};
	
	v8::Handle<v8::String> result = JS_STR(str.c_str());
	delete[] chars;
	return result;
}

void report_exception(v8::TryCatch* try_catch) {
	v8::HandleScope handle_scope;
	v8::String::Utf8Value exception(try_catch->Exception());
	v8::Handle<v8::Message> message = try_catch->Message();
	std::string msgstring = "";
	std::stringstream ss;
	std::string tmp;

	if (message.IsEmpty()) {
		msgstring += *exception;
		msgstring += "\n";
	} else {
		v8::String::Utf8Value filename(message->GetScriptResourceName());
		int linenum = message->GetLineNumber();
		msgstring += *filename;
		msgstring += ":";
		
		ss << linenum;
		ss >> tmp;

		msgstring += tmp;
		msgstring += ": ";
		msgstring += *exception;
		msgstring += "\n";
	}
	
	int cgi = 0;
	v8::Local<v8::Function> fun;
	v8::Local<v8::Value> context = v8::Context::GetCurrent()->Global()->Get(JS_STR("response"));
	if (context->IsObject()) {
		v8::Local<v8::Value> print = context->ToObject()->Get(JS_STR("error"));
		if (print->IsObject()) {
			fun = v8::Local<v8::Function>::Cast(print);
			cgi = 1;
		}
	}
	if (!cgi) {
		context = v8::Context::GetCurrent()->Global()->Get(JS_STR("System"));
		fun = v8::Local<v8::Function>::Cast(context->ToObject()->Get(JS_STR("stdout")));
	}
	
	v8::Handle<v8::Value> data[1];
	data[0] = JS_STR(msgstring.c_str());
	fun->Call(context->ToObject(), 1, data);
}

int execute_file(const char * str, bool change) {
	v8::HandleScope handle_scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::String> name = JS_STR(str);
	v8::Handle<v8::String> source = read_file(str);

	if (source.IsEmpty()) {
		printf("Error reading '%s'\n", str);
		return 1;
	}
	
	v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
	if (script.IsEmpty()) {
		report_exception(&try_catch);
		return 1;
	} else {
		char * old = getcwd(NULL, 0);
		char * end = strrchr((char *)str, '/');
		if (end == NULL) {
			end = strrchr((char *)str, '\\');
		}
		if (end != NULL && change) {
			int len = end-str;
			char * base = (char *) malloc(len+1);
			strncpy(base, str, len);
    		base[len] = '\0';
    		chdir(base);
			free(base);
		}
		
		v8::Handle<v8::Value> result = script->Run();
		
		chdir(old);
		if (result.IsEmpty()) {
			report_exception(&try_catch);
			return 1;
		}
	}
	return 0;
}

int library(char * name) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Value> config = v8::Context::GetCurrent()->Global()->Get(JS_STR("Config"));
	v8::Handle<v8::Value> prefix = config->ToObject()->Get(JS_STR("libraryPath"));
	v8::String::Utf8Value pfx(prefix);
	std::string path = "";
	
	path += *pfx;
	path += "/";
	path += name;
	
	if (path.find(".so") != std::string::npos) {
		void * handle;
	    if (!(handle = dlopen(path.c_str(), RTLD_LAZY))) {
			printf("open");
			return 1;
		}
		void (*func) (v8::Handle<v8::Object>);
		if (!(func = reinterpret_cast<void (*)(v8::Handle<v8::Object>)>(dlsym(handle, "init")))) {
			printf("init");
			dlclose(handle);
			return 1;
		}
		func(v8::Context::GetCurrent()->Global());
		return 0;									
	} else {
		return execute_file(path.c_str(), false);
	}
}

v8::Handle<v8::Value> _include(const v8::Arguments& args) {
	bool ok = true;
	int result;
	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		v8::String::Utf8Value file(args[i]);
		result = execute_file(*file, false);
		if (result != 0) { ok = false; }
	}
	return JS_BOOL(ok);
}

v8::Handle<v8::Value> _library(const v8::Arguments & args) {
	bool ok = true;
	int result;

	v8::Handle<v8::Value> config = v8::Context::GetCurrent()->Global()->Get(JS_STR("Config"));
	v8::Handle<v8::Value> prefix = config->ToObject()->Get(JS_STR("libraryPath"));
	v8::String::Utf8Value pfx(prefix);

	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		v8::String::Utf8Value file(args[i]);
		result = library(*file);
		if (result != 0) { ok = false; }
	}
	return JS_BOOL(ok);
}

v8::Handle<v8::Value> _exit(const v8::Arguments& args) {
	die(args[0]->Int32Value());
	return v8::Undefined();
}

v8::Handle<v8::Value> _onexit(const v8::Arguments& args) {
	__onexit->Set(JS_INT(__onexit->Length()), args[0]);
	return v8::Undefined();
}

int library_autoload() {
	v8::Handle<v8::Value> config = v8::Context::GetCurrent()->Global()->Get(JS_STR("Config"));
	v8::Handle<v8::Array> list = v8::Handle<v8::Array>::Cast(config->ToObject()->Get(JS_STR("libraryAutoload")));
	int cnt = list->Length();
	for (int i=0;i<cnt;i++) {
		v8::Handle<v8::Value> item = list->Get(JS_INT(i));
		v8::String::Utf8Value name(item);
		if (library(*name)) { return 1; }
	}
	return 0;
}

void init(char * cfg) {
	int result = execute_file(cfg, false);
	if (result) { 
		printf("Cannot load configuration, quitting...\n");
		die(1);
	}
	result = library_autoload();
	if (result) { 
		printf("Cannot load default libraries, quitting...\n");
		die(1);
	}
}

int main(int argc, char ** argv, char ** envp) {
	v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
	v8::HandleScope handle_scope;

	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
	v8::Handle<v8::Context> context = v8::Context::New(NULL, global);
	v8::Context::Scope context_scope(context);

	__onexit = v8::Array::New();
	context->Global()->Set(JS_STR("library"), v8::FunctionTemplate::New(_library)->GetFunction());
	context->Global()->Set(JS_STR("include"), v8::FunctionTemplate::New(_include)->GetFunction());
	context->Global()->Set(JS_STR("exit"), v8::FunctionTemplate::New(_exit)->GetFunction());
	context->Global()->Set(JS_STR("onexit"), v8::FunctionTemplate::New(_onexit)->GetFunction());
	context->Global()->Set(JS_STR("global"), context->Global());
	context->Global()->Set(JS_STR("Config"), v8::Object::New());

	setup_system(envp, context->Global());
	setup_io(context->Global());	
	
	char * cfg = STRING(CONFIG_PATH);
	int argptr = 0;
	for (int i = 1; i < argc; i++) {
		const char* str = argv[i];
		argptr = i;
		if (strcmp(str, "-c") == 0 && i + 1 < argc) {
			cfg = argv[i+1];
			argptr = 0;
			i++;
		}
	}
							 
	init(cfg);
	
	if (!argptr) {
		// try the PATH_TRANSLATED env var
		v8::Handle<v8::Value> sys = v8::Context::GetCurrent()->Global()->Get(JS_STR("System"));
		v8::Handle<v8::Value> env = sys->ToObject()->Get(JS_STR("env"));
		v8::Handle<v8::Value> pt = env->ToObject()->Get(JS_STR("PATH_TRANSLATED"));
		if (pt->IsString()) {
			v8::String::Utf8Value name(pt);
			int result = execute_file(*name, true);
			if (result) { die(result); }
		} else {
			printf("Nothing to do.\n");
		}
	} else {
		int result = execute_file(argv[argptr], true);
		if (result) { die(result); }
	}
	die(0);
}
