#include <v8.h>
#include <string>
#include <vector>
#include "macros.h"
#include "gc.h"
#include "binary.h"
#include "bytearray.h"
#include "bytestorage.h"

#define WRONG_CTOR JS_EXCEPTION("ByteArray called with wrong arguments.")

namespace {

v8::Persistent<v8::FunctionTemplate> byteArrayTemplate;
v8::Persistent<v8::Function> byteArray;


/**
 * ByteArray constructor
 */
JS_METHOD(_ByteArray) {
	if (!args.IsConstructCall()) { RETURN_CONSTRUCT_CALL; }
	
	try {
		int arglen = args.Length();
		switch (arglen) {
			case 0: /* empty */
				SAVE_PTR(0, new ByteStorage());
			break;
			case 1: {
				if (args[0]->IsNumber()) { /* blank with a given length */
					SAVE_PTR(0, new ByteStorage(args[0]->IntegerValue()));
				} else if (args[0]->IsExternal()) { /* from a bytestorage */
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
	return byteArray->NewInstance(1, newargs);
}

JS_METHOD(_pop) {
	ByteStorage * bs = BS_THIS;
	if (!bs->getLength()) { return v8::Undefined(); }
	return JS_INT(bs->pop());
}

JS_METHOD(_shift) {
	ByteStorage * bs = BS_THIS;
	if (!bs->getLength()) { return v8::Undefined(); }
	return JS_INT(bs->shift());
}

JS_METHOD(_push) {
	return Binary_concat(args.This(), args, true);
}

JS_METHOD(_unshift) {
	return Binary_concat(args.This(), args, false);
}

JS_METHOD(_reverse) {
	ByteStorage * bs = BS_THIS;
	bs->reverse();
	return args.This();
}

JS_METHOD(_concat) {
	Binary_concat(args.This(), args, true);
	return args.This();
}

v8::Handle<v8::Value> _get(size_t index, const v8::AccessorInfo &info) {
	ByteStorage * bs = BS_OTHER(info.This());
	size_t len = bs->getLength();
	if (index < 0 || index >= len) { return v8::Undefined(); }
	
	return JS_INT(bs->getByte(index));
}

v8::Handle<v8::Value> _set(size_t index, v8::Local<v8::Value> value, const v8::AccessorInfo &info) {
	ByteStorage * bs = BS_OTHER(info.This());
	size_t len = bs->getLength();
	if (index < 0 || index >= len) { return v8::Undefined(); }
	
	size_t number = value->IntegerValue();
	bs->setByte(index, (unsigned char) number);

	return value;
}

void _length(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo &info) {
	int num = value->IntegerValue();
	if (num < 0) { 
		JS_EXCEPTION("ByteArray length cannot be negative"); 
		return;
	}

	ByteStorage * bs = BS_OTHER(info.This());
	bs->resize(num, true);
}


} /* end namespace */

void ByteArray_init(v8::Handle<v8::FunctionTemplate> binaryTemplate) {
	byteArrayTemplate = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_ByteArray));
	byteArrayTemplate->Inherit(binaryTemplate);
	byteArrayTemplate->SetClassName(JS_STR("ByteArray"));

	v8::Handle<v8::ObjectTemplate> byteArrayObject = byteArrayTemplate->InstanceTemplate();
	byteArrayObject->SetInternalFieldCount(1);	
	byteArrayObject->SetAccessor(JS_STR("length"), Binary_length, _length, v8::Handle<v8::Value>(), v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::DontDelete));
	byteArrayObject->SetIndexedPropertyHandler(_get, _set);

	v8::Handle<v8::ObjectTemplate> byteArrayPrototype = byteArrayTemplate->PrototypeTemplate();
	byteArrayPrototype->Set(JS_STR("slice"), v8::FunctionTemplate::New(_slice));
	byteArrayPrototype->Set(JS_STR("pop"), v8::FunctionTemplate::New(_pop));
	byteArrayPrototype->Set(JS_STR("shift"), v8::FunctionTemplate::New(_shift));
	byteArrayPrototype->Set(JS_STR("push"), v8::FunctionTemplate::New(_push));
	byteArrayPrototype->Set(JS_STR("unshift"), v8::FunctionTemplate::New(_unshift));
	byteArrayPrototype->Set(JS_STR("reverse"), v8::FunctionTemplate::New(_reverse));
	byteArrayPrototype->Set(JS_STR("concat"), v8::FunctionTemplate::New(_concat));

	byteArray = v8::Persistent<v8::Function>::New(byteArrayTemplate->GetFunction());
}

v8::Handle<v8::Function> ByteArray_function() {
	return byteArray;
}

v8::Handle<v8::FunctionTemplate> ByteArray_template() {
	return byteArrayTemplate;
}
