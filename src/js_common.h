#ifndef COMMON
#define COMMON

#define SAVE_PTR(index, ptr) args.This()->SetInternalField(index, v8::External::New((void *)ptr)); 
#define LOAD_PTR(index, type) reinterpret_cast<type>(v8::Handle<v8::External>::Cast(args.This()->GetInternalField(index))->Value());
#define SAVE_VALUE(index, val) args.This()->SetInternalField(index, val)
#define LOAD_VALUE(index) args.This()->GetInternalField(index)
#define JS_STR(...) v8::String::New(__VA_ARGS__)
#define JS_INT(val) v8::Integer::New(val)
#define JS_FLOAT(val) v8::Number::New(val)
#define JS_BOOL(val) v8::Boolean::New(val)
#define JS_METHOD(name) v8::Handle<v8::Value> name(const v8::Arguments& args) { v8::HandleScope handle_scope;



#include <v8.h>

v8::Handle<v8::Array> char2array(char * data, int count);
v8::Handle<v8::String> char2string(char * data, int count);


#endif
