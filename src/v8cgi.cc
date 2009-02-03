/*
 * v8cgi - cgi binary
 */

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "js_app.h"

extern char ** environ;

size_t reader_function(char * destination, size_t amount) {
	return fread((void *) destination, sizeof(char), amount, stdin);
}

size_t writer_function(const char * data, size_t amount) {
	return fwrite((void *) data, sizeof(char), amount, stdout);
}

void error_function(const char * data, const char * file, int line) {
	fwrite((void *) data, sizeof(char), strlen(data), stderr);
}

void header_function(const char * name, const char * value) {
	printf("%s: %s\n", name, value);
}

int main(int argc, char ** argv) {
	int result = 0;
	v8cgi_App app;
	app.setReader((v8cgi_App::reader_func_t) reader_function);
	app.setWriter(writer_function);
	app.setError(error_function);
	app.setHeader(header_function);
	
	result = app.init(argc, argv);
	if (result) { exit(1); }

#ifdef FASTCGI
	while (FCGI_Accept() >= 0) {
#endif
	result = app.execute(environ);
	
#ifdef FASTCGI
	FCGI_SetExitStatus(result);
#endif
	
#ifdef FASTCGI
	}
#endif

	return result;
}
