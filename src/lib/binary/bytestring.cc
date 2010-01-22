#include <v8.h>
#include <string>
#include "macros.h"
#include "gc.h"
#include "binary.h"
#include "bytestring.h"
#include "bytestorage.h"

#define WRONG_CTOR JS_EXCEPTION("ByteString called with wrong arguments.")

namespace {

v8::Persistent<v8::FunctionTemplate> byteStringTemplate;
v8::Persistent<v8::Function> byteString;

/**
 * ByteString constructor
 */
JS_METHOD(_ByteString) {
	if (!args.IsConstructCall()) {
		/* FIXME */
		return JS_UNDEFINED;
	}
	
	try {
		int arglen = args.Length();
		switch (arglen) {
			case 0: /* empty */
				SAVE_PTR(0, new ByteStorage());
			break;
			case 1: {
				if (args[0]->IsExternal()) { /* from a bytestorage */
					SAVE_VALUE(0, args[0]);
				} else if (args[0]->IsArray()) { /* array of numbers */
					v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
					SAVE_PTR(0, new ByteStorage(arr));
				} else if (args[0]->IsObject()) { /* copy constructor */
					v8::Handle<v8::Object> obj = v8::Handle<v8::Object>::Cast(args[0]);
					if (IS_BINARY(obj)) {
						SAVE_PTR(0, new ByteStorage(BS_OTHER(obj)));
					} else {
						return WRONG_CTOR;
					}
				} else {
					return WRONG_CTOR;
				}
			} break;
			case 2: {
				/* string, charset */
				v8::String::Utf8Value str(args[0]);
				v8::String::Utf8Value charset(args[1]);
				ByteStorage bs_tmp((unsigned char *) (*str), str.length());
				ByteStorage * bs = bs_tmp.transcode("utf-8", *charset);
				SAVE_PTR(0, bs);
			} break;
			default:
				return WRONG_CTOR;
			break;
		}
	} catch (std::string e) {
		return JS_EXCEPTION(e.c_str());
	}

	GC * gc = GC_PTR;
	gc->add(args.This(), Binary_destroy);

	return args.This();
}

JS_METHOD(_slice) {
	ByteStorage * bs = BS_THIS;
	size_t len = args.Length();
	
	size_t start = (len > 0 ? args[0]->IntegerValue() : 0);
	int end_ = (len > 1 ? args[1]->IntegerValue() : bs->getLength());
	if (end_ < 0) { end_ += bs->getLength(); }
	size_t end = (end_ < 0 ? 0 : end_);
	
	ByteStorage * bs2 = new ByteStorage(bs, start, end);
	v8::Handle<v8::Value> newargs[] = { v8::External::New((void*)bs2) };

	return byteString->NewInstance(1, newargs);
}

JS_METHOD(_concat) {
	v8::Handle<v8::Value> newargs[]= { args.This() };
	v8::Handle<v8::Object> result = ByteString_function()->NewInstance(1, newargs);
	Binary_concat(result, args, true);
	return result;
}

v8::Handle<v8::Value> _get(size_t index, const v8::AccessorInfo &info) {
	ByteStorage * bs = BS_OTHER(info.This());
	size_t len = bs->getLength();
	if (index < 0 || index >= len) { return v8::Undefined(); }
	
	ByteStorage * bs2 = new ByteStorage(bs, index, index+1);
	v8::Handle<v8::Value> newargs[] = { v8::External::New((void*)bs2) };
	
	return byteString->NewInstance(1, newargs);
}


} /* end namespace */

void ByteString_init(v8::Handle<v8::FunctionTemplate> binaryTemplate) {
	byteStringTemplate = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_ByteString));
	byteStringTemplate->Inherit(binaryTemplate);
	byteStringTemplate->SetClassName(JS_STR("ByteString"));
	
	v8::Handle<v8::ObjectTemplate> byteStringObject = byteStringTemplate->InstanceTemplate();
	byteStringObject->SetInternalFieldCount(1);	
	byteStringObject->SetAccessor(JS_STR("length"), Binary_length, 0, v8::Handle<v8::Value>(), v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete));
	byteStringObject->SetIndexedPropertyHandler(_get);

	v8::Handle<v8::ObjectTemplate> byteStringPrototype = byteStringTemplate->PrototypeTemplate();
	byteStringPrototype->Set(JS_STR("slice"), v8::FunctionTemplate::New(_slice));
	byteStringPrototype->Set(JS_STR("concat"), v8::FunctionTemplate::New(_concat));

	byteString = v8::Persistent<v8::Function>::New(byteStringTemplate->GetFunction());
}

v8::Handle<v8::Function> ByteString_function() {
	return byteString;
}

v8::Handle<v8::FunctionTemplate> ByteString_template() {
	return byteStringTemplate;
}
