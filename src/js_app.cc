/*
 * v8cgi app file. Loosely based on V8's "shell" sample app.
 */

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

/**
 * global.include = global.require + populate global object
 */
JS_METHOD(_include) {
	v8cgi_App * app = APP_PTR;
	v8::String::Utf8Value file(args[0]);
	v8::Handle<v8::Value> result;
	try {
		result = app->include(*file, true, true); /* populate, wrap */
	} catch (std::string e) {
		return JS_EXCEPTION(e.c_str());
	}
	return result;
}

/**
 * global.require = load module and return its (cached) exports
 */
JS_METHOD(_require) {
	v8cgi_App * app = APP_PTR;
	v8::String::Utf8Value file(args[0]);
	v8::Handle<v8::Value> result;
	try {
		result = app->include(*file, false, true); /* do not populate, wrap */
	} catch (std::string e) {
		return JS_EXCEPTION(e.c_str());
	}
	return result;
}

/**
 * global.onexit = add a function to be executed when context ends
 */
JS_METHOD(_onexit) {
	v8cgi_App * app = APP_PTR;

	v8::Persistent<v8::Function> fun  = v8::Persistent<v8::Function>::New(v8::Handle<v8::Function>::Cast(args[0]));
	app->onexit.push_back(fun);
	return v8::Undefined();
}

/**
 * does not work atm.
 */
JS_METHOD(_exit) {
	v8::Context::GetCurrent()->Exit();
	return v8::Undefined();
}

/**
 * Format for command line arguments
 *
 * as you can see if you wish to pass any arguments to v8, you MUST
 * put a -- surrounded by whitespace after all the v8 arguments
 *
 * any arguments after the v8_args but before the program_file are
 * used by v8cgi.
 */
static const char * v8cgi_usage = "v8cgi [v8_args --] [-c path] program_file [argument ...]";

/**
 * Execute only once - process command line arguments, set config file name
 */
int v8cgi_App::init(int argc, char ** argv) {
	this->cfgfile = STRING(CONFIG_PATH);
	try {
		this->process_args(argc, argv);
	} catch (std::string e) {
		this->error(e.c_str(), __FILE__, __LINE__); /* initialization error -> goes to stderr */
		return 1;
	}

	return 0;
}

/**
 * Process a request.
 * @param {bool} change Perform a chdir?
 * @param {char**} envp Environment
 */
int v8cgi_App::execute(bool change, char ** envp) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::ObjectTemplate> globaltemplate = v8::ObjectTemplate::New();
	globaltemplate->SetInternalFieldCount(2);
	v8::Handle<v8::Context> context = v8::Context::New(NULL, globaltemplate);
	v8::Context::Scope context_scope(context);

	try {
		this->prepare(envp); /* prepare JS environment */
	} catch (std::string e) {
		this->error(e.c_str(), __FILE__, __LINE__); /* error with config file or default libs -> goes to stderr */
		this->finish();
		return 1;
	}

	try {
		this->findmain();  /* try to locate main file */
	} catch (std::string e) {
		this->error(e.c_str(), __FILE__, __LINE__); /* cannot locate main file -> goes to stderr */
		this->finish();
		return 1;
	}
	
	if (change) { path_chdir(path_dirname(this->mainfile)); } /* if requested, chdir */
	this->http(); /* setup builtin request and response, if running as CGI */

	try {
		this->include(this->mainfile, false, false); /* do not populate, do not wrap */
	} catch (std::string e) {
		this->error(e.c_str(), __FILE__, __LINE__); /* error when executing main file -> goes to ??? */
//		this->js_error(e.c_str()); /* error when executing main file -> goes to ??? */
		this->finish();
		return 1;
	}
	
	this->finish();
	return 0;
}

/**
 * Try to report error via JS means, instead of stderr 
 */
void v8cgi_App::js_error(std::string message) {
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
		if (context->IsUndefined()) {
			this->error(message.c_str(), __FILE__, __LINE__);
			return;
		} else {
			fun = v8::Local<v8::Function>::Cast(context->ToObject()->Get(JS_STR("stdout")));
		}
	}
	
	v8::Handle<v8::Value> data[1] = { JS_STR(message.c_str()) };
	fun->Call(context->ToObject(), 1, data);
}

/** 
 * Convert JS exception to c string 
 */
std::string v8cgi_App::exception(v8::TryCatch* try_catch) {
	v8::HandleScope handle_scope;
	v8::String::Utf8Value exception(try_catch->Exception());
	v8::Handle<v8::Message> message = try_catch->Message();
	std::string msgstring = "";
	std::stringstream ss;

	if (message.IsEmpty()) {
		msgstring += *exception;
	} else {
		v8::String::Utf8Value filename(message->GetScriptResourceName());
		int linenum = message->GetLineNumber();
		msgstring += *filename;
		msgstring += ":";
		ss << linenum;
		msgstring += ss.str();
		msgstring += ": ";
		msgstring += *exception;
	}
	return msgstring;
}

/**
 * Include a module
 * @param {std::string} name
 * @param {bool} populate Should we automatically populate global object?
 * @param {bool} wrap Should we wrap the module in an "exports" envelope?
 */
v8::Handle<v8::Value> v8cgi_App::include(std::string name, bool populate, bool wrap) {
	v8::HandleScope handle_scope;
#ifdef VERBOSE
	printf("[include] looking for '%s'\n", name.c_str()); 
#endif	
	std::string filename = this->findname(name, !wrap);
#ifdef VERBOSE
	printf("[include] resolved as '%s'\n", filename.c_str()); 
#endif	
	
	if (filename == "") {
		std::string s = "Cannot find '";
		s += name;
		s += "'";
		throw s;
	}
	
	exportmap::iterator it = this->exports.find(filename);
	if (it != this->exports.end()) { return this->exports[filename];  } /* use cached version */

	v8::Handle<v8::Object> exports = v8::Object::New();
	if (wrap) { this->exports[filename] = v8::Persistent<v8::Object>::New(exports); } /* add exports to cache */

	this->paths.push(path_dirname(filename)); /* prepare path to stack */
	v8::Handle<v8::Value> data; /* result */

	try {
		size_t index = filename.find_last_of(".");
		std::string ext = filename.substr(index+1);
		if (ext == "so" || ext == "dll") {
			data = this->include_dso(filename, exports);
		} else {
			data = this->include_js(filename, exports, wrap);

		}
	} catch (std::string e) {
		this->paths.pop(); /* remove from stack */
		if (wrap) { /* remove from export cache */
			exportmap::iterator it = this->exports.find(filename);
			this->exports.erase(it);
		}
		throw e; /* rethrow */
	}

	this->paths.pop(); /* execution ended, remove top path */
	if (populate) { this->populate_global(exports); }
	return handle_scope.Close(data);
}

/**
 * Include a js module
 */
v8::Handle<v8::Value> v8cgi_App::include_js(std::string filename, v8::Handle<v8::Object> exports, bool wrap) {
	v8::HandleScope handle_scope;
	v8::TryCatch tc;

	std::string source = this->cache.getJS(filename);
	if (wrap) { source = this->wrap(source); }
	
	v8::Handle<v8::Script> script = v8::Script::Compile(JS_STR(source.c_str()), JS_STR(filename.c_str()));
	if (tc.HasCaught()) {
		throw this->exception(&tc);
	} else {
		v8::Handle<v8::Value> result = script->Run();
		if (tc.HasCaught()) { throw this->exception(&tc); }
		
		if (wrap) {
			v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(result);
			v8::Handle<v8::Value> params[1] = {exports}; 
			result = fun->Call(JS_GLOBAL, 1, params);
			if (tc.HasCaught()) { throw this->exception(&tc); }
			return exports;
		}
		
		return handle_scope.Close(result);
	}
}

/**
 * Include a dso module
 */
v8::Handle<v8::Value> v8cgi_App::include_dso(std::string filename, v8::Handle<v8::Object> exports) {
	v8::HandleScope handle_scope;
	void * handle = this->cache.getHandle(filename);

	typedef void (*funcdef)(v8::Handle<v8::Object>);
	typedef funcdef (*dlsym_t)(void *, const char *);
	funcdef func;
	func = ((dlsym_t)(DLSYM))(handle, "init");	
	
	if (!func) {
		std::string error = "Cannot initialize shared library '";
		error += filename;
		error += "'";
		throw error;
	}
	
	func(exports);
	return handle_scope.Close(exports);	
}

/**
 * Wrap a string with exports envelope
 */
std::string v8cgi_App::wrap(std::string original) {
	std::string result = "";
	result += "(function(exports){";
	result += original;
	result += "})";
	return result;
}

/**
 * Apply exports object to global object
 */
void v8cgi_App::populate_global(v8::Handle<v8::Object> exports) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Array> names = exports->GetPropertyNames();
	for (unsigned i=0;i<names->Length();i++) {
		v8::Handle<v8::Value> name = names->Get(JS_INT(i));
		JS_GLOBAL->Set(name, exports->Get(name));		
	}
}

/**
 * Try to find absolute file name. If !local, libraryPath is used
 */
std::string v8cgi_App::findname(std::string name, bool forceLocal) {
	if (!name.length()) { return std::string(""); }

	/* try all these suffixes if file does not exist */
	const char * suffixes[] = {"js", "so", "dll"};
	
	/* try to fetch the Config.libraryPath option */
	v8::Handle<v8::Value> config = JS_GLOBAL->Get(JS_STR("Config"));
	v8::Handle<v8::Value> prefix = config->ToObject()->Get(JS_STR("libraryPath"));
	v8::String::Utf8Value pfx(prefix);

	std::string fullPath = "";
	if (path_isabsolute(name)) { /* v8cgi non-standard extension - absolute path */
		fullPath = name;
	} else { 
		if (!forceLocal && name.at(0) != '.') { /* "global" module */
			fullPath = std::string(*pfx);
		} else { /* "local" module */
			fullPath = this->paths.empty() ? path_getcwd() : this->paths.top();
		}
		fullPath += "/";
		fullPath += name;
	}

#ifdef VERBOSE
	printf("[findname] expanded to '%s'\n", fullPath.c_str()); 
#endif	

	fullPath = path_normalize(fullPath); /* remove /./, /../ etc */
	if (path_file_exists(fullPath)) { return fullPath; }
	
	std::string path2; /* try all suffixes */
	for (int j=0;j<3;j++) {
		path2 = fullPath;
		path2 += ".";
		path2 += suffixes[j];
		if (path_file_exists(path2)) { return path2; }
	}
	return std::string("");
}

/**
 * Load default libraries
 */
void v8cgi_App::autoload() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Value> config = JS_GLOBAL->Get(JS_STR("Config"));
	v8::Handle<v8::Array> list = v8::Handle<v8::Array>::Cast(config->ToObject()->Get(JS_STR("libraryAutoload")));
	int cnt = list->Length();
	v8::Handle<v8::Value> dummy;
	
	for (int i=0;i<cnt;i++) {
		v8::Handle<v8::Value> item = list->Get(JS_INT(i));
		v8::String::Utf8Value name(item);
		std::string filename = *name;
		this->include(filename, true, true); /* populate, wrap */
	}
}

/**
 * End request
 */
void v8cgi_App::finish() {
	v8::HandleScope handle_scope;
	/* user callbacks */
	for (unsigned int i=0; i<this->onexit.size(); i++) {
		this->onexit[i]->Call(JS_GLOBAL, 0, NULL);
		this->onexit[i].Dispose();
	}
	this->onexit.clear();

	/* garbage collection */
	this->gc.finish();
	
	/* export cache */
	exportmap::iterator expit;
	for (expit=this->exports.begin(); expit != this->exports.end(); expit++) {
		expit->second.Dispose();
	}
	this->exports.clear();
	
	/* paths */
	while (!this->paths.empty()) { this->paths.pop(); }
}

/**
 * Create global.response and global.request
 */
void v8cgi_App::http() {
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
		sys->Get(JS_STR("stdout"))
	};

	JS_GLOBAL->Set(JS_STR("response"), resf->NewInstance(1, resargs));
	JS_GLOBAL->Set(JS_STR("request"), reqf->NewInstance(2, reqargs));
}

/**
 * Try to locate main file
 */
void v8cgi_App::findmain() {
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
	
	if (!this->mainfile.length()) { throw std::string("Cannot locate main file."); }
}

/**
 * Initialize and setup the context
 */
void v8cgi_App::prepare(char ** envp) {
	v8::Handle<v8::Object> g = JS_GLOBAL;
	
	GLOBAL_PROTO->SetInternalField(0, v8::External::New((void *) this)); 
	GLOBAL_PROTO->SetInternalField(1, v8::External::New((void *) &(this->gc))); 

	g->Set(JS_STR("include"), v8::FunctionTemplate::New(_include)->GetFunction());
	g->Set(JS_STR("require"), v8::FunctionTemplate::New(_require)->GetFunction());
	g->Set(JS_STR("onexit"), v8::FunctionTemplate::New(_onexit)->GetFunction());
//	g->Set(JS_STR("exit"), v8::FunctionTemplate::New(_exit)->GetFunction());
	g->Set(JS_STR("global"), g);
	g->Set(JS_STR("Config"), v8::Object::New());

	setup_system(g, envp);
	setup_io(g);
	
	this->include(this->cfgfile, false, false); /* do not populate, do not wrap */
	this->autoload();
	
	v8::Handle<v8::Object> args = v8::Array::New();
	for (size_t i = 0; i < this->mainfile_args.size(); ++i) {
		args->Set(JS_INT(i), JS_STR(this->mainfile_args.at(i).c_str()));
	}
	g->Set(JS_STR("arguments"), args);
}

/**
 * Process command line arguments.
 * @returns {bool} True if we were able to (optionaly) set a config file and 
 * (non-optionally) set a mainfile. False if usage was invalid.
 */
void v8cgi_App::process_args(int argc, char ** argv) {
	std::string err = "Invalid command line usage.\n";
	err += "Correct usage: ";
	err += v8cgi_usage;

	// see the v8cgi_usage definition for the format
	
	// we must have at least one arg
	if (argc == 1) { throw err; }
	
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
	
	// we haven't found a mainfile yet, so there MUST be more arguments
	if (index >= argc) { throw err; }
	
	// Only the very next argument can be the "-c".  if it isn't
	// then set the cfgfile to the one passed in at compile time
	if (std::string(argv[index]) == "-c") {
		// make sure there is an argument after the "-c"
		if (index + 1 >= argc) { 
			throw err; 
		} else {
			++index; // skip over the "-c"
		}
		
		//printf("cfgfile: %s\n", argv[index]);
		this->cfgfile = argv[index];
		++index; // skip over the config file
	}

	// argv[index] MUST be the program_file.  If it doesn't
	// exist then we have an error.
	if (index >= argc) {
		throw err;
	} else {
		this->mainfile = argv[index];
		++index; // skip over the program_file
	}
	
	// all the rest of the arguments are arguments to the program_file
	for (; index < argc; ++index) {
		//printf("program_arg: %s\n", argv[index]);
		this->mainfile_args.push_back(std::string(argv[index]));
	}
}

/**
 * Default stdin routine
 */
size_t v8cgi_App::reader(char * destination, size_t amount) {
	return fread((void *) destination, sizeof(char), amount, stdin);
}

/**
 * Default stdout routine
 */
size_t v8cgi_App::writer(const char * data, size_t amount) {
	return fwrite((void *) data, sizeof(char), amount, stdout);
}

/**
 * Default stderr routine
 */
void v8cgi_App::error(const char * data, const char * file, int line) {
	fwrite((void *) data, sizeof(char), strlen(data), stderr);
	fwrite((void *) "\n", sizeof(char), 1, stderr);
}
