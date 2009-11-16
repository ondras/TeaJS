/**
 * Process control - running other tasks and manipulating their input/output
 */

#include <v8.h>
#include <string>
#include "js_macros.h"
#include "js_common.h"
#include <stdlib.h>

namespace {

JS_METHOD(_process) {
	ASSERT_CONSTRUCTOR;
	SAVE_PTR(0, NULL);
	return args.This();
}

JS_METHOD(_system) {
	if (args.Length() != 1) {
		return JS_EXCEPTION("Wrong argument count. Use new Process().system(\"command\")");
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
		return JS_EXCEPTION("Wrong argument count. Use new Process().exec(\"command\")");
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

	exports->Set(JS_STR("Process"), funct->GetFunction());
}
