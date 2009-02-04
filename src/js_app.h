/*
 * v8cgi app file. Loosely based on V8's "shell" sample app.
 */

#ifndef _JS_APP_H
#define _JS_APP_H

#include <v8.h>
#include "js_cache.h"

class v8cgi_App {
public:
	int init(int argc, char ** argv);
	int execute(char ** envp);
	void addOnExit(v8::Handle<v8::Value>);
	int library(char * name);
	int execfile(std::string str, bool change);
	virtual ~v8cgi_App() {};
	
	virtual size_t reader (char * destination, size_t size);
	virtual size_t writer (const char * source, size_t size);
	virtual void error(const char * data, const char * file, int line);
	virtual void header(const char * name, const char * value);

private:
	v8::Handle<v8::Array> onexit; /* what to do on exit */
	std::string cfgfile; /* config file */
	std::string mainfile; /* command-line specified file */
	Cache cache;
	
	int prepare(char ** envp);
	int go(char ** envp);
	void finish();
	void http();
	void report_error(const char * message);
	void exception(v8::TryCatch* try_catch);
	v8::Handle<v8::String> read(std::string name);
	int autoload();
};

#endif
