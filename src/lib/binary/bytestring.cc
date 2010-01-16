#include <v8.h>
#include "macros.h"
#include "gc.h"
#include "bytestring.h"

#define GET_LENGTH(obj) obj->GetInternalField(0)->NumberValue()
#define GET_DATA(obj) reinterpret_cast<unsigned char *>(v8::Handle<v8::External>::Cast(obj->GetInternalField(1))->Value())

namespace {

v8::Persistent<v8::FunctionTemplate> bytestring;

void destroy(v8::Handle<v8::Object> instance) {
	unsigned char * data = GET_DATA(instance);
	delete[] data;
}

/**
 * ByteString constructor
 */
JS_METHOD(_bytestring) {
	if (!args.IsConstructCall()) {
		/* FIXME */
		return JS_UNDEFINED;
	}
	
	size_t length = 0;
	unsigned char * data = NULL;
	
	int arglen = args.Length();
	switch (arglen) {
		case 0: /* empty */
		break;
		case 1: {
			/* bytestring, bytearray, arrayofnumbers FIXME */
			if (args[0]->IsArray()) {
				v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
				v8::Handle<v8::Object> arrobj = v8::Handle<v8::Object>::Cast(args[0]);
				
				length = arr->Length();
				data = new unsigned char[length];
				for (size_t i = 0; i<length;i++) {
					int num = arrobj->Get(JS_INT(i))->IntegerValue();
					data[i] = (unsigned char) num;
				}
			} else {
				v8::Handle<v8::Object> obj = v8::Handle<v8::Object>::Cast(args[0]);
				if (INSTANCEOF(obj, bytestring_template())) {
					length = GET_LENGTH(obj);
					unsigned char * d = GET_DATA(obj);
					data = new unsigned char[length];
					for (size_t i=0;i<length;i++) { data[i] = d[i]; }
				} else {
					return JS_EXCEPTION("ByteString called with wrong argument type");
				}
			}
		} break;
		case 2:
			/* string, charset FIXME */
		break;
		default:
			return JS_EXCEPTION("ByteString called with wrong argument count");
		break;
		
	}

	SAVE_VALUE(0, JS_INT(length));
	SAVE_PTR(1, data);
	GC * gc = GC_PTR;
	gc->add(args.This(), destroy);

	return args.This();
}

} /* end namespace */

void bytestring_init() {
	bytestring = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_bytestring));
	bytestring->SetClassName(JS_STR("ByteString"));
	

	v8::Handle<v8::ObjectTemplate> ot = bytestring->InstanceTemplate();
	ot->SetInternalFieldCount(2); /* data, length */

	v8::Handle<v8::ObjectTemplate> pt = bytestring->PrototypeTemplate();
}

v8::Handle<v8::FunctionTemplate> bytestring_template() {
	return bytestring;
}