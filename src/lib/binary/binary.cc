#include <v8.h>
#include "macros.h"
#include "gc.h"
#include "bytestring.h"

SHARED_INIT() {
	v8::HandleScope handle_scope;
	bytestring_init();
	
	v8::Handle<v8::FunctionTemplate> ft = bytestring_template();
	exports->Set(JS_STR("ByteString"), ft->GetFunction());
	exports->Set(JS_STR("ByteString2"), ft->GetFunction());
}
