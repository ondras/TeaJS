/*
 * v8cgi app file. Loosely based on V8's "shell" sample app.
 */

#define _STRING(x) #x
#define STRING(x) _STRING(x)

#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <v8.h>

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include "js_app.h"
#include "js_system.h"
#include "js_io.h"
#include "js_socket.h"
#include "js_macros.h"
#include "js_cache.h"
#include "js_path.h"

#ifndef windows
#   include <dlfcn.h>
#	define DLSYM dlsym
#else
#   include <windows.h>
#	define DLSYM GetProcAddress
#   define dlsym(x,y) (void*)GetProcAddress((HMODULE)x,y)
#endif

JS_METHOD(_include) {
	v8cgi_App * app = APP_PTR;
	v8::String::Utf8Value file(args[0]);
	int result = app->include(*file, true);
	return JS_BOOL(!result);
}

JS_METHOD(_require) {
	v8cgi_App * app = APP_PTR;
	v8::String::Utf8Value file(args[0]);
	return app->require(*file, true);
}

JS_METHOD(_onexit) {
	v8cgi_App * app = APP_PTR;

	v8::Persistent<v8::Function> fun  = v8::Persistent<v8::Function>::New(v8::Handle<v8::Function>::Cast(args[0]));
	app->onexit.push_back(fun);
	return v8::Undefined();
}

JS_METHOD(_exit) {
	v8::Context::GetCurrent()->Exit();
	return v8::Undefined();
}

// Format for command line arguments
//
// as you can see if you wish to pass any arguments to v8, you MUST
// put a -- surrounded by whitespace after all the v8 arguments
//
// any arguments after the v8_args but before the program_file are
// used by v8cgi.
static const char* v8cgi_usage = "v8cgi [v8_args --] [-c path] program_file [argument ...]";

int v8cgi_App::init(int argc, char ** argv) {
	if (!this->process_args(argc, argv)) {
		std::string err = "Invalid command line usage.\n";
		err += "Correct usage: ";
		err += v8cgi_usage;
		err += "\n";
		this->error(err.c_str(), __FILE__, __LINE__);
		return 1;
	}

	FILE* file = fopen(this->cfgfile.c_str(), "rb");
	if (file == NULL) { 
		std::string err = "Invalid configuration file (";
		err += this->cfgfile;
		err += ").\n";
		this->error(err.c_str(), __FILE__, __LINE__ );
		return 1;
	}
	fclose(file);
	return 0;
}

int v8cgi_App::execute(char ** envp, bool change) {
	v8::HandleScope handle_scope;
	int result;
	v8::Handle<v8::ObjectTemplate> globaltemplate = v8::ObjectTemplate::New();
	globaltemplate->SetInternalFieldCount(1);
	v8::Handle<v8::Context> context = v8::Context::New(NULL, globaltemplate);
	v8::Context::Scope context_scope(context);
	
	result = this->prepare(envp); /* prepare JS environment */
	if (result == 0) { result = this->findmain(); } /* try to locate main file */
	if (result == 0) {
		if (change) { path_chdir(path_dirname(this->mainfile)); } /* if requested, chdir */
		std::string current = path_getcwd(); /* add current path to stack */
		this->paths.push(current);
		result = this->process(); /* go! */
	} else {
		error("Nothing to do.\n", __FILE__, __LINE__);
	}
	
	this->finish();
	return result;
}

int v8cgi_App::include(std::string str, bool populate) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Value> exports = this->require(str, populate);
	
	int result = (exports->IsNull() ? 1 : 0);
	if (populate && !result) { 
		v8::Persistent<v8::Object> obj = v8::Persistent<v8::Object>::New(exports->ToObject());
		this->populate_global(obj); 
		obj.Dispose();
	}
	return result;
}

v8::Handle<v8::Value> v8cgi_App::require(std::string str, bool wrap) {
	v8::HandleScope handle_scope;
	std::string filename = this->findname(str);
	if (filename == "") {
		std::string s = "Cannot find '";
		s += str;
		s += "'\n";
		this->report_error(s.c_str());
		return v8::Null();
	}
	
	v8cgi_App::exportmap::iterator it = this->exports.find(filename);
	if (it != this->exports.end()) { /* use cached version */
		return this->exports[filename];
	}
	
	this->paths.push(path_dirname(filename));
	
	v8::Handle<v8::Value> data;
	size_t index = filename.find_last_of(".");
	std::string ext = filename.substr(index+1);
	if (ext == "so" || ext == "dll") {
		data = this->include_dso(filename);
	} else {
		data = this->include_js(filename, wrap);
	}

	this->paths.pop();
	v8::Persistent<v8::Value> exports = v8::Persistent<v8::Value>::New(data);
	this->exports[filename] = exports;
	return handle_scope.Close(data);
}

void v8cgi_App::report_error(const char * message) {
	int cgi = 0;
	v8::Local<v8::Function> fun;
	v8::Local<v8::Value> context = JS_GLOBAL->Get(JS_STR("response"));
	if (context->IsObject()) {
		v8::Local<v8::Value> print = context->ToObject()->Get(JS_STR("write"));
		if (print->IsObject()) {
			fun = v8::Local<v8::Function>::Cast(print);
			cgi = 1;
		}
	}
	if (!cgi) {
		context = JS_GLOBAL->Get(JS_STR("System"));
		fun = v8::Local<v8::Function>::Cast(context->ToObject()->Get(JS_STR("stdout")));
	}
	
	v8::Handle<v8::Value> data[1];
	data[0] = JS_STR(message);
	fun->Call(context->ToObject(), 1, data);
}

void v8cgi_App::exception(v8::TryCatch* try_catch) {
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
	
	this->report_error(msgstring.c_str());
}

v8::Handle<v8::Value> v8cgi_App::include_js(std::string filename, bool wrap) {
	v8::HandleScope handle_scope;
	v8::TryCatch try_catch;

	std::string source = this->cache.getJS(filename);
	if (source.length() == 0) {
		std::string s = "Error reading '";
		s += filename;
		s += "'\n";
		this->report_error(s.c_str());
		return v8::Null();
	}
	
	if (wrap) { source = this->wrap(source); }
	
	v8::Handle<v8::Script> script = v8::Script::Compile(JS_STR(source.c_str()), JS_STR(filename.c_str()));
	if (script.IsEmpty()) {
		this->exception(&try_catch);
		return v8::Null();
	} else {
		v8::Handle<v8::Value> result = script->Run();
		if (result.IsEmpty()) {
			this->exception(&try_catch);
			return v8::Null();
		}
		return handle_scope.Close(result);
	}
}

v8::Handle<v8::Value> v8cgi_App::include_dso(std::string filename) {
	v8::HandleScope handle_scope;
	void * handle = this->cache.getHandle(filename);
	if (handle == NULL) {
		std::string error = "Cannot load shared library '";
		error += filename;
		error += "'\n";
		this->report_error(error.c_str());
		return v8::Null();
	}

	typedef void (*funcdef)(v8::Handle<v8::Object>);
	typedef funcdef (*dlsym_t)(void *, const char *);
	funcdef func;
	func = ((dlsym_t)(DLSYM))(handle, "init");	
	
	if (!func) {
		std::string error = "Cannot initialize shared library '";
		error += filename;
		error += "'\n";
		this->report_error(error.c_str());
		return v8::Null();
	}
	
	v8::Handle<v8::Object> exports = v8::Object::New();
	func(exports);
	return handle_scope.Close(exports);	
}

std::string v8cgi_App::wrap(std::string original) {
	std::string result = "";
	result += "(function() { var exports = {}; (function(exports){";
	result += original;
	result += "})(exports); return exports; })()";
	return result;
}

void v8cgi_App::populate_global(v8::Handle<v8::Object> exports) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Array> names = exports->GetPropertyNames();
	for (unsigned i=0;i<names->Length();i++) {
		v8::Handle<v8::Value> name = names->Get(JS_INT(i));
		JS_GLOBAL->Set(name, exports->Get(name));		
	}
}

std::string v8cgi_App::findname(std::string name) {
	v8::Handle<v8::Value> config = JS_GLOBAL->Get(JS_STR("Config"));
	v8::Handle<v8::Value> prefix = config->ToObject()->Get(JS_STR("libraryPath"));
	v8::String::Utf8Value pfx(prefix);
	
	std::string current = (this->paths.empty() ? "" : this->paths.top());
	std::string paths[] = { current, std::string(*pfx) };
	const char * suffixes[] = {"js", "so", "dll"};
	std::string path = "";
	std::string path2 = "";
	
	for (int i=0;i<2;i++) {
		path = path_normalize(name, paths[i]);
		if (path_exists(path)) { return path; }
		for (int j=0;j<3;j++) {
			path2 = path;
			path2 += ".";
			path2 += suffixes[j];
			if (path_exists(path2)) { return path2; }
		}
	}
	return std::string("");
}

int v8cgi_App::autoload() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Value> config = JS_GLOBAL->Get(JS_STR("Config"));
	v8::Handle<v8::Array> list = v8::Handle<v8::Array>::Cast(config->ToObject()->Get(JS_STR("libraryAutoload")));
	int cnt = list->Length();
	for (int i=0;i<cnt;i++) {
		v8::Handle<v8::Value> item = list->Get(JS_INT(i));
		v8::String::Utf8Value name(item);
		std::string filename = *name;
		if (this->include(filename, true)) { return 1; }
	}
	return 0;
}

void v8cgi_App::finish() {
	v8::HandleScope handle_scope;
	/* callbacks */
	for (unsigned int i=0; i<this->onexit.size(); i++) {
		this->onexit[i]->Call(JS_GLOBAL, 0, NULL);
		this->onexit[i].Dispose();
	}
	this->onexit.clear();

	/* export cache */
	v8cgi_App::exportmap::iterator it;
	for (it=this->exports.begin(); it != this->exports.end(); it++) {
		it->second.Dispose();
	}
	this->exports.clear();
	
	/* paths */
	while (!this->paths.empty()) {
		this->paths.pop();
	}
}

void v8cgi_App::http() { /* prepare global request and response objects */
	v8::Handle<v8::Object> sys = JS_GLOBAL->Get(JS_STR("System"))->ToObject();
	v8::Handle<v8::Value> env = sys->ToObject()->Get(JS_STR("env"));
	v8::Handle<v8::Value> ss = env->ToObject()->Get(JS_STR("SERVER_SOFTWARE"));
	if (!ss->IsString()) { return; }
	
	v8::Handle<v8::Object> http = JS_GLOBAL->Get(JS_STR("HTTP"))->ToObject();
	v8::Handle<v8::Value> req = http->Get(JS_STR("ServerRequest"));
	v8::Handle<v8::Value> res = http->Get(JS_STR("ServerResponse"));
	v8::Handle<v8::Function> reqf = v8::Handle<v8::Function>::Cast(req);
	v8::Handle<v8::Function> resf = v8::Handle<v8::Function>::Cast(res);

	v8::Handle<v8::Value> reqargs[] = { 
		sys->Get(JS_STR("stdin")),
		sys->Get(JS_STR("env"))
	};
	v8::Handle<v8::Value> resargs[] = { 
		sys->Get(JS_STR("stdout")),
		sys->Get(JS_STR("header"))
	};

	JS_GLOBAL->Set(JS_STR("request"), reqf->NewInstance(2, reqargs));
	JS_GLOBAL->Set(JS_STR("response"), resf->NewInstance(2, resargs));
}

int v8cgi_App::findmain() {
	if (this->mainfile.length() == 0) { /* try the PATH_TRANSLATED env var */
		v8::Handle<v8::Value> sys = JS_GLOBAL->Get(JS_STR("System"));
		v8::Handle<v8::Value> env = sys->ToObject()->Get(JS_STR("env"));
		v8::Handle<v8::Value> pt = env->ToObject()->Get(JS_STR("PATH_TRANSLATED"));
		v8::Handle<v8::Value> sf = env->ToObject()->Get(JS_STR("SCRIPT_FILENAME"));
		if (pt->IsString()) {
			v8::String::Utf8Value jsname(pt);
			this->mainfile = *jsname;
		} else if (sf->IsString()) {
			v8::String::Utf8Value jsname(sf);
			this->mainfile = *jsname;
		}
	}
	
	return (this->mainfile.length() == 0 ? 1 : 0);
}

int v8cgi_App::process() {
	this->http(); /* setup builtin request and response, if running as CGI */
	return this->include(this->mainfile, false);
}

int v8cgi_App::prepare(char ** envp) {
	v8::Handle<v8::Object> g = JS_GLOBAL;
	
	GLOBAL_PROTO->SetInternalField(0, v8::External::New((void *)this)); 
	g->Set(JS_STR("include"), v8::FunctionTemplate::New(_include)->GetFunction());
	g->Set(JS_STR("require"), v8::FunctionTemplate::New(_require)->GetFunction());
	g->Set(JS_STR("onexit"), v8::FunctionTemplate::New(_onexit)->GetFunction());
//	g->Set(JS_STR("exit"), v8::FunctionTemplate::New(_exit)->GetFunction());
	g->Set(JS_STR("global"), g);
	g->Set(JS_STR("Config"), v8::Object::New());

	setup_system(g, envp);
	setup_io(g);	
	setup_socket(g);
	
	if (this->include(cfgfile, false)) { 
		error("Cannot load configuration, quitting...\n", __FILE__, __LINE__);
		return 1;
	}

	if (this->autoload()) {  
		error("Cannot load default libraries, quitting...\n", __FILE__, __LINE__); 
		return 1;
	}
	
	v8::Handle<v8::Object> args = v8::Array::New();
	for (size_t i = 0; i < this->mainfile_args.size(); ++i) {
		args->Set(JS_INT(i), JS_STR(this->mainfile_args.at(i).c_str()));
	}
	g->Set(JS_STR("arguments"), args);
	
	return 0;
}

// return true if we were able to (optionally) set a config file and 
// (non-optionally) set a mainfile. false if usage was invalid.
bool v8cgi_App::process_args(int argc, char ** argv) {
	// see the v8cgi_usage definition for the format
	
	// we must have atleast one arg
	if (argc == 1) return false;
	
	int index = 0;
	
	// see if we have v8 options
	bool have_v8args = false;
	for (; index < argc; ++index) {
		// FIXME: if there is a standalone "--" after the name of the script
		// then this breaks.  I can't figure out a solution to this, so
		// for now we don't support any standalone "--" after the script name.
		// One solution (and the way it currently works) is to require "--"
		// before all other args even if no v8 args are used, but that seems
		// I don't like this, but it is where we are right now.
		if (std::string(argv[index]) == "--") {
			// treat all previous arguments as v8 arguments
			int v8argc = index;
			v8::V8::SetFlagsFromCommandLine(&v8argc, argv, true);
			++index; // skip over the "--"
			have_v8args = true;
			break;
		}
	}
	
	// if there were no v8 args, then reset index to the first argument
	if (!have_v8args) index = 1;
	
	// Only the very next argument can be the "-c".  if it isn't
	// then set the cfgfile to the one passed in at compile time
	if (std::string(argv[index]) == "-c") {
		// make sure there is an argument after the "-c"
		if (index + 1 >= argc) return false;
		else ++index;
		
		//printf("cfgfile: %s\n", argv[index]);
		this->cfgfile = argv[index];
		++index; // skip over the config file
	} else
		this->cfgfile = STRING(CONFIG_PATH);
	
	// argv[index] MUST be the program_file.  If it doesn't
	// exist then we have an error.
	std::string program_file = argv[index];
	if (program_file.size() == 0)
		return false;
	else {
		//printf("mainfile: %s\n", argv[index]);
		this->mainfile = argv[index];
		++index; // skip over the program_file
	}
	
	// all the rest of the arguments are arguments to the program_file
	for (; index < argc; ++index) {
		//printf("program_arg: %s\n", argv[index]);
		this->mainfile_args.push_back(std::string(argv[index]));
	}
	
	return true;
}

size_t v8cgi_App::reader(char * destination, size_t amount) {
	return fread((void *) destination, sizeof(char), amount, stdin);
}

size_t v8cgi_App::writer(const char * data, size_t amount) {
	return fwrite((void *) data, sizeof(char), amount, stdout);
}

void v8cgi_App::error(const char * data, const char * file, int line) {
	fwrite((void *) data, sizeof(char), strlen(data), stderr);
}

void v8cgi_App::header(const char * name, const char * value) {
	printf("%s: %s\n", name, value);
}
