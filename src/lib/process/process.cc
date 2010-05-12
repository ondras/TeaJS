/**
 * Process control - running other tasks and manipulating their input/output
 */

#include <v8.h>
#include <string>
#include "macros.h"
#include "common.h"
#include <stdlib.h>

#ifndef windows
#  include <sys/wait.h>
#  include <paths.h>  // for _PATH_BSHELL
#endif

namespace {

JS_METHOD(_process) {
	ASSERT_CONSTRUCTOR;
	SAVE_PTR(0, NULL);
	return args.This();
}

JS_METHOD(_system) {
	if (args.Length() != 1) {
		return JS_TYPE_ERROR("Wrong argument count. Use new Process().system(\"command\")");
	}
	
	v8::String::Utf8Value cmd(args[0]);
	int result = system(*cmd);
	return JS_INT(result);
}

/**
 * The initial .exec method for stream buffering system commands
 */
JS_METHOD(_exec) {
	if (args.Length() != 1) {
		return JS_TYPE_ERROR("Wrong argument count. Use new Process().exec(\"command\")");
	}
	
	std::string data;
	FILE *stream;
	const int MAX_BUFFER = 256;
	char buffer[MAX_BUFFER];

	v8::String::Utf8Value cmd(args[0]);
	stream = popen(*cmd, "r");
	while ( fgets(buffer, MAX_BUFFER, stream) != NULL ) {
		data.append(buffer);
	}
	pclose(stream);
	
	if(data.c_str() != NULL) {
		return JS_STR(data.c_str());
	} else {
		return JS_NULL;
	}
}


/**
 * Execute the given command, and return exit code and stdout/stderr data
 *
 * TODO: any reason to keep exec?  Either remove exec and rename exec2 to exec,
 * or rename exec2 to something else.
 *
 * @param command    {String}  bash command
 * @param input      {String}  optional; text to send to process as stdin
 *
 * @return a JavaScript object like: {
 *   status: {Integer} the return code from the process
 *   out:    {String}  contents of stdout
 *   err:    {String}  contents of stderr
 * }
 */
 
#ifndef windows
 
JS_METHOD(_exec2) {
	int arg_count = args.Length();
	if (arg_count < 1 || arg_count > 2) {
		return JS_TYPE_ERROR("Wrong argument count. Use new Process().exec2(\"command\", [\"standard input\"])");
}

	const int MAX_BUFFER = 256;
	char buffer[MAX_BUFFER + 1];

	v8::String::Utf8Value command_arg(args[0]);

	// File descriptors all named from perspective of child process.
	int input_fd[2];
	int out_fd[2];
	int err_fd[2];

	pipe(input_fd); // Where the parent is going to write to
	pipe(out_fd); // From where parent is going to read
	pipe(err_fd);

	int pid = fork();
	switch (pid) {

	case -1:  // Error case.
		return JS_ERROR("Failed to fork process");

	case 0:  // Child process.

		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		close(STDIN_FILENO);

		dup2(input_fd[0], STDIN_FILENO);
		dup2(out_fd[1], STDOUT_FILENO);
		dup2(err_fd[1], STDERR_FILENO);

		close(input_fd[0]); // Not required for the child
		close(input_fd[1]);
		close(out_fd[0]);
		close(out_fd[1]);
		close(err_fd[0]);
		close(err_fd[1]);

		execl(_PATH_BSHELL, "sh", "-c", *command_arg, NULL);
#if defined(__CYGWIN__) || defined(__MSYS__)
                // On cygwin or msys, we may not have /bin/sh.  In that case,
                // try to find sh on PATH.
		execlp("sh", "sh", "-c", *command_arg, NULL);
#endif
		exit(127);  // "command not found"
		return JS_NULL;  // unreachable

	default:  // Parent process.

		close(input_fd[0]); // These are being used by the child
		close(out_fd[1]);
		close(err_fd[1]);

		if (arg_count >= 2) {
			v8::String::Utf8Value input_arg(args[1]);
			write(input_fd[1], *input_arg, input_arg.length()); // Write to child’s stdin
		}
		close(input_fd[1]);

		std::string ret_out;
		while (true) {
			int bytes_read = read(out_fd[0], buffer, MAX_BUFFER);
			if (bytes_read == 0) {
				break;
			} else if (bytes_read < 0) {
				return JS_NULL;  // TODO: throw JavaScript exception
			}
			buffer[bytes_read] = 0;
			ret_out.append(buffer);
		}
		close(out_fd[0]);

		std::string ret_err;
		while (true) {
			int bytes_read = read(err_fd[0], buffer, MAX_BUFFER);
			if (bytes_read == 0) {
				break;
			} else if (bytes_read < 0) {
				return JS_NULL;  // TODO: throw JavaScript exception
			}
			buffer[bytes_read] = 0;
			ret_err.append(buffer);
		}
		close(err_fd[0]);

		int status;
		waitpid(pid, &status, 0);

		v8::Handle<v8::Object> ret = v8::Object::New();
		ret->Set(JS_STR("status"), JS_INT(status));
		ret->Set(JS_STR("out"), JS_STR(ret_out.c_str()));
		ret->Set(JS_STR("err"), JS_STR(ret_err.c_str()));
		return ret;
	}
}

/**
 * Execute the given command as a background process.
 *
 * @param command    {String}  bash command
 * @param input      {String}  optional; text to send to process as stdin
 * @return undefined
 */
JS_METHOD(_fork) {
	int arg_count = args.Length();
	if (arg_count < 1 || arg_count > 2) {
		return JS_TYPE_ERROR("Wrong argument count. Use new Process().exec2(\"command\", [\"standard input\"])");
	}

	v8::String::Utf8Value command_arg(args[0]);

	int input_fd[2];
	pipe(input_fd); // Where the parent is going to write to

	int pid = fork();
	switch (pid) {

	case -1:  // Error case.
		return JS_ERROR("Failed to fork process");

	case 0:  // Child process.

		close(STDIN_FILENO);
		dup2(input_fd[0], STDIN_FILENO);
		close(input_fd[0]); // Not required for the child
		close(input_fd[1]);

		execl(_PATH_BSHELL, "sh", "-c", *command_arg, NULL);
#if defined(__CYGWIN__) || defined(__MSYS__)
                // On cygwin or msys, we may not have /bin/sh.  In that case,
                // try to find sh on PATH.
		execlp("sh", "sh", "-c", *command_arg, NULL);
#endif
		exit(127);  // "command not found"
		return JS_NULL;  // unreachable

	default:  // Parent process.

		close(input_fd[0]); // These are being used by the child
		if (arg_count >= 2) {
			v8::String::Utf8Value input_arg(args[1]);
			write(input_fd[1], *input_arg, input_arg.length()); // Write to child’s stdin
		}
		close(input_fd[1]);
		return JS_UNDEFINED;
	}
}

#endif

}

SHARED_INIT() {
	v8::HandleScope handle_scope;
	v8::Handle<v8::FunctionTemplate> funct = v8::FunctionTemplate::New(_process);
	funct->SetClassName(JS_STR("Process"));
	v8::Handle<v8::ObjectTemplate> ot = funct->InstanceTemplate();
	ot->SetInternalFieldCount(1);
	v8::Handle<v8::ObjectTemplate> process = funct->PrototypeTemplate();

	/* this module provides a set of (static) functions */
	process->Set(JS_STR("system"), v8::FunctionTemplate::New(_system)->GetFunction());
	process->Set(JS_STR("exec"), v8::FunctionTemplate::New(_exec)->GetFunction());

#ifndef windows
	process->Set(JS_STR("exec2"), v8::FunctionTemplate::New(_exec2)->GetFunction());
	process->Set(JS_STR("fork"), v8::FunctionTemplate::New(_fork)->GetFunction());
#endif
	
	exports->Set(JS_STR("Process"), funct->GetFunction());
}
