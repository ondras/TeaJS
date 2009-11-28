/**
 * v8cgi - cgi binary
 */

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#  include <signal.h>
#endif

#include <v8.h>
#include <v8-debug.h>
#include <stdlib.h>
#include <string.h>
#include "js_app.h"
#include "js_path.h"

/**
 * Format for command line arguments
 *
 * as you can see if you wish to pass any arguments to v8, you MUST
 * put a -- surrounded by whitespace after all the v8 arguments
 *
 * any arguments after the v8_args but before the program_file are
 * used by v8cgi.
 */
static const char * v8cgi_usage = "v8cgi [v8_args --] [-c path] [-d port] program_file [argument ...]";

class v8cgi_CGI : public v8cgi_App {
public:
	/**
	 * Initialize from command line
	 */
	int init(int argc, char ** argv) {
		v8cgi_App::init();
		
		this->argv0 = std::string(argc > 0 ? path_normalize(argv[0]).c_str() : '\0');
		if (argc == 1) {
			/* no command-line arguments, try looking for CGI env vars */
			if (!this->fromEnvVars()) { return 0; }
		}
		
		try {
			this->process_args(argc, argv);
		} catch (std::string e) {
			/* initialization error -> goes to stderr */
			this->error(e.c_str(), __FILE__, __LINE__); 
			return 1;
		}
		
		return 0;
	}
	
	/**
	 * STDIN reader
	 */
	size_t reader(char * destination, size_t amount) {
		return fread((void *) destination, sizeof(char), amount, stdin);
	}

	/**
	 * STDOUT writer
	 */
	size_t writer(const char * data, size_t amount) {
		return fwrite((void *) data, sizeof(char), amount, stdout);
	}

	/**
	 * STDERR error
	 */
	void error(const char * data, const char * file, int line) {
		fwrite((void *) data, sizeof(char), strlen(data), stderr);
		fwrite((void *) "\n", sizeof(char), 1, stderr);
	}

	int fromEnvVars() {
		char * env = getenv("PATH_TRANSLATED");
		if (!env) { env = getenv("SCRIPT_FILENAME"); }
		if (env) {
			this->mainfile = std::string(env);
			return 0;
		}
		return 1;
	}
	
private:
	std::string argv0;

	const char * instanceType() { 
		return "cli";
	}
	
	const char * executableName() {
		return this->argv0.c_str();
	}
	
	/**
	 * Process command line arguments.
	 */
	void process_args(int argc, char ** argv) {
		std::string err = "Invalid command line usage.\n";
		err += "Correct usage: ";
		err += v8cgi_usage; /* see the v8cgi_usage definition for the format */
		
		/* we must have at least one arg */
		if (argc == 1) { throw err; }
		
		int index = 0;
		
		/* see if we have v8 options */
		bool have_v8args = false;
		for (; index < argc; ++index) {
			/* FIXME: if there is a standalone "--" after the name of the script
			 then this breaks.  I can't figure out a solution to this, so
			 for now we don't support any standalone "--" after the script name.
			 One solution (and the way it currently works) is to require "--"
			 before all other args even if no v8 args are used, but that seems
			 I don't like this, but it is where we are right now. */
			if (std::string(argv[index]) == "--") {
				/* treat all previous arguments as v8 arguments */
				int v8argc = index;
				v8::V8::SetFlagsFromCommandLine(&v8argc, argv, true);
				index++; /* skip over the "--" */
				have_v8args = true;
				break;
			}
		}
		
		/* if there were no v8 args, then reset index to the first argument */
		if (!have_v8args) index = 1;
		
		
		/* scan for v8cgi-specific arguments now */
		while (1) {
			/* we haven't found a mainfile yet, so there MUST be more arguments */
			if (index >= argc) { throw err; }
			std::string optname(argv[index]);
			if (optname[0] != '-') { break; } /* not starting with "-" => mainfile */
			if (optname.length() != 2) { throw err; } /* one-character options only */
			index++; /* skip the option name */
			
			if (index >= argc) { throw err; } /* missing option value */
			
			switch (optname[1]) {
				case 'c':
					this->cfgfile = argv[index];		
	#ifdef VERBOSE
					printf("cfgfile: %s\n", argv[index]);
	#endif
				break;
				
				case 'd':
					v8::Debug::EnableAgent("v8cgi", atoi(argv[index]));
	#ifdef VERBOSE
					printf("port: %s\n", argv[index]);
	#endif
				break;
				
				default:
					throw err;
				break;
			}
			
			index++; /* skip the option value */
		} 
		
		/* argv[index] MUST be the program_file.  If it doesn't
		 exist then we have an error. */
		if (index >= argc) {
			throw err;
		} else {
			this->mainfile = argv[index];
			/* expand mainfile to absolute path */
			if (!path_isabsolute(this->mainfile)) {
				std::string tmp = path_getcwd();
				tmp += "/";
				tmp += this->mainfile;
				this->mainfile = path_normalize(this->mainfile);
			}
			index++; /* skip over the program_file */
		}
		
		/* all the rest of the arguments are arguments to the program_file */
		for (; index < argc; ++index) {
	#ifdef VERBOSE
			printf("program_arg: %s\n", argv[index]);
	#endif
			this->mainfile_args.push_back(std::string(argv[index]));
		}
	}
};

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

extern char ** environ;

int main(int argc, char ** argv) {
	int result = 0;
	v8cgi_CGI cgi;
	result = cgi.init(argc, argv);
	if (result) { exit(result); }

#ifdef FASTCGI
	signal(SIGTERM, handle_sigterm);
	signal(SIGUSR1, handle_sigusr1);
	/**
	 * FastCGI main loop
	 */
	while (FCGI_Accept() >= 0  && !exit_requested) {
		cgi.fromEnvVars();
#endif

		result = cgi.execute(environ);

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
