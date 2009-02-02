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
	result = app_initialize(argc, argv, reader_function, writer_function, error_function, header_function);
	if (result) { exit(1); }

#ifdef FASTCGI
	while (FCGI_Accept() >= 0) {
#endif
	result = app_cycle(environ);
	
#ifdef FASTCGI
	FCGI_SetExitStatus(result);
#endif
	
#ifdef FASTCGI
	}
#endif

	app_terminate();
	return result;
}
