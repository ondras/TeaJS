#include <v8.h>
#include <string>

#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

#include "macros.h"
#include "common.h"
#include "app.h"
#include "system.h"
#include "path.h"
#include <unistd.h>
#include <sys/time.h>

#ifndef HAVE_SLEEP
#	include <windows.h>
#	include <process.h>
#	define sleep(num) { Sleep(num * 1000); }
#	define usleep(num) { Sleep(num / 1000); }
#endif

namespace {

v8::Persistent<v8::Function> js_stdin;
v8::Persistent<v8::Function> js_stdout;
v8::Persistent<v8::Function> js_stderr;

/**
 * Read characters from stdin
 * @param {int} count How many; 0 == all
 */
JS_METHOD(_read) {
	size_t count = 0;
	if (args.Length() && args[0]->IsNumber()) {
		count = args[0]->IntegerValue();
	}
	
	return READ(stdin, count);
}

JS_METHOD(_readline) {
	int size = args[1]->IntegerValue();
	if (size < 1) { size = 0xFFFF; }
	return READ_LINE(stdin, size);
}

/**
 * Dump data to stdout
 * @param {string||Buffer} String or Buffer
 */
JS_METHOD(_write_stdout) {
	WRITE(stdout, args[0]);
	return js_stdout;
}

JS_METHOD(_write_stderr) {
	WRITE(stderr, args[0]);
	return js_stderr;
}

JS_METHOD(_writeline_stdout) {
	WRITE_LINE(stdout, args[0]);
	return js_stdout;
}

JS_METHOD(_writeline_stderr) {
	WRITE_LINE(stderr, args[0]);
	return js_stderr;
}

JS_METHOD(_getcwd) {
	return JS_STR(path_getcwd().c_str());
}

JS_METHOD(_getpid) {
	return JS_INT(getpid());
}

/**
 * Sleep for a given number of seconds
 */
JS_METHOD(_sleep) {
	int num = args[0]->Int32Value();
	{
		v8::Unlocker unlocker;
		sleep(num);
	}
	return v8::Undefined();
}

/**
 * Sleep for a given number of microseconds
 */
JS_METHOD(_usleep) {
	v8::HandleScope handle_scope;
	int num = args[0]->Int32Value();
	usleep(num);
	return v8::Undefined();
}

/**
 * Return the number of microseconds that have elapsed since the epoch.
 */
JS_METHOD(_getTimeInMicroseconds) {
	struct timeval tv;
	gettimeofday(&tv, 0);
	char buffer[24];
	sprintf(buffer, "%lu%06lu", tv.tv_sec, tv.tv_usec);
	return JS_STR(buffer)->ToNumber();
}

JS_METHOD(_flush_stdout) {
	if (fflush(stdout)) { return JS_ERROR("Can not flush stdout"); }
	return v8::Undefined();
}

JS_METHOD(_flush_stderr) {
	if (fflush(stderr)) { return JS_ERROR("Can not flush stderr"); }
	return v8::Undefined();
}

}

void setup_system(v8::Handle<v8::Object> global, char ** envp, std::string mainfile, std::vector<std::string> args) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Object> system = v8::Object::New();
	v8::Handle<v8::Object> env = v8::Object::New();
	global->Set(JS_STR("system"), system);
	
	/**
	 * Create system.args 
	 */
	v8::Handle<v8::Array> arr = v8::Array::New();
	arr->Set(JS_INT(0), JS_STR(mainfile.c_str()));
	for (size_t i = 0; i < args.size(); ++i) {
		arr->Set(JS_INT(i+1), JS_STR(args.at(i).c_str()));
	}
	system->Set(JS_STR("args"), arr);

	js_stdin = v8::Persistent<v8::Function>::New(v8::FunctionTemplate::New(_read)->GetFunction());
	system->Set(JS_STR("stdin"), js_stdin);
	js_stdin->Set(JS_STR("read"), js_stdin);
	js_stdin->Set(JS_STR("readLine"), v8::FunctionTemplate::New(_readline)->GetFunction());

	js_stdout = v8::Persistent<v8::Function>::New(v8::FunctionTemplate::New(_write_stdout)->GetFunction());
	system->Set(JS_STR("stdout"), js_stdout);
	js_stdout->Set(JS_STR("write"), js_stdout);
	js_stdout->Set(JS_STR("writeLine"), v8::FunctionTemplate::New(_writeline_stdout)->GetFunction());
	js_stdout->Set(JS_STR("flush"), v8::FunctionTemplate::New(_flush_stdout)->GetFunction());

	js_stderr = v8::Persistent<v8::Function>::New(v8::FunctionTemplate::New(_write_stderr)->GetFunction());
	system->Set(JS_STR("stderr"), js_stderr);
	js_stderr->Set(JS_STR("write"), js_stderr);
	js_stderr->Set(JS_STR("writeLine"), v8::FunctionTemplate::New(_writeline_stderr)->GetFunction());
	js_stderr->Set(JS_STR("flush"), v8::FunctionTemplate::New(_flush_stderr)->GetFunction());
	
	system->Set(JS_STR("getcwd"), v8::FunctionTemplate::New(_getcwd)->GetFunction());
	system->Set(JS_STR("getpid"), v8::FunctionTemplate::New(_getpid)->GetFunction());
	system->Set(JS_STR("sleep"), v8::FunctionTemplate::New(_sleep)->GetFunction());
	system->Set(JS_STR("usleep"), v8::FunctionTemplate::New(_usleep)->GetFunction());
	system->Set(JS_STR("getTimeInMicroseconds"), v8::FunctionTemplate::New(_getTimeInMicroseconds)->GetFunction());
	system->Set(JS_STR("env"), env);
	
	std::string name, value;
	bool done;
	int i,j;
	char ch;
	
	/* extract environment variables and create JS object */
	for (i = 0; envp[i] != NULL; i++) {
		done = false;
		name = "";
		value = "";
		for (j = 0; envp[i][j] != '\0'; j++) {
			ch = envp[i][j];
			if (!done) {
				if (ch == '=') {
					done = true;
				} else {
					name += ch;
				}
			} else {
				value += ch;
			}
		}
		env->Set(JS_STR(name.c_str()), JS_STR(value.c_str()));
	}
}
