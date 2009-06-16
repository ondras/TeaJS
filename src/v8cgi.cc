/**
 * v8cgi - cgi binary
 */

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#  include <signal.h>
#endif

#include <stdlib.h>
#include "js_app.h"

#ifdef FASTCGI
	/**
	 * This is true only after we receive a signal to terminate
	 */
	bool exit_requested = false;
	
	void handle_sigterm(int param) {
		exit_requested = true;
	}

	void handle_sigusr1(int param) {
		exit_requested = true;
	}
#endif

int main(int argc, char ** argv) {
	int result = 0;
	v8cgi_App app;
	result = app.init(argc, argv);
	if (result) { exit(result); }

#ifdef FASTCGI
	signal(SIGTERM, handle_sigterm);
	signal(SIGUSR1, handle_sigusr1);
	/**
	 * FastCGI main loop
	 */
	while (FCGI_Accept() >= 0  && !exit_requested) {
#endif

		result = app.execute(false, NULL);

#ifdef FASTCGI
		if (exit_requested) { 
			FCGI_SetExitStatus(0);
			exit(0); 
		} else {
			FCGI_SetExitStatus(result);
		}
	}
#endif

	return result;
}
