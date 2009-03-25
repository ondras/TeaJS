/*
 * v8cgi app file. Loosely based on V8's "shell" sample app.
 */

#ifndef _JS_APP_H
#define _JS_APP_H

#include <map>
#include <stack>
#include <vector>
#include <v8.h>
#include "js_cache.h"

class v8cgi_App {
public:
	virtual ~v8cgi_App() {};
	int init(int argc, char ** argv);
	int execute(char ** envp, bool change);
	int include(std::string str, bool populate);
	v8::Handle<v8::Value> require(std::string str, bool wrap);
	
	typedef std::vector<v8::Persistent<v8::Function> > funcvector;
	typedef std::stack<std::string> pathstack;
	typedef std::map<std::string, v8::Persistent<v8::Value> > exportmap;
	exportmap exports;
	funcvector onexit;
	pathstack paths;

	virtual size_t reader (char * destination, size_t size);
	virtual size_t writer (const char * source, size_t size);
	virtual void error(const char * data, const char * file, int line);

private:
	std::string cfgfile; /* config file */
	std::string mainfile; /* command-line specified file */
	std::vector<std::string> mainfile_args; /* arguments after mainfile */
	std::string cwd;
	Cache cache;

	virtual bool process_args(int argc, char ** argv);
	int prepare(char ** envp);
	int process();
	int findmain();
	void finish();
	void http();
	void report_error(const char * message);
	void exception(v8::TryCatch* try_catch);
	int autoload();
	
	std::string findname(std::string name);
	void populate_global(v8::Handle<v8::Object> exports);
	std::string wrap(std::string original);
	v8::Handle<v8::Value> include_js(std::string filename, bool wrap);
	v8::Handle<v8::Value> include_dso(std::string filename);
};

#endif
