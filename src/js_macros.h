#ifndef _JS_MACROS_H
#define _JS_MACROS_H

#define SAVE_PTR(index, ptr) args.This()->SetInternalField(index, v8::External::New((void *)ptr)); 
#define LOAD_PTR(index, type) reinterpret_cast<type>(v8::Handle<v8::External>::Cast(args.This()->GetInternalField(index))->Value());
#define SAVE_VALUE(index, val) args.This()->SetInternalField(index, val)
#define LOAD_VALUE(index) args.This()->GetInternalField(index)
#define JS_STR(...) v8::String::New(__VA_ARGS__)
#define JS_INT(val) v8::Integer::New(val)
#define JS_FLOAT(val) v8::Number::New(val)
#define JS_BOOL(val) v8::Boolean::New(val)
#define JS_METHOD(name) v8::Handle<v8::Value> name(const v8::Arguments& args)
#define JS_EXCEPTION(reason) v8::ThrowException(JS_STR(reason))

#ifdef _WIN32
#   define SHARED_INIT() extern "C" __declspec(dllexport) void init(v8::Handle<v8::Object> target)
#else
#   define SHARED_INIT() extern "C" void init(v8::Handle<v8::Object> target)
#endif

#endif
