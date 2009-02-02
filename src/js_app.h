/*
 * v8cgi app file. Loosely based on V8's "shell" sample app.
 */

#ifndef _JS_APP_H
#define _JS_APP_H

typedef size_t (*reader_func_t) (char *, size_t);
typedef size_t (*writer_func_t) (const char *, size_t);
typedef void (*error_func_t) (const char *, const char *, int);
typedef void (*header_func_t) (const char *, const char *);

void app_terminate();
int app_initialize(
	int argc, 
	char ** argv, 
	reader_func_t reader_func, 
	writer_func_t writer_func, 
	error_func_t error_func,
	header_func_t header_func
);
int app_cycle(char ** envp);

#endif
