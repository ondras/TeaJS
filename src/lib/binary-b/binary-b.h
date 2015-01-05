#ifndef _BINARY_H
#define _BINARY_H

#include <v8.h>
#include "macros.h"
#include "bytestring.h"
#include "bytearray.h"

#define IS_BINARY(obj) (INSTANCEOF(obj, v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, ByteArray_template())) || INSTANCEOF(obj, v8::Local<v8::FunctionTemplate>::New(JS_ISOLATE, ByteString_template())))

void Binary_length(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
JS_METHOD(Binary_indexOf);
JS_METHOD(Binary_lastIndexOf);
JS_METHOD(Binary_codeAt);
JS_METHOD(Binary_toByteString);
JS_METHOD(Binary_toByteArray);
JS_METHOD(Binary_decodeToString);

void Binary_concat(v8::Handle<v8::Object> obj, const v8::FunctionCallbackInfo<v8::Value>& args, bool right);
void Binary_destroy(v8::Handle<v8::Object> instance);

#endif
