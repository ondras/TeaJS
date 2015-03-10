/**
 * Garbage collection support. Every C++ class can subscribe to be notified,
 * when its JS representation gets GC'ed.
 */

#ifndef _JS_GC_H
#define _JS_GC_H

#include <list>
#include "v8.h"

class GC {
public:
	virtual ~GC();

	typedef void (*dtor_t) (v8::Handle<v8::Object>);

	static void WeakCallback(const v8::WeakCallbackData<v8::Value, void>& data);    

	virtual void add(v8::Handle<v8::Value> object, dtor_t);
	virtual void add(v8::Handle<v8::Value> object, const char *name);
};

struct GCObject {
    GC::dtor_t dtor;
    const char *dtor_name;

    v8::Persistent<v8::Value> _handle;
};

#endif
