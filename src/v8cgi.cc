/*
 * v8cgi main file. Loosely based on V8's "shell" sample app.
 */

#define _STRING(x) #x
#define STRING(x) _STRING(x)

#include <sstream>
#include <stdlib.h>
#include <v8.h>
#include <map>

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include "js_system.h"
#include "js_io.h"
#include "js_socket.h"
#include "js_common.h"
#include "js_macros.h"
#include "js_cache.h"

#ifndef windows
#   include <dlfcn.h>
#else
#   include <windows.h>
#   define dlsym(x,y) (void*)GetProcAddress((HMODULE)x,y)
#endif

// chdir()
#ifndef HAVE_CHDIR
#	include <direct.h>
#	define chdir(name) _chdir(name)
#endif

// getcwd()
#ifndef HAVE_GETCWD
#	include <direct.h>
#	define getcwd(name, bytes) _getcwd(name, bytes)
#endif

v8::Handle<v8::Array> __onexit; /* what to do on exit */
const char * cfgfile = NULL; /* config file */
const char * execfile = NULL; /* command-line specified file */
Cache cache;

int total = 0; /* fcgi debug */

void js_error(const char * message) {
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
	data[0] = JS_STR(message);
	fun->Call(context->ToObject(), 1, data);
}

void js_exception(v8::TryCatch* try_catch) {
	v8::HandleScope handle_scope;
	v8::String::Utf8Value exception(try_catch->Exception());
	v8::Handle<v8::Message> message = try_catch->Message();
	std::string msgstring = "";
	std::stringstream ss;

	if (message.IsEmpty()) {
		msgstring += *exception;
		msgstring += "\n";
	} else {
		v8::String::Utf8Value filename(message->GetScriptResourceName());
		int linenum = message->GetLineNumber();
		msgstring += *filename;
		msgstring += ":";
		ss << linenum;
		msgstring += ss.str();
		msgstring += ": ";
		msgstring += *exception;
		msgstring += "\n";
	}
	
	js_error(msgstring.c_str());
}

v8::Handle<v8::String> js_read(const char* name) {
	std::string n = name;
	std::string source = cache.getJS(n);
	return JS_STR(source.c_str());
}

int js_execute(const char * str, bool change) {
	v8::HandleScope handle_scope;
	v8::TryCatch try_catch;
	v8::Handle<v8::String> name = JS_STR(str);
	v8::Handle<v8::String> source = js_read(str);

	if (source.IsEmpty()) {
		std::string s = "Error reading '";
		s += str;
		s += "'\n";
		js_error(s.c_str());
		return 1;
	}
	
	v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
	if (script.IsEmpty()) {
		js_exception(&try_catch);
		return 1;
	} else {
		char * tmp = getcwd(NULL, 0);
		std::string oldcwd = tmp;
		free(tmp);
		
		std::string newcwd = str;
		size_t pos = newcwd.find_last_of('/');
		if (pos == std::string::npos) { pos = newcwd.find_last_of('\\'); }
		if (pos != std::string::npos && change) {
			newcwd.erase(pos, newcwd.length()-pos);
    		chdir(newcwd.c_str());
		}
		
		v8::Handle<v8::Value> result = script->Run();
		
		if (change) { chdir(oldcwd.c_str()); }
		if (result.IsEmpty()) {
			js_exception(&try_catch);
			return 1;
		}
	}
	return 0;
}

int js_library(char * name) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Value> config = v8::Context::GetCurrent()->Global()->Get(JS_STR("Config"));
	v8::Handle<v8::Value> prefix = config->ToObject()->Get(JS_STR("libraryPath"));
	v8::String::Utf8Value pfx(prefix);
	std::string path = "";
	std::string error;
	
	path += *pfx;
	path += "/";
	path += name;
	
	if (path.find(".so") != std::string::npos || path.find(".dll") != std::string::npos) {
		void * handle = cache.getHandle(path);
		if (handle == NULL) {
			error = "Cannot load shared library '";
			error += path;
			error += "'\n";
			js_error(error.c_str());
			return 1;
		}

		void (*func) (v8::Handle<v8::Object>);
		func = reinterpret_cast<void (*)(v8::Handle<v8::Object>)>(dlsym(handle, "init"));
		if (!func) {
			error = "Cannot initialize shared library '";
			error += path;
			error += "'\n";
			js_error(error.c_str());
			return 1;
		}
		
		func(v8::Context::GetCurrent()->Global());
		return 0;									
	} else {
		return js_execute(path.c_str(), false);
	}
}

int js_autoload() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Value> config = v8::Context::GetCurrent()->Global()->Get(JS_STR("Config"));
	v8::Handle<v8::Array> list = v8::Handle<v8::Array>::Cast(config->ToObject()->Get(JS_STR("libraryAutoload")));
	int cnt = list->Length();
	for (int i=0;i<cnt;i++) {
		v8::Handle<v8::Value> item = list->Get(JS_INT(i));
		v8::String::Utf8Value name(item);
		if (js_library(*name)) { return 1; }
	}
	return 0;
}

JS_METHOD(_include) {
	bool ok = true;
	int result;
	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		v8::String::Utf8Value file(args[i]);
		result = js_execute(*file, true);
		if (result != 0) { ok = false; }
	}
	return JS_BOOL(ok);
}

JS_METHOD(_library) {
	v8::HandleScope handle_scope;
	bool ok = true;
	int result;

	v8::Handle<v8::Value> config = v8::Context::GetCurrent()->Global()->Get(JS_STR("Config"));
	v8::Handle<v8::Value> prefix = config->ToObject()->Get(JS_STR("libraryPath"));
	v8::String::Utf8Value pfx(prefix);

	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		v8::String::Utf8Value file(args[i]);
		result = js_library(*file);
		if (result != 0) { ok = false; }
	}
	return JS_BOOL(ok);
}

JS_METHOD(_onexit) {
	__onexit->Set(JS_INT(__onexit->Length()), args[0]);
	return v8::Undefined();
}

void main_terminate() {	
}

void main_finish() {
	v8::HandleScope handle_scope;
	uint32_t max = __onexit->Length();
	v8::Handle<v8::Function> fun;
	for (unsigned int i=0;i<max;i++) {
		fun = v8::Handle<v8::Function>::Cast(__onexit->Get(JS_INT(i)));
		fun->Call(v8::Context::GetCurrent()->Global(), 0, NULL);
	}
}

int main_execute() {
	v8::HandleScope handle_scope;
	const char * name = execfile;

	if (name == NULL) { // try the PATH_TRANSLATED env var
		v8::Handle<v8::Value> sys = v8::Context::GetCurrent()->Global()->Get(JS_STR("System"));
		v8::Handle<v8::Value> env = sys->ToObject()->Get(JS_STR("env"));
		v8::Handle<v8::Value> pt = env->ToObject()->Get(JS_STR("PATH_TRANSLATED"));
		if (pt->IsString()) {
			v8::String::Utf8Value jsname(pt);
			name = *jsname;
		}
	}
	
	if (name == NULL) {
		js_error("Nothing to do.\n");
		return 1;
	} else {
		return js_execute(name, true);
	}
	
}

int main_prepare(char ** envp) {
	__onexit = v8::Array::New();
	v8::Handle<v8::Object> g = v8::Context::GetCurrent()->Global();
	g->Set(JS_STR("library"), v8::FunctionTemplate::New(_library)->GetFunction());
	g->Set(JS_STR("include"), v8::FunctionTemplate::New(_include)->GetFunction());
	g->Set(JS_STR("onexit"), v8::FunctionTemplate::New(_onexit)->GetFunction());
	g->Set(JS_STR("total"), JS_INT(total++));
	g->Set(JS_STR("global"), g);
	g->Set(JS_STR("Config"), v8::Object::New());

	setup_system(envp, g);
	setup_io(g);	
	setup_socket(g);
	
	if (js_execute(cfgfile, false)) { 
		js_error("Cannot load configuration, quitting...\n");
		return 1;
	}

	if (js_autoload()) {  
		js_error("Cannot load default libraries, quitting...\n"); 
		return 1;
	}
	
	return 0;
}

int main_initialize(int argc, char ** argv) {
	v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
	cfgfile = STRING(CONFIG_PATH);
	
	int argptr = 0;
	for (int i = 1; i < argc; i++) {
		const char* str = argv[i];
		argptr = i;
		if (strcmp(str, "-c") == 0 && i + 1 < argc) {
			cfgfile = argv[i+1];
			argptr = 0;
			i++;
		}
	}
	
	if (argptr) { execfile = argv[argptr]; }
	
	FILE* file = fopen(cfgfile, "rb");
	if (file == NULL) { 
		printf("Invalid configuration file.\n");
		return 1;
	}
	fclose(file);
	return 0;
}

int main_cycle(char ** envp) {
	int result = 0;
	v8::HandleScope handle_scope;
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
	v8::Handle<v8::Context> context = v8::Context::New(NULL, global);
	v8::Context::Scope context_scope(context);

	result = main_prepare(envp);
	if (result == 0) {
		result = main_execute();
	}
	main_finish();
	return result;
}

int main(int argc, char ** argv, char ** envp) {
	int result = 0;
	result = main_initialize(argc, argv);
	if (result) { exit(1); }

#ifdef FASTCGI
	while(FCGI_Accept() >= 0) {
#endif

	result = main_cycle(envp);
	
#ifdef FASTCGI
	FCGI_SetExitStatus(result);
#endif
	
#ifdef FASTCGI
	}
#endif

	main_terminate();
	return result;
}
