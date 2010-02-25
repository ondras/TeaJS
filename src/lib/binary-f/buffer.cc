#include <v8.h>
#include <string>
#include <vector>
#include "macros.h"
#include "gc.h"
#include "bytestorage.h"

#define BS_OTHER(object) reinterpret_cast<ByteStorage *>(object->GetPointerFromInternalField(0))
#define BS_THIS BS_OTHER(args.This())
#define WRONG_CTOR JS_TYPE_ERROR("Buffer() called with wrong arguments.")

namespace {

v8::Persistent<v8::FunctionTemplate> bufferTemplate;
v8::Persistent<v8::Function> buffer;

size_t firstIndex(v8::Handle<v8::Value> index, size_t length) {
	int i = 0;
	if (!index->IsUndefined()) { i = index->IntegerValue(); }
	if (i < 0) { i += length; }
	
	if (i < 0) { i = 0; }
	if (i > length) { i = length; }
	return (size_t) i;
}

size_t lastIndex(v8::Handle<v8::Value> index, size_t length) {
	int i = length;
	if (!index->IsUndefined()) { i = index->IntegerValue(); }
	if (i < 0) { i += length; }
	
	if (i < 0) { i = 0; }
	if (i > length) { i = length; }
	return (size_t) i;
}

void Buffer_destroy(v8::Handle<v8::Object> instance) {
	ByteStorage * bs = BS_OTHER(instance);
	delete bs;
}

void Buffer_fromBuffer(const v8::Arguments& args, v8::Handle<v8::Object> obj) {
	ByteStorage * bs2 = BS_OTHER(obj);

	int index1 = firstIndex(args[1], bs2->getLength());
	int index2 = lastIndex(args[2], bs2->getLength());
	
	bool copy = true;
	if (!args[3]->IsUndefined()) { copy = args[3]->ToBoolean()->Value(); }
	
	ByteStorage * bs;
	if (copy) {
		size_t length = index2-index1;
		bs = new ByteStorage(length);
		bs->fill(bs2->getData() + index1, length);
	} else {
		bs = new ByteStorage(bs2, index1, index2);
	}
	
	SAVE_PTR(0, bs);
}

void Buffer_fromString(const v8::Arguments& args) {
	if (args.Length() < 2) { WRONG_CTOR; }
	v8::String::Utf8Value str(args[0]);
	v8::String::Utf8Value charset(args[1]);
	ByteStorage bs_tmp((unsigned char *) (*str), str.length());
	ByteStorage * bs = bs_tmp.transcode("utf-8", *charset);
	SAVE_PTR(0, bs);
}

void Buffer_fromArray(const v8::Arguments& args) {
	v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[0]);

	size_t index1 = firstIndex(args[1], arr->Length());
	size_t index2 = lastIndex(args[2], arr->Length());
	ByteStorage * bs = new ByteStorage(index2 - index1);
	
	size_t index = 0;
	for (size_t i=index1; i<index2; i++) {
		unsigned char value = arr->Get(JS_INT(i))->IntegerValue();
		bs->setByte(index++, value);
	}
	SAVE_PTR(0, bs);
}

JS_METHOD(_Buffer) {
	if (!args.IsConstructCall()) { RETURN_CONSTRUCT_CALL; }
	if (args.Length() == 0) { WRONG_CTOR; }
	
	try {
		if (args[0]->IsExternal()) { /* from a bytestorage */
			v8::Handle<v8::External> ext = v8::Handle<v8::External>::Cast(args[0]);
			SAVE_PTR(0, ext->Value());
		} else if (args[0]->IsNumber()) { /* length, [fill] */
			unsigned char fill = (args.Length() > 1 ? (unsigned char) args[1]->IntegerValue() : 0);
			ByteStorage * bs = new ByteStorage(args[0]->IntegerValue());
			bs->fill(fill);
			SAVE_PTR(0, bs);
		} else if (args[0]->IsArray()) { /* array of numbers */
			Buffer_fromArray(args);
		} else if (args[0]->IsObject()) { /* copy */
			v8::Handle<v8::Object> obj = v8::Handle<v8::Object>::Cast(args[0]);
			if (INSTANCEOF(obj, bufferTemplate)) {
				Buffer_fromBuffer(args, obj);
			} else { WRONG_CTOR; }
		} else if (args[0]->IsString()) { /* string */
			Buffer_fromString(args);
		} else {
			WRONG_CTOR;
		}
	} catch (std::string e) {
		return JS_EXCEPTION(e.c_str());
	}
	
	GC * gc = GC_PTR;
	gc->add(args.This(), Buffer_destroy);

	return args.This();
}

JS_METHOD(Buffer_toString) {
	ByteStorage * bs = BS_THIS;

	if (args.Length() == 0) {
		size_t tmpSize = 100;
		std::string result = "[Buffer ";
		char * tmp = (char *) malloc(tmpSize);
		if (tmp) {
			size_t size = snprintf(tmp, tmpSize, "%d", bs->getLength());
			if (size < tmpSize) { result += tmp; }
			free(tmp);
		}
		result += "]";
		return JS_STR(result.c_str());
	}
	
	v8::String::Utf8Value charset(args[1]);
	try {
		ByteStorage * bs2 = bs->transcode(*charset, "utf-8");
		v8::Handle<v8::Value> result = JS_STR((const char *) bs2->getData(), bs2->getLength());
		delete bs2;
		return result;
	} catch (std::string e) {
		return JS_ERROR(e.c_str());
	}
}

JS_METHOD(Buffer_range) {
	ByteStorage * bs = BS_THIS;
	size_t index1 = firstIndex(args[0], bs->getLength());
	size_t index2 = lastIndex(args[1], bs->getLength());

	ByteStorage * bs2 = new ByteStorage(bs, index1, index2);
	v8::Handle<v8::Value> newargs[] = { v8::External::New((void*)bs2) };
	return buffer->NewInstance(1, newargs);
}

JS_METHOD(Buffer_slice) {
	ByteStorage * bs = BS_THIS;
	size_t index1 = firstIndex(args[0], bs->getLength());
	size_t index2 = lastIndex(args[1], bs->getLength());

	size_t length = index2-index1;
	ByteStorage * bs2 = new ByteStorage(bs->getData() + index1, length);
	
	v8::Handle<v8::Value> newargs[] = { v8::External::New((void*)bs2) };
	return buffer->NewInstance(1, newargs);
}

JS_METHOD(Buffer_fill) {
	if (args.Length() == 0) { return JS_TYPE_ERROR("Invalid value to fill"); }
	ByteStorage * bs = BS_THIS;
	size_t index1 = firstIndex(args[1], bs->getLength());
	size_t index2 = lastIndex(args[2], bs->getLength());
	unsigned char fill = (unsigned char) args[0]->IntegerValue();
	
	for (size_t i = index1; i<index2; i++) {
		bs->setByte(i, fill);
	}

	return args.This();
}

/**
 * Generic copy implementation. Handler either Buffer->Array/Buffer, or Array/Buffer->Buffer copies.
 * @param {args} args
 * @param {bool} to We are copying *from* args.This()
 */
v8::Handle<v8::Value> Buffer_copy_impl(const v8::Arguments& args, bool source) {
	const char * errmsg = "First argument must be a Buffer or Array";
	ByteStorage * bs = BS_THIS;
	ByteStorage * bs2 = NULL;
	size_t length;
	v8::Handle<v8::Array> arr;
	
	if (args.Length() == 0) { return JS_TYPE_ERROR(errmsg); }
	if (args[0]->IsArray()) {
		arr = v8::Handle<v8::Array>::Cast(args[0]);
		length = arr->Length();
	} else if (args[0]->IsObject()) {
		v8::Handle<v8::Object> obj = v8::Handle<v8::Object>::Cast(args[0]);
		if (!INSTANCEOF(obj, bufferTemplate)) { return JS_TYPE_ERROR(errmsg); }
		bs2 = BS_OTHER(obj);
		length = bs2->getLength();
	} else { return JS_TYPE_ERROR(errmsg); }
	
	size_t index1source, index1target;
	if (source) {
		index1target = firstIndex(args[1], length);
		index1source = firstIndex(args[2], bs->getLength());
	} else {
		index1source = firstIndex(args[1], length);
		index1target = firstIndex(args[2], bs->getLength());
	}
	size_t index2 = MIN(length, lastIndex(args[3], bs->getLength()));

	unsigned char byte;
	size_t index;

	if (source) {
		for (size_t i=index1source; i<index2; i++) {
			index = index1target + (i-index1source);
			byte = bs->getByte(i);
			if (bs2) {
				bs2->setByte(index, byte);
			} else {
				arr->Set(JS_INT(index), JS_INT(byte));
			}
		}
	} else {
		for (size_t i=index1source; i<index2; i++) {
			index = index1target + (i-index1source);
			if (bs2) {
				byte = bs2->getByte(i);
			} else {
				byte = arr->Get(JS_INT(i))->IntegerValue();
			}
			bs->setByte(index, byte);
		}
	}
	
	return args.This();
}

JS_METHOD(Buffer_copy) {
	return Buffer_copy_impl(args, true);
}

JS_METHOD(Buffer_copyFrom) {
	return Buffer_copy_impl(args, false);
}

v8::Handle<v8::Value> Buffer_length(v8::Local<v8::String> property, const v8::AccessorInfo &info) {
	ByteStorage * bs = BS_OTHER(info.This());
	return JS_INT(bs->getLength());
}

v8::Handle<v8::Value> Buffer_get(uint32_t index, const v8::AccessorInfo &info) {
	ByteStorage * bs = BS_OTHER(info.This());
	size_t len = bs->getLength();
	if (index < 0 || index >= len) { return JS_RANGE_ERROR("Non-existent index"); }
	
	return JS_INT(bs->getByte(index));
}

v8::Handle<v8::Value> Buffer_set(uint32_t index, v8::Local<v8::Value> value, const v8::AccessorInfo &info) {
	ByteStorage * bs = BS_OTHER(info.This());
	size_t len = bs->getLength();
	if (index < 0 || index >= len) { return JS_RANGE_ERROR("Non-existent index"); }
	
	size_t number = value->IntegerValue();
	bs->setByte(index, (unsigned char) number);

	return value;
}

} /* namespace */

SHARED_INIT() {
	v8::HandleScope handle_scope;
	
	bufferTemplate = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_Buffer));
	bufferTemplate->SetClassName(JS_STR("Buffer"));
	
	v8::Handle<v8::ObjectTemplate> bufferPrototype = bufferTemplate->PrototypeTemplate();
	bufferPrototype->Set(JS_STR("toString"), v8::FunctionTemplate::New(Buffer_toString));
	bufferPrototype->Set(JS_STR("range"), v8::FunctionTemplate::New(Buffer_range));
	bufferPrototype->Set(JS_STR("slice"), v8::FunctionTemplate::New(Buffer_slice));
	bufferPrototype->Set(JS_STR("fill"), v8::FunctionTemplate::New(Buffer_fill));
	bufferPrototype->Set(JS_STR("copy"), v8::FunctionTemplate::New(Buffer_copy));
	bufferPrototype->Set(JS_STR("copyFrom"), v8::FunctionTemplate::New(Buffer_copyFrom));

	v8::Handle<v8::ObjectTemplate> bufferObject = bufferTemplate->InstanceTemplate();
	bufferObject->SetInternalFieldCount(1);	
	bufferObject->SetAccessor(JS_STR("length"), Buffer_length, 0, v8::Handle<v8::Value>(), v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::DontDelete));
	bufferObject->SetIndexedPropertyHandler(Buffer_get, Buffer_set);

	exports->Set(JS_STR("Buffer"), bufferTemplate->GetFunction());
	buffer = v8::Persistent<v8::Function>::New(bufferTemplate->GetFunction());
}
