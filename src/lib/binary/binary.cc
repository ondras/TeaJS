#include <v8.h>
#include "macros.h"
#include "gc.h"
#include "bytestring.h"
#include "bytearray.h"

namespace {
	JS_METHOD(_Binary) {
		return JS_EXCEPTION("Binary function should never be called.");
	}
}


SHARED_INIT() {
	v8::HandleScope handle_scope;
	
	v8::Handle<v8::FunctionTemplate> binaryTemplate = v8::FunctionTemplate::New(_Binary);
	binaryTemplate->SetClassName(JS_STR("Binary"));
	exports->Set(JS_STR("Binary"), binaryTemplate->GetFunction());
	
	ByteString_init(binaryTemplate);
	exports->Set(JS_STR("ByteString"), ByteString_function());

	ByteArray_init(binaryTemplate);
	exports->Set(JS_STR("ByteArray"), ByteArray_function());
}
