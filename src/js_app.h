/*
 * v8cgi app file. Loosely based on V8's "shell" sample app.
 */

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
	virtual ~v8cgi_App() {};
	int init(int argc, char ** argv); /* once per app lifetime */
	int execute(char ** envp, bool change); /* once per request */
	v8::Handle<v8::Value> include(std::string name, bool populate, bool forceLocal);
	
	typedef std::vector<v8::Persistent<v8::Function> > funcvector;
	typedef std::stack<std::string> pathstack;
	typedef std::map<std::string, v8::Persistent<v8::Value> > exportmap;
	exportmap exports;	/* list of cached exports */
	funcvector onexit;	/* list of "onexit" functions */
	pathstack paths;	/* stack of current paths */ 

	virtual size_t reader (char * destination, size_t size); /* stdin */
	virtual size_t writer (const char * source, size_t size); /* stdout */
	virtual void error(const char * data, const char * file, int line); /* stderr */

private:
	std::string cfgfile; /* config file */
	std::string mainfile; /* command-line specified file */
	std::vector<std::string> mainfile_args; /* arguments after mainfile */
	Cache cache;
	GC gc;

	std::string exception(v8::TryCatch* try_catch);
	virtual void process_args(int argc, char ** argv);
	void prepare(char ** envp);
	void findmain();
	void finish();
	void http();
	void js_error(std::string message);
	void autoload();
	
	std::string findname(std::string name, bool forceLocal);
	void populate_global(v8::Handle<v8::Object> exports);
	std::string wrap(std::string original);
	v8::Handle<v8::Value> include_js(std::string filename, bool wrap);
	v8::Handle<v8::Value> include_dso(std::string filename);
};

#endif
