/*
 * v8cgi app file. Loosely based on V8's "shell" sample app.
 */

#define _STRING(x) #x
#define STRING(x) _STRING(x)

#include <sstream>
#include <stdlib.h>
#include <v8.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include "js_app.h"
#include "js_system.h"
#include "js_io.h"
#include "js_socket.h"
#include "js_macros.h"
#include "js_cache.h"

#ifndef windows
#   include <dlfcn.h>
#	define DLSYM dlsym
#else
#   include <windows.h>
#	define DLSYM GetProcAddress
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

JS_METHOD(_include) {
	v8::HandleScope handle_scope;
	v8cgi_App * app = APP_PTR;
	v8::String::Utf8Value file(args[0]);
	int result = app->include(*file);
	return JS_BOOL(!result);
}

JS_METHOD(_onexit) {
	v8::HandleScope handle_scope;
	v8cgi_App * app = APP_PTR;
	app->addOnExit(args[0]);
	return v8::Undefined();
}

JS_METHOD(_exit) {
	v8::Context::GetCurrent()->Exit();
	return v8::Undefined();
}

int v8cgi_App::init(int argc, char ** argv) {
	v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
	this->cfgfile = STRING(CONFIG_PATH);
	
	int argptr = 0;
	for (int i = 1; i < argc; i++) {
		const char* str = argv[i];
		std::string sstr = str;
		argptr = i;
		if (sstr.find("-c") == 0 && i + 1 < argc) {
			this->cfgfile = argv[i+1];
			argptr = 0;
			i++;
		}
	}
	
	if (argptr) { this->mainfile = argv[argptr]; }
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

int v8cgi_App::execute(char ** envp) {
	int result;
	v8::HandleScope handle_scope;
	v8::Handle<v8::ObjectTemplate> globaltemplate = v8::ObjectTemplate::New();
	globaltemplate->SetInternalFieldCount(1);
	v8::Handle<v8::Context> context = v8::Context::New(NULL, globaltemplate);
	v8::Context::Scope context_scope(context);
	
	result = this->prepare(envp);
	if (result == 0) {
		result = this->go(envp);
	}
	this->finish();
	return result;
}

void v8cgi_App::addOnExit(v8::Handle<v8::Value> what) {
	this->onexit->Set(JS_INT(this->onexit->Length()), what);
}

int v8cgi_App::include(std::string str) {
	std::string filename = this->findname(str);
	if (filename == "") {
		std::string s = "Cannot find '";
		s += str;
		s += "'\n";
		this->report_error(s.c_str());
		return 1;
	}
	
	int result;
	size_t index = filename.find_last_of(".");
	std::string ext = filename.substr(index+1);
	
	if (ext == "so" || ext == "dll") {
		result = this->include_dso(filename);
	} else {
		result = this->include_js(filename);
	}
	return result;
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

int v8cgi_App::include_js(std::string filename) {
	v8::HandleScope handle_scope;
	v8::TryCatch try_catch;

	v8::Handle<v8::String> source = JS_STR(this->cache.getJS(filename).c_str());
	if (source->Length() == 0) {
		std::string s = "Error reading '";
		s += filename;
		s += "'\n";
		this->report_error(s.c_str());
		return 1;
	}
	
	v8::Handle<v8::Script> script = v8::Script::Compile(source, JS_STR(filename.c_str()));
	if (script.IsEmpty()) {
		this->exception(&try_catch);
		return 1;
	} else {
		this->save_cwd();
		chdir(this->dirname(filename).c_str());
		v8::Handle<v8::Value> result = script->Run();
		this->restore_cwd();
		if (result.IsEmpty()) {
			this->exception(&try_catch);
			return 1;
		}
	}
	return 0;
}

int v8cgi_App::include_dso(std::string filename) {
	v8::HandleScope handle_scope;
	void * handle = this->cache.getHandle(filename);
	if (handle == NULL) {
		std::string error = "Cannot load shared library '";
		error += filename;
		error += "'\n";
		this->report_error(error.c_str());
		return 1;
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
		return 1;
	}
	
	v8::Handle<v8::Object> exports = v8::Object::New();
	func(exports);
	this->populate_global(exports);
	return 0;									
}

void v8cgi_App::populate_global(v8::Handle<v8::Object> exports) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Array> names = exports->GetPropertyNames();
	for (unsigned i=0;i<names->Length();i++) {
		v8::Handle<v8::Value> name = names->Get(JS_INT(i));
		JS_GLOBAL->Set(name, exports->Get(name));
	}
}

void v8cgi_App::save_cwd() {
	this->cwd = getcwd(NULL, 0);
}

void v8cgi_App::restore_cwd() {
	chdir(this->cwd.c_str());
}

std::string v8cgi_App::findname(std::string name) {
	v8::Handle<v8::Value> config = JS_GLOBAL->Get(JS_STR("Config"));
	v8::Handle<v8::Value> prefix = config->ToObject()->Get(JS_STR("libraryPath"));
	v8::String::Utf8Value pfx(prefix);
	
	char * paths[] = { "", *pfx};
	char * suffixes[] = {"js", "so", "dll"};
	std::string path = "";
	std::string path2 = "";
	
	for (int i=0;i<2;i++) {
		path = "";
		path += paths[i];
		if (strlen(paths[i]) > 0) { path += "/"; }
		path += name;
		if (this->exists(path)) { return path; }
		for (int j=0;j<3;j++) {
			path2 = path;
			path2 += ".";
			path2 += suffixes[j];
			if (this->exists(path2)) { return path2; }
		}
	}
	return std::string("");
}

bool v8cgi_App::exists(std::string filename) {
	struct stat st;
	if (stat(filename.c_str(), &st) != 0) { return false; } /* does not exist */
	if (st.st_mode & S_IFDIR) { return false; } /* is directory */
	return true;
}

std::string v8cgi_App::dirname(std::string filename) {
	size_t pos = filename.find_last_of('/');
	if (pos == std::string::npos) { pos = filename.find_last_of('\\'); }
	if (pos != std::string::npos) {
		filename.erase(pos, filename.length()-pos);
	}
	return filename;
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
		if (this->include(filename)) { return 1; }
	}
	return 0;
}

void v8cgi_App::finish() {
	v8::HandleScope handle_scope;
	uint32_t max = this->onexit->Length();
	v8::Handle<v8::Function> fun;
	for (unsigned int i=0;i<max;i++) {
		fun = v8::Handle<v8::Function>::Cast(this->onexit->Get(JS_INT(i)));
		fun->Call(JS_GLOBAL, 0, NULL);
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

int v8cgi_App::go(char ** envp) {
	v8::HandleScope handle_scope;
	
	this->http(); /* setup builtin request and response, if running as CGI */
	
	if (this->mainfile.length() == 0) { // try the PATH_TRANSLATED env var
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
	
	if (this->mainfile.length() == 0) {
		error("Nothing to do.\n", __FILE__, __LINE__);
		return 1;
	} else {
		return this->include(this->mainfile);
	}
}

int v8cgi_App::prepare(char ** envp) {
	this->onexit = v8::Array::New();
	v8::Handle<v8::Object> g = JS_GLOBAL;
	
	GLOBAL_PROTO->SetInternalField(0, v8::External::New((void *)this)); 
	
	g->Set(JS_STR("include"), v8::FunctionTemplate::New(_include)->GetFunction());
	g->Set(JS_STR("onexit"), v8::FunctionTemplate::New(_onexit)->GetFunction());
//	g->Set(JS_STR("exit"), v8::FunctionTemplate::New(_exit)->GetFunction());
	g->Set(JS_STR("global"), g);
	g->Set(JS_STR("Config"), v8::Object::New());

	setup_system(g, envp);
	setup_io(g);	
	setup_socket(g);
	
	if (this->include(cfgfile)) { 
		error("Cannot load configuration, quitting...\n", __FILE__, __LINE__);
		return 1;
	}

	if (this->autoload()) {  
		error("Cannot load default libraries, quitting...\n", __FILE__, __LINE__); 
		return 1;
	}
	
	return 0;
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
