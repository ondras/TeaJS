#include <v8.h>
#include <string>
#include <vector>
#include "macros.h"
#include "gc.h"
#include "binary-b.h"
#include "bytearray.h"
#include "bytestorage-b.h"

#define WRONG_CTOR JS_TYPE_ERROR("ByteArray called with wrong arguments.")

namespace {

v8::Persistent<v8::FunctionTemplate, v8::CopyablePersistentTraits<v8::FunctionTemplate> > _byteArrayTemplate;
v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function> > _byteArray;


/**
 * ByteArray constructor
 */
JS_METHOD(_ByteArray) {
	if (!args.IsConstructCall()) { RETURN_CONSTRUCT_CALL; }
	
	try {
		int arglen = args.Length();
		switch (arglen) {
			case 0: /* empty */
				SAVE_PTR(0, new ByteStorageB());
			break;
			case 1: {
				if (args[0]->IsNumber()) { /* blank with a given length */
					SAVE_PTR(0, new ByteStorageB(args[0]->IntegerValue()));
				} else if (args[0]->IsExternal()) { /* from a bytestorage */
					SAVE_VALUE(0, args[0]);
				} else if (args[0]->IsArray()) { /* array of numbers */
					v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);
					SAVE_PTR(0, new ByteStorageB(arr));
				} else if (args[0]->IsObject()) { /* copy constructor */
					v8::Handle<v8::Object> obj = v8::Handle<v8::Object>::Cast(args[0]);
					if (IS_BINARY(obj)) {
						SAVE_PTR(0, new ByteStorageB(BS_OTHER(obj)));
					} else {
						WRONG_CTOR;
						return;
					}
				} else {
					WRONG_CTOR;
					return;
				}
			} break;
			case 2: {
				/* string, charset */
				v8::String::Utf8Value str(args[0]);
				v8::String::Utf8Value charset(args[1]);
				ByteStorageB bs_tmp((unsigned char *) (*str), str.length());
				ByteStorageB * bs = bs_tmp.transcode("utf-8", *charset);
				SAVE_PTR(0, bs);
			} break;
			default:
				WRONG_CTOR;
				return;
			break;
		}
	} catch (std::string e) {
		JS_ERROR(e.c_str());
		return;
	}
	
	GC * gc = GC_PTR;
	gc->add(args.This(), Binary_destroy);

	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_slice) {
	ByteStorageB * bs = BS_THIS;
	size_t len = args.Length();
	
	size_t start = (len > 0 ? args[0]->IntegerValue() : 0);
	int end_ = (len > 1 ? args[1]->IntegerValue() : bs->getLength());
	if (end_ < 0) { end_ += bs->getLength(); }
	size_t end = (end_ < 0 ? 0 : end_);
	
	ByteStorageB * bs2 = new ByteStorageB(bs, start, end);
	v8::Handle<v8::Value> newargs[] = { v8::External::New(JS_ISOLATE, (void*)bs2) };
	v8::Local<v8::Function> byteArray = v8::Local<v8::Function>::New(JS_ISOLATE, _byteArray);
	args.GetReturnValue().Set(byteArray->NewInstance(1, newargs));
}

JS_METHOD(_splice) {
	ByteStorageB * bs = BS_THIS;
	size_t len = args.Length();
	size_t start = (len > 0 ? args[0]->IntegerValue() : 0);
	size_t howMany = (len > 1 ? args[1]->IntegerValue() : bs->getLength()-start);
	
	/* create new storage with spliced out elements */
	ByteStorageB * bs2 = new ByteStorageB(bs, start, start+howMany);
	
	bs->splice(start, howMany, args);
	
	v8::Handle<v8::Value> newargs[] = { v8::External::New(JS_ISOLATE, (void*)bs2) };
	v8::Local<v8::Function> byteArray = v8::Local<v8::Function>::New(JS_ISOLATE, _byteArray);
	args.GetReturnValue().Set(byteArray->NewInstance(1, newargs));
}

JS_METHOD(_displace) {
	ByteStorageB * bs = BS_THIS;
	size_t len = args.Length();
	size_t start = (len > 0 ? args[0]->IntegerValue() : 0);
	size_t howMany = (len > 1 ? args[1]->IntegerValue() : bs->getLength()-start);
	
	bs->splice(start, howMany, args);

	args.GetReturnValue().Set(JS_INT(bs->getLength()));
}

JS_METHOD(_pop) {
	ByteStorageB * bs = BS_THIS;
	if (!bs->getLength()) { args.GetReturnValue().SetUndefined(); return; }
	args.GetReturnValue().Set(JS_INT(bs->pop()));
}

JS_METHOD(_shift) {
	ByteStorageB * bs = BS_THIS;
	if (!bs->getLength()) { args.GetReturnValue().SetUndefined(); return; }
	args.GetReturnValue().Set(JS_INT(bs->shift()));
}

JS_METHOD(_push) {
	Binary_concat(args.This(), args, true);
}

JS_METHOD(_unshift) {
	Binary_concat(args.This(), args, false);
}

JS_METHOD(_reverse) {
	ByteStorageB * bs = BS_THIS;
	bs->reverse();
	args.GetReturnValue().Set(args.This());
}

JS_METHOD(_concat) {
	Binary_concat(args.This(), args, true);
	args.GetReturnValue().Set(args.This());
}

void _get(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info) {
	ByteStorageB * bs = BS_OTHER(info.This());
	size_t len = bs->getLength();
	if (index < 0 || index >= len) { info.GetReturnValue().SetUndefined(); return; }

	info.GetReturnValue().Set(JS_INT(bs->getByte(index)));
}

void _set(uint32_t index, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info) {
	ByteStorageB * bs = BS_OTHER(info.This());
	size_t len = bs->getLength();
	if (index < 0 || index >= len) { info.GetReturnValue().SetUndefined(); return; }
	
	size_t number = value->IntegerValue();
	bs->setByte(index, (unsigned char) number);

	info.GetReturnValue().Set(value);
}

void _length(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
	int num = value->IntegerValue();
	if (num < 0) { 
		JS_RANGE_ERROR("ByteArray length cannot be negative"); 
		return;
	}

	ByteStorageB * bs = BS_OTHER(info.This());
	bs->resize(num, true);
}


} /* end namespace */

void ByteArray_init(v8::Handle<v8::FunctionTemplate> binaryTemplate) {
	v8::Local<v8::FunctionTemplate> byteArrayTemplate = v8::FunctionTemplate::New(JS_ISOLATE, _ByteArray);
	byteArrayTemplate->Inherit(binaryTemplate);
	byteArrayTemplate->SetClassName(JS_STR("ByteArray"));
	_byteArrayTemplate.Reset(JS_ISOLATE, byteArrayTemplate);

	v8::Handle<v8::ObjectTemplate> byteArrayObject = byteArrayTemplate->InstanceTemplate();
	byteArrayObject->SetInternalFieldCount(1);	
	byteArrayObject->SetAccessor(JS_STR("length"), Binary_length, _length, v8::Handle<v8::Value>(), v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::DontDelete));
	byteArrayObject->SetIndexedPropertyHandler(_get, _set);

	v8::Handle<v8::ObjectTemplate> byteArrayPrototype = byteArrayTemplate->PrototypeTemplate();
	byteArrayPrototype->Set(JS_STR("slice"), v8::FunctionTemplate::New(JS_ISOLATE, _slice));
	byteArrayPrototype->Set(JS_STR("splice"), v8::FunctionTemplate::New(JS_ISOLATE, _splice));
	byteArrayPrototype->Set(JS_STR("displace"), v8::FunctionTemplate::New(JS_ISOLATE, _displace));
	byteArrayPrototype->Set(JS_STR("pop"), v8::FunctionTemplate::New(JS_ISOLATE, _pop));
	byteArrayPrototype->Set(JS_STR("shift"), v8::FunctionTemplate::New(JS_ISOLATE, _shift));
	byteArrayPrototype->Set(JS_STR("push"), v8::FunctionTemplate::New(JS_ISOLATE, _push));
	byteArrayPrototype->Set(JS_STR("unshift"), v8::FunctionTemplate::New(JS_ISOLATE, _unshift));
	byteArrayPrototype->Set(JS_STR("reverse"), v8::FunctionTemplate::New(JS_ISOLATE, _reverse));
	byteArrayPrototype->Set(JS_STR("concat"), v8::FunctionTemplate::New(JS_ISOLATE, _concat));

	_byteArray.Reset(JS_ISOLATE, byteArrayTemplate->GetFunction());
}

v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function> > ByteArray_function() {
	return _byteArray;
}

v8::Persistent<v8::FunctionTemplate, v8::CopyablePersistentTraits<v8::FunctionTemplate> > ByteArray_template() {
	return _byteArrayTemplate;
}
