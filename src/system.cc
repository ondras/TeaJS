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
	
	READ(stdin, count, args);
}

JS_METHOD(_readline) {
	int size = args[1]->IntegerValue();
	if (size < 1) { size = 0xFFFF; }
	READ_LINE(stdin, size, args);
}

/**
 * Dump data to stdout
 * @param {string||Buffer} String or Buffer
 */
JS_METHOD(_write_stdout) {
	WRITE(stdout, args[0]);
	args.GetReturnValue().Set(v8::Local<v8::Function>::New(JS_ISOLATE, js_stdout));
}

JS_METHOD(_write_stderr) {
	WRITE(stderr, args[0]);
	args.GetReturnValue().Set(v8::Local<v8::Function>::New(JS_ISOLATE, js_stderr));
}

JS_METHOD(_writeline_stdout) {
	v8::Handle<v8::Value> str = args[0];
	if (!args.Length()) { str = JS_STR(""); }
	WRITE_LINE(stdout, str);
	args.GetReturnValue().Set(v8::Local<v8::Function>::New(JS_ISOLATE, js_stdout));
}

JS_METHOD(_writeline_stderr) {
	v8::Handle<v8::Value> str = args[0];
	if (!args.Length()) { str = JS_STR(""); }
	WRITE_LINE(stderr, str);
	args.GetReturnValue().Set(v8::Local<v8::Function>::New(JS_ISOLATE, js_stderr));
}

JS_METHOD(_getcwd) {
	args.GetReturnValue().Set(JS_STR(path_getcwd().c_str()));
}

JS_METHOD(_getpid) {
	args.GetReturnValue().Set(getppid());
}

/**
 * Sleep for a given number of seconds
 */
JS_METHOD(_sleep) {
	int num = args[0]->Int32Value();
	{
		v8::Unlocker unlocker(JS_ISOLATE);
		sleep(num);
	}
	args.GetReturnValue().SetUndefined();
}

/**
 * Sleep for a given number of microseconds
 */
JS_METHOD(_usleep) {
	v8::HandleScope handle_scope(JS_ISOLATE);
	int num = args[0]->Int32Value();
	usleep(num);
	args.GetReturnValue().SetUndefined();
}

/**
 * run GC and forzen for n ms, default is 1000
 */
JS_METHOD(_gc) {
	int idle_time = args.Length() ? args[0]->Int32Value() : 1000;
	JS_ISOLATE->IdleNotification(idle_time);
	args.GetReturnValue().SetUndefined();
}

/**
 * run HEAP statistics
 */
JS_METHOD(_heap_statistics) {
	v8::HeapStatistics heap_statistics;
	v8::Handle<v8::Object> result = v8::Object::New(JS_ISOLATE);

	JS_ISOLATE->GetHeapStatistics(&heap_statistics);

	result->Set(JS_STR("total_heap_size"), JS_INT(heap_statistics.total_heap_size()));
	result->Set(JS_STR("total_heap_size_executable"), JS_INT(heap_statistics.total_heap_size_executable()));
	result->Set(JS_STR("total_physical_size"), JS_INT(heap_statistics.total_physical_size()));
	result->Set(JS_STR("used_heap_size"), JS_INT(heap_statistics.used_heap_size()));
	result->Set(JS_STR("heap_size_limit"), JS_INT(heap_statistics.heap_size_limit()));

	args.GetReturnValue().Set(result);
}

/**
 * Return the number of microseconds that have elapsed since the epoch.
 */
JS_METHOD(_getTimeInMicroseconds) {
	struct timeval tv;
	gettimeofday(&tv, 0);
	char buffer[24];
	sprintf(buffer, "%lu%06lu", tv.tv_sec, tv.tv_usec);
	args.GetReturnValue().Set(JS_STR(buffer)->ToNumber());
}

JS_METHOD(_flush_stdout) {
	if (fflush(stdout)) { JS_ERROR("Can not flush stdout"); return; }
	args.GetReturnValue().SetUndefined();
}

JS_METHOD(_flush_stderr) {
	if (fflush(stderr)) { JS_ERROR("Can not flush stderr"); return; }
	args.GetReturnValue().SetUndefined();
}

}

void setup_system(v8::Handle<v8::Object> global, char ** envp, std::string mainfile, std::vector<std::string> args) {
	v8::HandleScope handle_scope(JS_ISOLATE);
	v8::Handle<v8::Object> system = v8::Object::New(JS_ISOLATE);
	v8::Handle<v8::Object> env = v8::Object::New(JS_ISOLATE);
	global->Set(JS_STR("system"), system);
	
	/**
	 * Create system.args 
	 */
	v8::Handle<v8::Array> arr = v8::Array::New(JS_ISOLATE);
	arr->Set(JS_INT(0), JS_STR(mainfile.c_str()));
	for (size_t i = 0; i < args.size(); ++i) {
		arr->Set(JS_INT(i+1), JS_STR(args.at(i).c_str()));
	}
	system->Set(JS_STR("args"), arr);

	v8::Handle<v8::Function> _js_stdin = v8::FunctionTemplate::New(JS_ISOLATE, _read)->GetFunction();
	system->Set(JS_STR("stdin"), _js_stdin);
	_js_stdin->Set(JS_STR("read"), _js_stdin);
	_js_stdin->Set(JS_STR("readLine"), v8::FunctionTemplate::New(JS_ISOLATE, _readline)->GetFunction());
	js_stdin.Reset(JS_ISOLATE, _js_stdin);

	v8::Handle<v8::Function> _js_stdout = v8::FunctionTemplate::New(JS_ISOLATE, _write_stdout)->GetFunction();
	system->Set(JS_STR("stdout"), _js_stdout);
	_js_stdout->Set(JS_STR("write"), _js_stdout);
	_js_stdout->Set(JS_STR("writeLine"), v8::FunctionTemplate::New(JS_ISOLATE, _writeline_stdout)->GetFunction());
	_js_stdout->Set(JS_STR("flush"), v8::FunctionTemplate::New(JS_ISOLATE, _flush_stdout)->GetFunction());
	js_stdout.Reset(JS_ISOLATE, _js_stdout);

	v8::Handle<v8::Function> _js_stderr = v8::FunctionTemplate::New(JS_ISOLATE, _write_stderr)->GetFunction();
	system->Set(JS_STR("stderr"), _js_stderr);
	_js_stderr->Set(JS_STR("write"), _js_stderr);
	_js_stderr->Set(JS_STR("writeLine"), v8::FunctionTemplate::New(JS_ISOLATE, _writeline_stderr)->GetFunction());
	_js_stderr->Set(JS_STR("flush"), v8::FunctionTemplate::New(JS_ISOLATE, _flush_stderr)->GetFunction());
	js_stderr.Reset(JS_ISOLATE, _js_stderr);
	
	system->Set(JS_STR("getcwd"), v8::FunctionTemplate::New(JS_ISOLATE, _getcwd)->GetFunction());
	system->Set(JS_STR("getpid"), v8::FunctionTemplate::New(JS_ISOLATE, _getpid)->GetFunction());
	system->Set(JS_STR("sleep"), v8::FunctionTemplate::New(JS_ISOLATE, _sleep)->GetFunction());
	system->Set(JS_STR("usleep"), v8::FunctionTemplate::New(JS_ISOLATE, _usleep)->GetFunction());
	system->Set(JS_STR("gc"), v8::FunctionTemplate::New(JS_ISOLATE, _gc)->GetFunction());
	system->Set(JS_STR("heap_statistics"), v8::FunctionTemplate::New(JS_ISOLATE, _heap_statistics)->GetFunction());
	system->Set(JS_STR("getTimeInMicroseconds"), v8::FunctionTemplate::New(JS_ISOLATE, _getTimeInMicroseconds)->GetFunction());
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
