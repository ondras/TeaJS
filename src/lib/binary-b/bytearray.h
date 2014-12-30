#ifndef _BYTEARRAY_H
#define _BYTEARRAY_H

#include <v8.h>
#include "macros.h"

v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function> > ByteArray_function();
v8::Persistent<v8::FunctionTemplate, v8::CopyablePersistentTraits<v8::FunctionTemplate> > ByteArray_template();
void ByteArray_init(v8::Handle<v8::FunctionTemplate> binary);

#endif
