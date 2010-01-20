#include <v8.h>
#include "macros.h"
#include "gc.h"
#include "bytestring.h"
#include "bytestorage.h"

#define WRONG_CTOR JS_EXCEPTION("ByteString called with wrong arguments.");

namespace {

v8::Persistent<v8::FunctionTemplate> byteStringTemplate;
v8::Persistent<v8::Function> byteString;

void destroy(v8::Handle<v8::Object> instance) {
	ByteStorage * bs = BS_OTHER(instance);
	delete bs;
}

/**
 * ByteString constructor
 */
JS_METHOD(_ByteString) {
	if (!args.IsConstructCall()) {
		/* FIXME */
		return JS_UNDEFINED;
	}
	
	int arglen = args.Length();
	switch (arglen) {
		case 0: /* empty */
			SAVE_PTR(0, new ByteStorage());
		break;
		case 1: {
			if (args[0]->IsArray()) { /* array of numbers */
				v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
				SAVE_PTR(0, new ByteStorage(arr));
			} else if (args[0]->IsObject()) { /* copy constructor */
				v8::Handle<v8::Object> obj = v8::Handle<v8::Object>::Cast(args[0]);
				if (INSTANCEOF(obj, byteStringTemplate)) {
					SAVE_PTR(0, new ByteStorage(BS_OTHER(obj)));
				} else {
					return WRONG_CTOR;
				}
			} else {
				return WRONG_CTOR;
			}
		} break;
		case 2:
			/* string, charset FIXME */
		break;
		default:
			return WRONG_CTOR;
		break;
		
	}

	GC * gc = GC_PTR;
	gc->add(args.This(), destroy);

	return args.This();
}

v8::Handle<v8::Value> length(v8::Local<v8::String> property, const v8::AccessorInfo &info) {
	ByteStorage * bs = BS_OTHER(info.This());
	return JS_INT(bs->getLength());
}


} /* end namespace */

void ByteString_init(v8::Handle<v8::FunctionTemplate> binaryTemplate) {
	byteStringTemplate = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_ByteString));
	byteStringTemplate->SetClassName(JS_STR("ByteString"));
	byteStringTemplate->Inherit(binaryTemplate);
	
	v8::Handle<v8::ObjectTemplate> byteStringObject = byteStringTemplate->InstanceTemplate();
	byteStringObject->SetInternalFieldCount(1);
	
	byteStringObject->SetAccessor(JS_STR("length"), length);

	
	byteString = v8::Persistent<v8::Function>::New(byteStringTemplate->GetFunction());
}

v8::Handle<v8::Function> ByteString_function() {
	return byteString;
}

