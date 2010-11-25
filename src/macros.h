/**
 * Shorthands for various lengthy V8 syntaxt constructs.
 */
 

#ifndef _JS_MACROS_H
#define _JS_MACROS_H

#include "app.h"
#include "lib/binary/bytestorage.h"

#define _STRING(x) #x
#define STRING(x) _STRING(x)

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

#define SAVE_PTR(index, ptr) args.This()->SetPointerInInternalField(index, (void *)(ptr))
#define LOAD_PTR(index, type) reinterpret_cast<type>(args.This()->GetPointerFromInternalField(index))
#define SAVE_VALUE(index, val) args.This()->SetInternalField(index, val)
#define LOAD_VALUE(index) args.This()->GetInternalField(index)
#define JS_STR(...) v8::String::New(__VA_ARGS__)
#define JS_INT(val) v8::Integer::New(val)
#define JS_FLOAT(val) v8::Number::New(val)
#define JS_BOOL(val) v8::Boolean::New(val)
#define JS_NULL v8::Null()
#define JS_UNDEFINED v8::Undefined()
#define JS_METHOD(name) v8::Handle<v8::Value> name(const v8::Arguments& args)
#define INSTANCEOF(obj, func) func->HasInstance(obj)

#define JS_THROW(type, reason) v8::ThrowException(v8::Exception::type(JS_STR(reason)))
#define JS_ERROR(reason) JS_THROW(Error, reason)
#define JS_TYPE_ERROR(reason) JS_THROW(TypeError, reason)
#define JS_RANGE_ERROR(reason) JS_THROW(RangeError, reason)
#define JS_SYNTAX_ERROR(reason) JS_THROW(SyntaxError, reason)
#define JS_REFERENCE_ERROR(reason) JS_THROW(ReferenceError, reason)
#define JS_RETHROW(tc) v8::Local<v8::Value>::New(tc.Exception());

#define JS_GLOBAL v8::Context::GetCurrent()->Global()
#define GLOBAL_PROTO v8::Handle<v8::Object>::Cast(JS_GLOBAL->GetPrototype())
#define APP_PTR reinterpret_cast<v8cgi_App *>(v8::Handle<v8::External>::Cast(GLOBAL_PROTO->GetInternalField(0))->Value())
#define GC_PTR reinterpret_cast<GC *>(v8::Handle<v8::External>::Cast(GLOBAL_PROTO->GetInternalField(1))->Value())

#define ASSERT_CONSTRUCTOR if (!args.IsConstructCall()) { return JS_ERROR("Invalid call format. Please use the 'new' operator."); }
#define ASSERT_NOT_CONSTRUCTOR if (args.IsConstructCall()) { return JS_ERROR("Invalid call format. Please do not use the 'new' operator."); }
#define RETURN_CONSTRUCT_CALL \
	std::vector< v8::Handle<v8::Value> > params(args.Length()); \
	for (size_t i=0; i<params.size(); i++) { params[i] = args[i]; } \
	return args.Callee()->NewInstance(args.Length(), &params[0]);

#ifdef _WIN32
#   define SHARED_INIT() extern "C" __declspec(dllexport) void init(v8::Handle<v8::Function> require, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module)
#else
#   define SHARED_INIT() extern "C" void init(v8::Handle<v8::Function> require, v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module)
#endif

inline v8::Handle<v8::Value> BYTESTORAGE_TO_JS(ByteStorage * bs) {
	v8::Handle<v8::Function> buffer = v8::Handle<v8::Function>::Cast((APP_PTR)->require("binary", "")->Get(JS_STR("Buffer")));
	v8::Handle<v8::Value> newargs[] = { v8::External::New((void*)bs) };
	return v8::Handle<v8::Function>::Cast(buffer)->NewInstance(1, newargs);
}

inline ByteStorage * JS_TO_BYTESTORAGE(v8::Handle<v8::Value> value) {
	v8::Handle<v8::Object> object = value->ToObject();
	return reinterpret_cast<ByteStorage *>(object->GetPointerFromInternalField(0));
}


inline v8::Handle<v8::Value> JS_BUFFER(char * data, size_t length) {
	ByteStorage * bs = new ByteStorage(data, length);
	return BYTESTORAGE_TO_JS(bs);
}

inline char * JS_BUFFER_TO_CHAR(v8::Handle<v8::Value> value, size_t * size) {
	ByteStorage * bs = JS_TO_BYTESTORAGE(value);
	*size = bs->getLength();
	return bs->getData();
}

inline bool IS_BUFFER(v8::Handle<v8::Value> value) {
	if (!value->IsObject()) { return false; }
	v8::Handle<v8::Value> proto = value->ToObject()->GetPrototype();
	v8::Handle<v8::Value> prototype = (APP_PTR)->require("binary", "")->Get(JS_STR("Buffer"))->ToObject()->Get(JS_STR("prototype"));
	return proto->Equals(prototype);
}

#endif
