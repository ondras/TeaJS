#ifndef COMMON
#define COMMON

#include <v8.h>

v8::Handle<v8::Array> char2array(char * data, int count);
v8::Handle<v8::String> char2string(char * data, int count);

#endif
