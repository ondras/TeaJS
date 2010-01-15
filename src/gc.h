/**
 * Garbage collection support. Every C++ class can subscribe to be notified,
 * when its JS representation gets GC'ed.
 */

#ifndef _JS_GC_H
#define _JS_GC_H

#include <list>
#include "v8.h"
#include "macros.h"

class GC {
public:
	typedef std::list<std::pair<v8::Persistent<v8::Value>, const char *> > objlist;

	/* this method is called by V8 when persistent handle gets weak */
	static void handler(v8::Persistent<v8::Value> object, void * ptr);

	/* objects subscribe by calling this method */
	virtual void add(v8::Handle<v8::Value> object, const char * method);

	/* executes a callback for a given iterator */
	virtual void go(objlist::iterator it);

	/* app lifetime ends, time to collect everything that remains */
	virtual void finish();

	/* list of callbacks */
	objlist data;
};

#endif
