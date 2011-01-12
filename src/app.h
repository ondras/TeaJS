#ifndef _JS_APP_H
#define _JS_APP_H

#include <map>
#include <utility>
#include <vector>
#include <list>
#include <v8.h>
#include "cache.h"
#include "gc.h"

/**
 * This class defines a basic v8-based application.
 */
class v8cgi_App {
public:
	typedef std::vector<v8::Persistent<v8::Function> > funcvector;
	
	/* resolved native module, resolved js module */
	typedef std::vector<std::string> modulefiles;

	virtual ~v8cgi_App() {};
	/* once per app lifetime */
	virtual void init(); 
	/* once per request */
	int execute(char ** envp); 
	v8::Handle<v8::Object> include(std::string name, std::string moduleId);
	v8::Handle<v8::Object> require(std::string name, std::string moduleId);
	
	/* termination mark. if present, termination exception is not handled */
	bool terminated;

	/* list of "onexit" functions */
	funcvector onexit;

	/* stdin */
	virtual size_t reader (char * destination, size_t size) = 0;
	/* stdout */
	virtual size_t writer (const char * source, size_t size) = 0;
	/* stderr */
	virtual void error(const char * data, const char * file, int line) = 0;
	/* stdout flush */
	virtual bool flush() = 0;	

protected:
	/* env. preparation */
	virtual int prepare(char ** envp);

	/* config file */
	std::string cfgfile;
	/* main script file */
	std::string mainfile; 
	/* arguments after mainfile */
	std::vector<std::string> mainfile_args;
	/* create new v8 execution context */
	void create_context();
	/* delete existing context */
	void delete_context();
	/* setup the v8cgi free variable */
	void setup_v8cgi(v8::Handle<v8::Object> target);

private:
	/* current active context */
	v8::Persistent<v8::Context> context; 
	
	v8::Persistent<v8::Value> global;
	v8::Persistent<v8::ObjectTemplate> globalt;
	
	/* cache */
	Cache cache;
	/* GC notification engine */
	GC gc;

	std::string format_exception(v8::TryCatch* try_catch);
	void findmain();
	void finish();
	bool http();
	void js_error(std::string message);
	void autoload();
	void clear_global();
	
	/* instance type info */
	virtual const char * instanceType() = 0;

	/* instance type info */
	virtual const char * executableName() = 0;

	modulefiles resolve_module(std::string name, std::string relativeRoot);
	modulefiles resolve_extension(std::string path);
	int load_js(std::string filename, v8::Handle<v8::Function> require, v8::Handle<v8::Function> include, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module);
	int load_dso(std::string filename, v8::Handle<v8::Function> require, v8::Handle<v8::Function> include, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module);
	v8::Handle<v8::Value> get_config(std::string name);
	v8::Handle<v8::Function> build_require(std::string path, v8::Handle<v8::Value> (*func) (const v8::Arguments&));
	
	v8::Persistent<v8::Array> paths; /* require.paths */
	v8::Local<v8::Object> mainModule;
};

#endif
