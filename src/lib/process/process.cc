/**
 * Process control - running other tasks and manipulating their input/output
 */

#include <v8.h>
#include <string>
#include <vector>
#include "macros.h"
#include "common.h"
#include <stdlib.h>
#include <unistd.h>

#ifndef windows
#  include <sys/wait.h>
#  include <paths.h>  // for _PATH_BSHELL
#else
#  include <process.h>
#  define _PATH_BSHELL "sh"
#endif

namespace {

JS_METHOD(_process) {
	ASSERT_CONSTRUCTOR;
	SAVE_PTR(0, NULL);
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_system) {
	if (args.Length() != 1) {
		JS_TYPE_ERROR("Wrong argument count. Use new Process().system(\"command\")");
		return;
	}
	
	v8::String::Utf8Value cmd(args[0]);
	int result = system(*cmd);
	args.GetReturnValue().Set(JS_INT(result));
}

/**
 * The initial .exec method for stream buffering system commands
 */
JS_METHOD(_exec) {
	if (args.Length() != 1) {
		JS_TYPE_ERROR("Wrong argument count. Use new Process().exec(\"command\")");
		return;
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
		args.GetReturnValue().Set(JS_STR(data.c_str()));
	} else {
		args.GetReturnValue().SetNull();
	}
}


/**
 * Executes the specified comment, setting the environment if requested. Like
 * the exec* family this does not return.
 *
 * @param command the command to run
 * @param env an object whose fields will be the environment variables or null
 *		to use the current environment.
 */
void _executecommand(
		const v8::String::Utf8Value& command, v8::Object* env) {
	if (env != NULL) {

		std::vector<std::string> env_strings;
		std::vector<char const*> env_pointers;
		v8::Handle<v8::Array> keys = env->GetPropertyNames();
		for (unsigned int i=0;i<keys->Length();i++) {
			v8::String::Utf8Value key(keys->Get(JS_INT(i))->ToString());
			v8::String::Utf8Value value(env->Get(JS_STR(*key))->ToString());
			env_strings.push_back(std::string(*key) + "=" + *value);
			env_pointers.push_back(env_strings.back().c_str());
		}
		env_pointers.push_back(NULL);

		// There is no execlep so on Windows we hope that the first version works.
		execle(
				_PATH_BSHELL, "sh", "-c", *command, (char*)NULL, &env_pointers.front());
	} else {
			execl(_PATH_BSHELL, "sh", "-c", *command, (char*)NULL);
	}
	exit(127);  // "command not found"
}

/**
 * Execute the given command, and return exit code and stdout/stderr data
 *
 * TODO: any reason to keep exec?  Either remove exec and rename exec2 to exec,
 * or rename exec2 to something else.
 *
 * @param command    {String}  bash command
 * @param input      {String}  optional; text to send to process as stdin
 * @param env        {Object|null}  optional; an object whose fields will be the
 *                             environment variables. If null or missing then
 *                             the current environment will be used.
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
	if (arg_count < 1 || arg_count > 3) {
		JS_TYPE_ERROR("Wrong argument count. Use new Process().exec2(\"command\", [\"standard input\"], [\"env\"])");
		return;
	}

	const int MAX_BUFFER = 256;
	char buffer[MAX_BUFFER + 1];

	v8::String::Utf8Value command_arg(args[0]);
	v8::Object* env = NULL;
	if (arg_count >= 3 && !((*args[2])->IsNull())) {
		env = (*args[2]->ToObject());
	}

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
		JS_ERROR("Failed to fork process");
		return;

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

		_executecommand(command_arg, env);

		args.GetReturnValue().SetNull();  // unreachable
		return;

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
				// TODO: throw JavaScript exception
				args.GetReturnValue().SetNull();
				return;
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
				// TODO: throw JavaScript exception
				args.GetReturnValue().SetNull();
				return;
			}
			buffer[bytes_read] = 0;
			ret_err.append(buffer);
		}
		close(err_fd[0]);

		int status;
		waitpid(pid, &status, 0);

		v8::Handle<v8::Object> ret = v8::Object::New(JS_ISOLATE);
		if (WIFEXITED(status)) {
			ret->Set(JS_STR("status"), JS_INT(WEXITSTATUS(status)));
		} else {
			// TODO: What should we do in this case? It's not clear how to return
			// other exit codes (for signals, for example).
			ret->Set(JS_STR("status"), JS_INT(-1));
		}
		ret->Set(JS_STR("out"), JS_STR(ret_out.c_str()));
		ret->Set(JS_STR("err"), JS_STR(ret_err.c_str()));
		args.GetReturnValue().Set(ret);
	}
}

/**
 * Execute the given command as a background process.
 *
 * @param command    {String}  bash command
 * @param input      {String}  optional; text to send to process as stdin
 * @param env        {Object|null}  optional; an object whose fields will be the
 *                             environment variables. If null or missing then
 *                             the current environment will be used.
 * @return undefined
 */
JS_METHOD(_fork) {
	int arg_count = args.Length();
	if (arg_count < 1 || arg_count > 3) {
		JS_TYPE_ERROR("Wrong argument count. Use new Process().exec2(\"command\", [\"standard input\"], [\"env\"])");
		return;
	}

	v8::String::Utf8Value command_arg(args[0]);
	v8::Object* env = NULL;
	if (arg_count >= 3 && !((*args[2])->IsNull())) {
		env = (*args[2]->ToObject());
	}

	int input_fd[2];
	pipe(input_fd); // Where the parent is going to write to

	int pid = fork();
	switch (pid) {

	case -1:  // Error case.
		JS_ERROR("Failed to fork process");
		return;

	case 0: { // Child process.

		close(STDIN_FILENO);
		dup2(input_fd[0], STDIN_FILENO);
		close(input_fd[0]); // Not required for the child
		close(input_fd[1]);

		_executecommand(command_arg, env);

		args.GetReturnValue().SetNull();  // unreachable
		return;
	}

	default:  // Parent process.

		close(input_fd[0]); // These are being used by the child
		if (arg_count >= 2) {
			v8::String::Utf8Value input_arg(args[1]);
			write(input_fd[1], *input_arg, input_arg.length()); // Write to child’s stdin
		}
		close(input_fd[1]);
		args.GetReturnValue().SetUndefined();
		return;
	}
}

#endif

}

SHARED_INIT() {
	v8::HandleScope handle_scope(JS_ISOLATE);
	v8::Handle<v8::FunctionTemplate> funct = v8::FunctionTemplate::New(JS_ISOLATE, _process);
	funct->SetClassName(JS_STR("Process"));
	v8::Handle<v8::ObjectTemplate> ot = funct->InstanceTemplate();
	ot->SetInternalFieldCount(1);
	v8::Handle<v8::ObjectTemplate> process = funct->PrototypeTemplate();

	/* this module provides a set of (static) functions */
	process->Set(JS_STR("system"), v8::FunctionTemplate::New(JS_ISOLATE, _system)->GetFunction());
	process->Set(JS_STR("exec"), v8::FunctionTemplate::New(JS_ISOLATE, _exec)->GetFunction());

#ifndef windows
	process->Set(JS_STR("exec2"), v8::FunctionTemplate::New(JS_ISOLATE, _exec2)->GetFunction());
	process->Set(JS_STR("fork"), v8::FunctionTemplate::New(JS_ISOLATE, _fork)->GetFunction());
#endif
	
	exports->Set(JS_STR("Process"), funct->GetFunction());
}
