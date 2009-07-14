/**
 * Process control - running other tasks and manipulating their input/output
 */

#include <v8.h>
#include "js_macros.h"
#include <stdlib.h>

namespace {

JS_METHOD(_system) {
	if (args.Length() != 1) {
		return JS_EXCEPTION("Wrong argument count. Use system.system(\"command\")");
	}
	
	v8::String::Utf8Value cmd(args[0]);
	int result = system(*cmd);
	return JS_INT(result);
}

}

SHARED_INIT() {
	v8::HandleScope handle_scope;
	
	/* this module provides a set of (static) functions */
	exports->Set(JS_STR("system"), v8::FunctionTemplate::New(_system)->GetFunction());
}
