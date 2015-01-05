#ifndef _BYTESTRING_H
#define _BYTESTRING_H

#include <v8.h>
#include "macros.h"

v8::Persistent<v8::FunctionTemplate, v8::CopyablePersistentTraits<v8::FunctionTemplate> > ByteString_template();
v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function> > ByteString_function();
void ByteString_init(v8::Handle<v8::FunctionTemplate> binary);

#endif
