/**
 * Process control - running other tasks and manipulating their input/output
 */

#include <v8.h>
#include <string>
#include "js_macros.h"
#include <stdlib.h>

namespace {

JS_METHOD(_system) {
	if (args.Length() != 1) {
		return JS_EXCEPTION("Wrong argument count. Use include(\"process\").system(\"command\")");
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
		return JS_EXCEPTION("Wrong argument count. Use include(\"process\").exec(\"command\")");
	}
	
	std::string data;
	FILE *stream;
	int MAX_BUFFER = 256;
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
	
	/* this module provides a set of (static) functions */
	exports->Set(JS_STR("system"), v8::FunctionTemplate::New(_system)->GetFunction());
	exports->Set(JS_STR("exec"), v8::FunctionTemplate::New(_exec)->GetFunction());
}
