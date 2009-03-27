#ifndef _JS_GC_H
#define _JS_GC_H

#include <list>
#include "v8.h"
#include "js_macros.h"

class GC {
public:
	typedef std::list<std::pair<v8::Persistent<v8::Value>, char *> > objlist;                    
	
	static void handler(v8::Persistent<v8::Value> object, void * ptr);
    void add(v8::Handle<v8::Value> object, char * method);       
    void go(objlist::iterator it);
	void finish();
	objlist data;
};

#endif
