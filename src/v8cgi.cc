/*
 * v8cgi - cgi binary
 */

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include <stdlib.h>
#include "js_app.h"

extern char ** environ;

int main(int argc, char ** argv) {
	int result = 0;
	v8cgi_App app;
	
	result = app.init(argc, argv);
	if (result) { exit(1); }

#ifdef FASTCGI
	while (FCGI_Accept() >= 0) {
#endif
	result = app.execute(environ, false);
	
#ifdef FASTCGI
	FCGI_SetExitStatus(result);
#endif
	
#ifdef FASTCGI
	}
#endif

	return result;
}
