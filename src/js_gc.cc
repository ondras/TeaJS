/**
 * Garbage collection support. Every C++ class can subscribe to be notified 
 * when its JS representation gets GC'ed.
 */

#include "js_gc.h"

/**
 * GC handler: executed when given object dies
 * @param {v8::Value} object
 * @param {void *} ptr Pointer to GC instance
 */
void GC::handler(v8::Persistent<v8::Value> object, void * ptr) {
	GC * gc = (GC *) ptr;
	GC::objlist::iterator it = gc->data.begin();
	GC::objlist::iterator end = gc->data.end();
	while (it != end && it->first != object) { it++; }
	
	/* only if we have this one */
	if (it != end) { 
		gc->go(it);
	}
}

/**
 * Add a method to be executed when object dies
 * @param {v8::Value} object Object to monitor
 * @param {char *} method Method name
 */
void GC::add(v8::Handle<v8::Value> object, const char * method) {
	v8::Persistent<v8::Value> p = v8::Persistent<v8::Value>::New(object);
	p.MakeWeak((void *) this, &handler);
	this->data.push_back(std::pair<v8::Persistent<v8::Value>, const char *>(p, method));
}

/**
 * Execute ongarbagecollection callback
 */
void GC::go(objlist::iterator it) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Object> obj = it->first->ToObject();
	v8::Local<v8::Function> fun = v8::Local<v8::Function>::Cast(obj->Get(JS_STR(it->second)));
	fun->Call(obj, 0, NULL);
	this->data.erase(it);
}

/**
 * Finish = execute all callbacks
 */
void GC::finish() {
	while (!this->data.empty()) {
		this->go(this->data.begin());
	}
	this->data.clear();
}
