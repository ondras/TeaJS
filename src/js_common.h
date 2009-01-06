#ifndef _JS_COMMON_H
#define _JS_COMMON_H

#include <v8.h>

v8::Handle<v8::Array> char2array(char * data, int count);
v8::Handle<v8::String> char2string(char * data, int count);
size_t afread(char ** ptr, size_t count, FILE * stream);

#endif
