#ifndef _JS_APP_H
#define _JS_APP_H

#include <map>
#include <stack>
#include <vector>
#include <list>
#include <v8.h>
#include "js_cache.h"
#include "js_gc.h"

class v8cgi_App {
public:
	typedef std::vector<v8::Persistent<v8::Function> > funcvector;
	typedef std::stack<std::string> pathstack;
	typedef std::map<std::string, v8::Persistent<v8::Object> > exportmap;

	virtual ~v8cgi_App() {};
	virtual int init(int argc, char ** argv); /* once per app lifetime */
	int execute(bool change, char ** envp); /* once per request */
	v8::Handle<v8::Object> include(std::string name);
	v8::Handle<v8::Object> require(std::string name, bool wrap);
	
	funcvector onexit;	/* list of "onexit" functions */

	virtual size_t reader (char * destination, size_t size); /* stdin */
	virtual size_t writer (const char * source, size_t size); /* stdout */
	virtual void error(const char * data, const char * file, int line); /* stderr */

protected:
	std::string cfgfile; /* config file */
	void create_context();
	void delete_context();

private:
	v8::Persistent<v8::Context> context; /* current active context */
	std::string mainfile; /* command-line specified file */
	std::vector<std::string> mainfile_args; /* arguments after mainfile */
	Cache cache;
	GC gc;

	exportmap exports;	/* list of cached exports */
	pathstack paths;	/* stack of current paths */ 

	std::string format_exception(v8::TryCatch* try_catch);
	virtual void process_args(int argc, char ** argv);
	void prepare(char ** envp);
	void findmain();
	void finish();
	void http();
	void js_error(std::string message);
	void autoload();
	void clear_global();
	
	std::string findname(std::string name, bool forceLocal);
	v8::Handle<v8::Value> load_js(std::string filename, v8::Handle<v8::Object> exports, bool wrap);
	v8::Handle<v8::Value> load_dso(std::string filename, v8::Handle<v8::Object> exports);
};

#endif
