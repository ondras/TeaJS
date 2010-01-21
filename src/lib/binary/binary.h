#ifndef _BINARY_H
#define _BINARY_H

#include <v8.h>
#include "macros.h"
#include "bytestring.h"
#include "bytearray.h"

#define IS_BINARY(obj) (INSTANCEOF(obj, ByteArray_template()) || INSTANCEOF(obj, ByteString_template()))

v8::Handle<v8::Value> Binary_length(v8::Local<v8::String> property, const v8::AccessorInfo &info);
JS_METHOD(Binary_indexOf);
JS_METHOD(Binary_lastIndexOf);
JS_METHOD(Binary_codeAt);
JS_METHOD(Binary_toByteString);
JS_METHOD(Binary_toByteArray);
JS_METHOD(Binary_decodeToString);
void Binary_destroy(v8::Handle<v8::Object> instance);

#endif
