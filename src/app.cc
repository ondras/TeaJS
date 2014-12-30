/**
 * TeaJS app file. This class represents generic V8 embedding; cgi binary and apache module inherit from it.
 */

#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <v8.h>

#ifdef FASTCGI
#	include <fcgi_stdio.h>
#endif

#include "app.h"
#include "system.h"
#include "macros.h"
#include "cache.h"
#include "path.h"

#ifndef windows
#	include <dlfcn.h>
#else
#	include <windows.h>
#	define dlsym(x, y) GetProcAddress((HMODULE)x, y)
#endif

/**
 * global.require = load module and return its (cached) exports
 */
JS_METHOD(_require) {
	TeaJS_App * app = APP_PTR;
	v8::String::Utf8Value file(args[0]);
	std::string root = *(v8::String::Utf8Value(args.Data()));
	
	try {
		v8::Persistent<v8::Value> required;
		required.Reset(JS_ISOLATE, app->require(*file, root));
		args.GetReturnValue().Set(required);
	} catch (std::string e) {
		JS_ERROR(e.c_str());
	}
}

/**
 * global.onexit = add a function to be executed when context ends
 */
JS_METHOD(_onexit) {
	TeaJS_App * app = APP_PTR;
	if (!args[0]->IsFunction()) { JS_TYPE_ERROR("Non-function passed to onexit()"); return; }
	v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function> > fun;
	fun.Reset(JS_ISOLATE, v8::Handle<v8::Function>::Cast(args[0]));
	app->onexit.push_back(fun);
	args.GetReturnValue().SetUndefined();
}

/**
 * global.exit - terminate execution
 */
JS_METHOD(_exit) {
	TeaJS_App * app = APP_PTR;
	if (args.Length() > 0) {
		app->exit_code = args[0]->IntegerValue();
	} else {
		app->exit_code = 1;
	}

	v8::V8::TerminateExecution(JS_ISOLATE);
	/* do something at least a bit complex so the stack guard can throw the termination exception */
	v8::Script::Compile(JS_STR("(function(){})()"))->Run();
	args.GetReturnValue().SetUndefined();
}

/**
 * To be executed only once - initialize stuff
 */
void TeaJS_App::init() {
	this->cfgfile = STRING(CONFIG_PATH);
	this->show_errors = false;
	this->exit_code = 0;

	v8::V8::InitializeICU();
	v8::V8::Initialize();

	this->isolate = v8::Isolate::New();
	this->isolate->Enter();
}

/**
 * Initialize and setup the context. Executed during every request, prior to executing main request file.
 */
void TeaJS_App::prepare(char ** envp) {
	v8::HandleScope handle_scope(JS_ISOLATE);
	v8::Handle<v8::Object> g = JS_GLOBAL;

	std::string root = path_getcwd();
	/* FIXME it might be better NOT to expose this to global
	g->Set(JS_STR("require"), v8::FunctionTemplate::New(_require, JS_STR(root.c_str()))->GetFunction());
	*/
	g->Set(JS_STR("onexit"), v8::FunctionTemplate::New(JS_ISOLATE, _onexit)->GetFunction());
	g->Set(JS_STR("exit"), v8::FunctionTemplate::New(JS_ISOLATE, _exit)->GetFunction());
	g->Set(JS_STR("global"), g);

	this->paths.Reset(JS_ISOLATE, v8::Array::New(JS_ISOLATE));
	v8::Local<v8::Array> paths = v8::Local<v8::Array>::New(JS_ISOLATE, this->paths);

	/* config file */
	v8::Local<v8::Object> config =
			v8::Local<v8::Object>::New(JS_ISOLATE, this->require(path_normalize(this->cfgfile), path_getcwd()));

	if (!paths->Length()) {
		std::string error = "require.paths is empty, have you forgotten to push some data there?";
		throw error;
	}
	
	g->Set(JS_STR("Config"), config->Get(JS_STR("Config")));

	setup_teajs(g);
	setup_system(g, envp, this->mainfile, this->mainfile_args);
}

/**
 * Process a request.
 * @param {char**} envp Environment
 */
void TeaJS_App::execute(char ** envp) {
	v8::Locker locker(JS_ISOLATE);
	v8::HandleScope handle_scope(JS_ISOLATE);

	std::string caught;
	this->create_context();
	this->mainModule.Reset(JS_ISOLATE, v8::Object::New(JS_ISOLATE));

	try {
		v8::TryCatch tc;

		this->prepare(envp);
		if (tc.HasCaught()) { throw this->format_exception(&tc); } /* uncaught exception when loading config file */
		
		if (this->mainfile == "") { throw std::string("Nothing to do :)"); }

		this->require(this->mainfile, path_getcwd()); 
		
		if (tc.HasCaught() && tc.CanContinue()) { throw this->format_exception(&tc); } /* uncaught exception when executing main file */

	} catch (std::string e) {
		this->exit_code = 1;
		caught = e;
	}
	
	this->finish();
	
	if (caught.length()) { throw caught; } /* rethrow */
}

/**
 * End request
 */
void TeaJS_App::finish() {
	v8::Handle<v8::Value> show = this->get_config("showErrors");
	this->show_errors = show->ToBoolean()->IsTrue();

	/* user callbacks */
	for (unsigned int i=0; i<this->onexit.size(); i++) {
		v8::Local<v8::Function> onexit = v8::Local<v8::Function>::New(JS_ISOLATE, this->onexit[i]);
		onexit->Call(JS_GLOBAL, 0, NULL);
		this->onexit[i].Reset();
	}
	this->onexit.clear();

	/* garbage collection */
	this->gc.finish();
	
	/* export cache */
	this->cache.clearExports();
	
	this->delete_context();
}

/**
 * Require a module.
 * @param {std::string} name
 * @param {std::string} relativeRoot module root for relative includes
 */
v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object> > TeaJS_App::require(std::string name, std::string relativeRoot) {
	v8::HandleScope hs(JS_ISOLATE);
#ifdef VERBOSE
	printf("[require] looking for '%s'\n", name.c_str()); 
#endif	
	modulefiles files = this->resolve_module(name, relativeRoot);
	
	if (!files.size()) { 
		std::string error = "Cannot find module '";
		error += name;
		error += "'";
		throw error;
	}

#ifdef VERBOSE
	printf("[require] resolved as '%s' (%d files)\n", files[0].c_str(), files.size()); 
#endif	

	/* module name is the first component => hybrid modules are indexed by their native part */
	std::string modulename = files[0];
	modulename = modulename.substr(0,  modulename.find_last_of('.'));

	v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object> > exports = this->cache.getExports(modulename);
	/* check if exports are cached */
	if (!exports.IsEmpty()) { return exports; }
	
	/* create module-specific require */
	v8::Handle<v8::Function> require = this->build_require(modulename, _require);

	/* add new blank exports to cache */
	v8::Handle<v8::Object> _exports = v8::Object::New(JS_ISOLATE);
	this->cache.addExports(modulename, _exports);

	/* create/use the "module" variable" */
	v8::Handle<v8::Object> module =
			(name == this->mainfile ? v8::Local<v8::Object>::New(JS_ISOLATE, this->mainModule) : v8::Object::New(JS_ISOLATE));
	module->Set(JS_STR("id"), JS_STR(modulename.c_str()));

	int status = 0;
	for (unsigned int i=0; i<files.size(); i++) {
		std::string file = files[i];
		std::string ext = file.substr(file.find_last_of('.')+1, std::string::npos);
		if (ext == STRING(DSO_EXT)) {
			this->load_dso(file, require, _exports, module);
		} else {
			status = this->load_js(file, require, _exports, module);
			if (status != 0) {
				this->cache.removeExports(modulename);
				exports.Reset(JS_ISOLATE, _exports);
				return exports;
			}
		}
		
	}

	exports.Reset(JS_ISOLATE, _exports);
	return exports;
}

/**
 * Include a js module
 */
int TeaJS_App::load_js(std::string filename, v8::Handle<v8::Function> require, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module) {
	v8::HandleScope handle_scope(JS_ISOLATE);

	/* compiled script wrapped in anonymous function */
	v8::Local<v8::Script> script = v8::Local<v8::Script>::New(JS_ISOLATE, this->cache.getScript(filename));

	if (script.IsEmpty()) { return 1; } /* compilation error? */
	/* run the script, no error should happen here */
	v8::Handle<v8::Value> wrapped = script->Run();

	v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(wrapped);
	v8::Handle<v8::Value> params[3] = {require, exports, module}; 
	v8::Handle<v8::Value> result = fun->Call(exports, 3, params);
	
	return (result.IsEmpty() ? 1 : 0);
}

/**
 * Include a DSO module
 */
void TeaJS_App::load_dso(std::string filename, v8::Handle<v8::Function> require, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module) {
	v8::HandleScope handle_scope(JS_ISOLATE);
	void * handle = this->cache.getHandle(filename);;
	
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
 * Fully expand/resolve module name
 */
TeaJS_App::modulefiles TeaJS_App::resolve_module(std::string name, std::string relativeRoot) {
	if (!name.length()) { return modulefiles(); }

	if (path_isabsolute(name)) {
		/* TeaJS non-standard extension - absolute path */
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
		v8::Local<v8::Array> arr = v8::Local<v8::Array>::New(JS_ISOLATE, this->paths);
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
TeaJS_App::modulefiles TeaJS_App::resolve_extension(std::string path) {
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
		if (path_file_exists(path2)) { 
			result.push_back(path2); 
#ifdef VERBOSE
			printf("[resolve_extension] extension found '%s'\n", path2.c_str()); 
#endif	
		}
	}

	/* if the path already exists (extension to commonjs modules 1.1), use it */
	if (!result.size() && path_file_exists(fullPath)) { result.push_back(fullPath); }
	
	return result;
}

/** 
 * Convert JS exception to c string 
 */
std::string TeaJS_App::format_exception(v8::TryCatch* try_catch) {
	v8::HandleScope handle_scope(JS_ISOLATE);
	v8::String::Utf8Value exception(try_catch->Exception());
	v8::Handle<v8::Message> message = try_catch->Message();
	std::string msgstring = "";
	std::stringstream ss;

	if (message.IsEmpty()) {
		msgstring += *exception;
	} else {
		v8::String::Utf8Value filename(message->GetScriptResourceName());
		int linenum = message->GetLineNumber();
		msgstring += *exception;
		msgstring += " (";
		msgstring += *filename;
		msgstring += ":";
		ss << linenum;
		msgstring += ss.str();
		msgstring += ")";
		
		v8::Handle<v8::Value> stack = try_catch->StackTrace();
		if (!stack.IsEmpty()) {
			v8::String::Utf8Value sstack(stack);
			msgstring += "\n";
			msgstring += *sstack;
		}
	}
	return msgstring;
}

/**
 * Creates a new context
 */
void TeaJS_App::create_context() {
	v8::HandleScope handle_scope(JS_ISOLATE);

	if (this->global.IsEmpty()) { /* first time */
		v8::Local<v8::ObjectTemplate> globalt = v8::ObjectTemplate::New(JS_ISOLATE);
		globalt->SetInternalFieldCount(2);
		this->globalt.Reset(JS_ISOLATE, globalt);

		v8::Local<v8::Context> context = v8::Context::New(JS_ISOLATE, NULL, globalt);
		context->Enter();
		this->context.Reset(JS_ISOLATE, context);

		this->global.Reset(JS_ISOLATE, JS_GLOBAL);
	} else { /* Nth time */
#ifdef REUSE_CONTEXT
		v8::Local<v8::Context> context = v8::Local<v8::Context>::New(JS_ISOLATE, this->context);
		context->Enter();
		this->clear_global(); /* reuse - just clear */
#else
		v8::Local<v8::ObjectTemplate> globalt = v8::Local<v8::ObjectTemplate>::New(JS_ISOLATE, this->globalt);
		v8::Local<v8::Value> global = v8::Local<v8::Value>::New(JS_ISOLATE, this->global);
		v8::Local<v8::Context> context = v8::Context::New(JS_ISOLATE, NULL, globalt, global);
		context->Enter();
		this->context.Reset(JS_ISOLATE, context);
#endif
	}
	GLOBAL_PROTO->SetInternalField(0, v8::External::New(JS_ISOLATE, (void *) this));
	GLOBAL_PROTO->SetInternalField(1, v8::External::New(JS_ISOLATE, (void *) &(this->gc)));

}

/**
 * Deletes the existing context
 */
void TeaJS_App::delete_context() {
	v8::Local<v8::Context> context = v8::Local<v8::Context>::New(JS_ISOLATE, this->context);
	context->Exit();
#ifndef REUSE_CONTEXT
	this->context.Reset();
#endif
}

/**
 * Removes all "garbage" from the global object
 */
void TeaJS_App::clear_global() {
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
v8::Handle<v8::Value> TeaJS_App::get_config(std::string name) {
	v8::Handle<v8::Value> config = JS_GLOBAL->Get(JS_STR("Config"));
	if (!config->IsObject()) { return JS_UNDEFINED; }
	return config->ToObject()->Get(JS_STR(name.c_str()));
}

/**
 * Build module-specific require
 */
v8::Handle<v8::Function> TeaJS_App::build_require(std::string path, void (*func) (const v8::FunctionCallbackInfo<v8::Value>&)) {
	std::string root = path_dirname(path);
	v8::Handle<v8::FunctionTemplate> requiretemplate = v8::FunctionTemplate::New(JS_ISOLATE, func, JS_STR(root.c_str()));
	v8::Handle<v8::Function> require = requiretemplate->GetFunction();
	v8::Local<v8::Array> paths = v8::Local<v8::Array>::New(JS_ISOLATE, this->paths);
	require->Set(JS_STR("paths"), paths);
	v8::Local<v8::Object> mainModule = v8::Local<v8::Object>::New(JS_ISOLATE, this->mainModule);
	require->Set(JS_STR("main"), mainModule);
	return require;
}

void TeaJS_App::setup_teajs(v8::Handle<v8::Object> target) {
	v8::HandleScope handle_scope(JS_ISOLATE);
	
	v8::Handle<v8::Object> teajs = v8::Object::New(JS_ISOLATE);
	teajs->Set(JS_STR("version"), JS_STR(STRING(VERSION)));
	teajs->Set(JS_STR("instanceType"), JS_STR(this->instanceType()));
	teajs->Set(JS_STR("executableName"), JS_STR(this->executableName()));
	
	target->Set(JS_STR("TeaJS"), teajs);
	target->Set(JS_STR("v8cgi"), teajs);
}
