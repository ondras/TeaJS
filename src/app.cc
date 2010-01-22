/**
 * v8cgi app file. This class represents generic V8 embedding; cgi binary and apache module inherit from it.
 */

#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <v8.h>

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include "app.h"
#include "system.h"
#include "io.h"
#include "macros.h"
#include "cache.h"
#include "path.h"

#ifndef windows
#   include <dlfcn.h>
#else
#   include <windows.h>
#	define dlsym(x, y) GetProcAddress((HMODULE)x, y)
#endif

/**
 * global.include = global.require + populate global object
 */
JS_METHOD(_include) {
	v8cgi_App * app = APP_PTR;
	v8::String::Utf8Value file(args[0]);
	v8::Handle<v8::Object> exports;
	try {
		exports = app->include(*file);
	} catch (std::string e) {
		return JS_EXCEPTION(e.c_str());
	}
	return exports;
}

/**
 * global.require = load module and return its (cached) exports
 */
JS_METHOD(_require) {
	v8cgi_App * app = APP_PTR;
	v8::String::Utf8Value file(args[0]);
	v8::Handle<v8::Object> exports;
	std::string root = *(v8::String::Utf8Value(args.Data()));
	try {
		exports = app->require(*file, root);
	} catch (std::string e) {
		return JS_EXCEPTION(e.c_str());
	}
	return exports;
}

/**
 * global.onexit = add a function to be executed when context ends
 */
JS_METHOD(_onexit) {
	v8cgi_App * app = APP_PTR;
	if (!args[0]->IsFunction()) { return JS_EXCEPTION("Non-function passed to onexit()"); }
	v8::Persistent<v8::Function> fun = v8::Persistent<v8::Function>::New(v8::Handle<v8::Function>::Cast(args[0]));
	app->onexit.push_back(fun);
	return v8::Undefined();
}

/**
 * global.exit - terminate execution
 */
JS_METHOD(_exit) {
	v8cgi_App * app = APP_PTR;
	app->terminated = true;
	v8::V8::TerminateExecution();
	
	/* do something at least a bit complex so the stack guard can throw the termination exception */
	v8::Handle<v8::String> source = JS_STR("(function(){})()");
	v8::Script::Compile(source)->Run();

	return v8::Undefined();
}

/**
 * To be executed only once - initialize stuff
 */
void v8cgi_App::init() {
	this->cfgfile = STRING(CONFIG_PATH);

	/**
	 * Reusable context is created only once, here.
 	 */
#ifdef REUSE_CONTEXT
	this->create_context();
#endif
}

/**
 * Initialize and setup the context. Executed during every request, prior to executing main request file.
 */
void v8cgi_App::prepare(char ** envp) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Object> g = JS_GLOBAL;

	std::string root = path_getcwd();
	g->Set(JS_STR("include"), v8::FunctionTemplate::New(_include)->GetFunction());
	g->Set(JS_STR("require"), v8::FunctionTemplate::New(_require, JS_STR(root.c_str()))->GetFunction());
	g->Set(JS_STR("onexit"), v8::FunctionTemplate::New(_onexit)->GetFunction());
	g->Set(JS_STR("exit"), v8::FunctionTemplate::New(_exit)->GetFunction());
	g->Set(JS_STR("global"), g);
	g->Set(JS_STR("Config"), v8::Object::New());
	
	this->paths = v8::Persistent<v8::Array>::New(v8::Array::New());

	setup_v8cgi(g);
	setup_system(g, envp, this->mainfile, this->mainfile_args);
	setup_io(g);

	/* config file */
	this->include(path_normalize(this->cfgfile)); 
	
	/* default libraries */
	this->autoload();
}

/**
 * Load default libraries
 */
void v8cgi_App::autoload() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Value> config = JS_GLOBAL->Get(JS_STR("Config"));
	v8::Handle<v8::Array> list = v8::Handle<v8::Array>::Cast(this->get_config("libraryAutoload"));
	int cnt = list->Length();
	v8::Handle<v8::Value> dummy;
	
	for (int i=0;i<cnt;i++) {
		v8::Handle<v8::Value> item = list->Get(JS_INT(i));
		v8::String::Utf8Value name(item);
		std::string filename = *name;
		this->include(filename);
	}
}

/**
 * Process a request.
 * @param {char**} envp Environment
 */
int v8cgi_App::execute(char ** envp) {
	v8::HandleScope handle_scope;
	
	/**
	 * Context must be clened before reusing
	 */
#ifdef REUSE_CONTEXT
	this->clear_global();
#else
	/**
	 * No reusing -> new context 
	 */
	this->create_context();
#endif

	this->terminated = false;

	try {
		/* prepare JS environment: config, default libraries */
		this->prepare(envp); 
	} catch (std::string e) {
		/* error with config file or default libs -> goes to stderr */
		this->error(e.c_str(), __FILE__, __LINE__); 
		this->finish();
		return 1;
	}
	
	/* setup builtin request and response, if running as CGI */
	if (this->http()) {
		/* do we have a forced http handler? */
		v8::Handle<v8::Value> handler = this->get_config("httpHandler");
		if (handler->ToBoolean()->IsTrue()) {
			v8::String::Utf8Value name(handler);
			this->mainfile = *name;
		}
	}

	try {
		/* require the mainfile */
		this->require(this->mainfile, path_getcwd()); 
	} catch (std::string e) {
		/* error when executing main file */
		v8::Handle<v8::Value> show = this->get_config("showErrors");
		if (show->ToBoolean()->IsTrue()) {
			this->js_error(e.c_str()); 
		} else {
			this->error(e.c_str(), __FILE__, __LINE__);
		}
		this->finish();
		return 1;
	}
	
	this->finish();
	return 0;
}

/**
 * End request
 */
void v8cgi_App::finish() {
	/* user callbacks */
	for (unsigned int i=0; i<this->onexit.size(); i++) {
		this->onexit[i]->Call(JS_GLOBAL, 0, NULL);
		this->onexit[i].Dispose();
		this->onexit[i].Clear();
	}
	this->onexit.clear();

	/* garbage collection */
	this->gc.finish();
	
	/* export cache */
	this->cache.clearExports();
	
#ifndef REUSE_CONTEXT
	/**
	 * Delete current context
	 */
	this->delete_context();
#endif
}

/**
 * To include a module, we first require it and than populate global object with retrieved data
 * @param {std::string} name
 */
v8::Handle<v8::Object> v8cgi_App::include(std::string name) {
	v8::HandleScope handle_scope;

	v8::Handle<v8::Object> exports = this->require(name, path_getcwd());
	v8::Handle<v8::Array> names = exports->GetPropertyNames();
	for (unsigned i=0;i<names->Length();i++) {
		v8::Handle<v8::Value> name = names->Get(JS_INT(i));
		JS_GLOBAL->Set(name, exports->Get(name));		
	}

	return handle_scope.Close(exports);
}

/**
 * Require a module
 * @param {std::string} name
 * @param {std::string} relativeRoot module root for relative includes
 */
v8::Handle<v8::Object> v8cgi_App::require(std::string name, std::string relativeRoot) {
	v8::HandleScope handle_scope;
#ifdef VERBOSE
	printf("[require] looking for '%s'\n", name.c_str()); 
#endif	
	modulefiles files = this->resolve_module(name, relativeRoot);
	
	if (!files.size()) {
		std::string s = "Cannot find module '";
		s += name;
		s += "'";
		throw s;
	}

#ifdef VERBOSE
	printf("[require] resolved as '%s' (%d files)\n", files[0].c_str(), files.size()); 
#endif	

	/* module name is the first component => hybrid modules are indexed by their native part */
	std::string modulename = files[0];
	modulename = modulename.substr(0,  modulename.find_last_of('.'));
	
	v8::Handle<v8::Object> exports = this->cache.getExports(modulename);
	/* check if exports are cached */
	if (!exports.IsEmpty()) { return exports; }
	
	/* create module-specific require */
	v8::Handle<v8::Function> require = this->build_require(modulename);

	/* add new blank exports to cache */
	exports = v8::Object::New();
	this->cache.addExports(modulename, exports);

	/* create the "module" variable" */
	v8::Handle<v8::Object> module = v8::Object::New();
	module->Set(JS_STR("id"), JS_STR(modulename.c_str()));

	try {
		for (unsigned int i=0; i<files.size(); i++) {
			std::string file = files[i];
			std::string ext = file.substr(file.find_last_of('.')+1, std::string::npos);
			if (ext == STRING(DSO_EXT)) {
				this->load_dso(file, require, exports, module);
			} else {
				this->load_js(file, require, exports, module);
			}
		}
	} catch (std::string e) {
		/* remove from export cache */
		this->cache.removeExports(modulename);
		/* rethrow */
		throw e; 
	}

	return handle_scope.Close(exports);
}

/**
 * Include a js module
 */
void v8cgi_App::load_js(std::string filename, v8::Handle<v8::Function> require, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module) {
	v8::HandleScope handle_scope;
	v8::TryCatch tc;

	/* compiled script wrapped in anonymous function */
	v8::Handle<v8::Script> script = this->cache.getScript(filename);
	
	/* compilation error? */
	if (tc.HasCaught()) {
		throw this->format_exception(&tc);
	} else {
		/* run the script, no error should happen here */
		v8::Handle<v8::Value> result = script->Run();

		v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(result);
		v8::Handle<v8::Value> params[3] = {require, exports, module}; 
		result = fun->Call(exports, 3, params);

		/* runtime error in inner code */
		if (tc.HasCaught() && !this->terminated) { throw this->format_exception(&tc); }
	}
}

/**
 * Include a DSO module
 */
void v8cgi_App::load_dso(std::string filename, v8::Handle<v8::Function> require, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module) {
	v8::HandleScope handle_scope;
	void * handle = this->cache.getHandle(filename);

	typedef void (*init_t)(v8::Handle<v8::Function>, v8::Handle<v8::Object>, v8::Handle<v8::Object>);

	init_t func = (init_t) dlsym(handle, "init");	
	
	if (!func) {
		std::string error = "Cannot initialize shared library '";
		error += filename;
		error += "'";
		throw error;
	}
	
	func(require, exports, module);
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
		if (print->IsFunction()) {
			fun = v8::Local<v8::Function>::Cast(print);
			cgi = 1;
		}
	}
	if (!cgi) {
		context = JS_GLOBAL->Get(JS_STR("system"));
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
 * Fully expand/resolve module name
 */
v8cgi_App::modulefiles v8cgi_App::resolve_module(std::string name, std::string relativeRoot) {
	if (!name.length()) { return modulefiles(); }

	if (path_isabsolute(name)) {
		/* v8cgi non-standard extension - absolute path */
#ifdef VERBOSE
		printf("[resolve_module] expanded to '%s'\n", name.c_str()); 
#endif	
		return this->resolve_extension(name);
	} else if (name.at(0) == '.') {
		/* local module, relative to current path */
		std::string path = relativeRoot;
		path += "/";
		path += name;
#ifdef VERBOSE
		printf("[resolve_module] expanded to '%s'\n", path.c_str()); 
#endif	
		return this->resolve_extension(path);
	} else {
		/* convert to array of search paths */
		v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(this->paths);
		int length = arr->Length();
		v8::Handle<v8::Value> prefix;
		modulefiles result;
		
		for (int i=0;i<length;i++) {
			prefix = arr->Get(JS_INT(i));
			v8::String::Utf8Value pfx(prefix);
			std::string path(*pfx);
			path += "/";
			path += name;
#ifdef VERBOSE
		printf("[resolve_module] expanded to '%s'\n", path.c_str()); 
#endif	
			result = this->resolve_extension(path);
			if (result.size()) { return result; }
		}
		
		return modulefiles();
	}
}

/**
 * Try to adjust file's extension in order to locate an existing file
 */
v8cgi_App::modulefiles v8cgi_App::resolve_extension(std::string path) {
	/* remove /./, /../ etc */
	std::string fullPath = path_normalize(path); 
	modulefiles result;
	
	/* first, try suffixes */
	const char * suffixes[] = {STRING(DSO_EXT), "js"};
	std::string path2; 
	for (int j=0;j<2;j++) {
		path2 = fullPath;
		path2 += ".";
		path2 += suffixes[j];
		if (path_file_exists(path2)) { result.push_back(path2); }
	}

	/* if the path already exists (extension to commonjs modules 1.1), use it */
	if (!result.size() && path_file_exists(fullPath)) { result.push_back(fullPath); }
	
	return result;
}

/**
 * Create global.response and global.request
 */
bool v8cgi_App::http() {
	v8::Handle<v8::Object> sys = JS_GLOBAL->Get(JS_STR("system"))->ToObject();
	v8::Handle<v8::Value> env = sys->ToObject()->Get(JS_STR("env"));
	v8::Handle<v8::Value> ss = env->ToObject()->Get(JS_STR("SERVER_SOFTWARE"));
	if (!ss->IsString()) { return false; }
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
	return true;
}

/** 
 * Convert JS exception to c string 
 */
std::string v8cgi_App::format_exception(v8::TryCatch* try_catch) {
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
 * Creates a new context
 */
void v8cgi_App::create_context() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::ObjectTemplate> globaltemplate = v8::ObjectTemplate::New();
	globaltemplate->SetInternalFieldCount(2);
	this->context = v8::Context::New(NULL, globaltemplate);
	this->context->Enter();

	GLOBAL_PROTO->SetInternalField(0, v8::External::New((void *) this)); 
	GLOBAL_PROTO->SetInternalField(1, v8::External::New((void *) &(this->gc))); 
}

/**
 * Deletes the existing context
 */
void v8cgi_App::delete_context() {
	this->context->Exit();
	this->context.Dispose();
	this->context.Clear();
}

/**
 * Removes all "garbage" from the global object
 */
void v8cgi_App::clear_global() {
	v8::Handle<v8::Array> keys = JS_GLOBAL->GetPropertyNames();
	int length = keys->Length();
	for (int i=0;i<length;i++) {
		v8::Handle<v8::String> key = keys->Get(JS_INT(i))->ToString();
		JS_GLOBAL->ForceDelete(key);
	}
}

/**
 * Retrieve a configuration value
 */
v8::Handle<v8::Value> v8cgi_App::get_config(std::string name) {
	v8::Handle<v8::Value> config = JS_GLOBAL->Get(JS_STR("Config"));
	return config->ToObject()->Get(JS_STR(name.c_str()));
}

/**
 * Build module-specific require
 */
v8::Handle<v8::Function> v8cgi_App::build_require(std::string path) {
	std::string root = path_dirname(path);
	v8::Handle<v8::FunctionTemplate> requiretemplate = v8::FunctionTemplate::New(_require, JS_STR(root.c_str()));
	v8::Handle<v8::Function> require = requiretemplate->GetFunction();
	require->Set(JS_STR("paths"), this->paths);
	return require;
}

void v8cgi_App::setup_v8cgi(v8::Handle<v8::Object> target) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Object> v8cgi = v8::Object::New();
	
	v8cgi->Set(JS_STR("version"), JS_STR(STRING(VERSION)));
	v8cgi->Set(JS_STR("instanceType"), JS_STR(this->instanceType()));
	v8cgi->Set(JS_STR("executableName"), JS_STR(this->executableName()));
	
	target->Set(JS_STR("v8cgi"), v8cgi);
}
