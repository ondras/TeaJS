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
	
	typedef size_t (*reader_func_t) (char *, size_t);
	typedef size_t (*writer_func_t) (const char *, size_t);
	typedef void (*error_func_t) (const char *, const char *, int);
	typedef void (*header_func_t) (const char *, const char *);

	void setReader(v8cgi_App::reader_func_t);
	void setWriter(v8cgi_App::writer_func_t);
	void setError(v8cgi_App::error_func_t);
	void setHeader(v8cgi_App::header_func_t);
	v8cgi_App::reader_func_t reader;
	v8cgi_App::writer_func_t writer; 
	v8cgi_App::error_func_t error; 
	v8cgi_App::header_func_t header; 

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
