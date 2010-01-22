#include <v8.h>
#include <string>
#include "macros.h"
#include "gc.h"
#include "bytestring.h"
#include "bytearray.h"
#include "bytestorage.h"

v8::Handle<v8::Value> commonIndexOf(const v8::Arguments& args, int direction) {
	ByteStorage * bs = BS_THIS;
	int len = args.Length();

	unsigned char value = (unsigned char) args[0]->IntegerValue();
	size_t start = (len > 1 ? args[1]->IntegerValue() : 0);
	size_t end = (len > 2 ? args[2]->IntegerValue() : bs->getLength()-1);
	size_t index1 = MIN(start, end);
	size_t index2 = MAX(start, end);

	return JS_INT(bs->indexOf(value, index1, index2, direction));
}

v8::Handle<v8::Value> Binary_length(v8::Local<v8::String> property, const v8::AccessorInfo &info) {
	ByteStorage * bs = BS_OTHER(info.This());
	return JS_INT(bs->getLength());
}

v8::Handle<v8::Value> Binary_convertTo(const v8::Arguments &args, v8::Handle<v8::Function> ctor) {
	if (args.Length() == 0) {
		/* no copying for ByteString->ByteString conversions */
		if (INSTANCEOF(args.This(), ByteString_template()) && ctor == ByteString_function()) { 
			return args.This(); 
		}
		
		v8::Handle<v8::Value> newargs[]= { args.This() };
		return ctor->NewInstance(1, newargs);
	} else {
		ByteStorage * bs = BS_THIS;
		v8::String::Utf8Value from(args[0]);
		v8::String::Utf8Value to(args[1]);
		try {		
			ByteStorage * bs2 = bs->transcode(*from, *to);
			v8::Handle<v8::Value> newargs[]= { v8::External::New((void*) bs2) };
			return ctor->NewInstance(1, newargs);
		} catch (std::string e) {
			return JS_EXCEPTION(e.c_str());
		}
	}
	
}

JS_METHOD(Binary_indexOf) {
	return commonIndexOf(args, 1);
}

JS_METHOD(Binary_lastIndexOf) {
	return commonIndexOf(args, -1);
}

JS_METHOD(Binary_codeAt) {
	ByteStorage * bs = BS_THIS;
	size_t len = bs->getLength();
	size_t index = args[0]->IntegerValue();
	if (index < 0 || index >= len) { return v8::Undefined(); }
	
	return JS_INT(bs->getByte(index));
}

JS_METHOD(Binary_decodeToString) {
	ByteStorage * bs = BS_THIS;
	v8::String::Utf8Value charset(args[0]);
	try {
		ByteStorage bs_tmp(bs->transcode(*charset, "utf-8"));
		return bs_tmp.toString();
	} catch (std::string e) {
		return JS_EXCEPTION(e.c_str());
	}
}

JS_METHOD(Binary_toByteString) {
	return Binary_convertTo(args, ByteString_function());
}

JS_METHOD(Binary_toByteArray) {
	return Binary_convertTo(args, ByteArray_function());
}

JS_METHOD(Binary_concat) {
	return args.This();	
}

void Binary_destroy(v8::Handle<v8::Object> instance) {
	ByteStorage * bs = BS_OTHER(instance);
	delete bs;
}

JS_METHOD(_Binary) {
	return JS_EXCEPTION("Binary function should never be called.");
}



SHARED_INIT() {
	v8::HandleScope handle_scope;
	
	v8::Handle<v8::FunctionTemplate> binaryTemplate = v8::FunctionTemplate::New(_Binary);
	binaryTemplate->SetClassName(JS_STR("Binary"));
	
	v8::Handle<v8::ObjectTemplate> binaryPrototype = binaryTemplate->PrototypeTemplate();
	binaryPrototype->Set(JS_STR("codeAt"), v8::FunctionTemplate::New(Binary_codeAt));
	binaryPrototype->Set(JS_STR("indexOf"), v8::FunctionTemplate::New(Binary_indexOf));
	binaryPrototype->Set(JS_STR("lastIndexOf"), v8::FunctionTemplate::New(Binary_lastIndexOf));
	binaryPrototype->Set(JS_STR("toByteString"), v8::FunctionTemplate::New(Binary_toByteString));
	binaryPrototype->Set(JS_STR("toByteArray"), v8::FunctionTemplate::New(Binary_toByteArray));
	binaryPrototype->Set(JS_STR("decodeToString"), v8::FunctionTemplate::New(Binary_decodeToString));
	binaryPrototype->Set(JS_STR("concat"), v8::FunctionTemplate::New(Binary_concat));
	exports->Set(JS_STR("Binary"), binaryTemplate->GetFunction());

	ByteString_init(binaryTemplate);
	exports->Set(JS_STR("ByteString"), ByteString_function());

	ByteArray_init(binaryTemplate);
	exports->Set(JS_STR("ByteArray"), ByteArray_function());
}
