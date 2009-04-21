/*
 * v8cgi - cgi binary
 */

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include <stdlib.h>
#include "js_app.h"

int main(int argc, char ** argv) {
	int result = 0;
	v8cgi_App app;
	result = app.init(argc, argv);
	if (result) { exit(result); }

#ifdef FASTCGI
	while (FCGI_Accept() >= 0) {
#endif
	result = app.execute(false, NULL);
	
#ifdef FASTCGI
	FCGI_SetExitStatus(result);
#endif
	
#ifdef FASTCGI
	}
#endif

	return result;
}
