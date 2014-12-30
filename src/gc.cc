/**
 * Garbage collection support. Every C++ class can subscribe to be notified 
 * when its JS representation gets GC'ed.
 */

#include "gc.h"
#include "macros.h"

/**
 * GC handler: executed when given object dies
 * @param {v8::Value} object
 * @param {void *} ptr Pointer to GC instance
 */
void GC::handler(const v8::WeakCallbackData<v8::Value, void>& data) {
	GC * gc = (GC *) data.GetParameter();
	v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value> > object;
	object.Reset(JS_ISOLATE, data.GetValue());
	GC::objlist::iterator it = gc->data.begin();
	GC::objlist::iterator end = gc->data.end();
	while (it != end && it->first != object) { it++; }

	object.Reset();
	/* only if we have this one */
	if (it != end) { gc->go(it); }
}

/**
 * Add a method to be executed when object dies
 * @param {v8::Value} object Object to monitor
 * @param {char *} method Method name
 */
void GC::add(v8::Handle<v8::Value> object, GC::dtor_t dtor) {
	v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value> > p;
	p.Reset(JS_ISOLATE, object);
	p.SetWeak((void *) this, &handler);
	this->data.push_back(std::pair<v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value> >, GC::dtor_t>(p, dtor));
}

/**
 * Execute ongarbagecollection callback
 */
void GC::go(objlist::iterator it) {
	dtor_t dtor = it->second;
	v8::Local<v8::Value> _object = v8::Local<v8::Value>::New(JS_ISOLATE, it->first);
	v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(_object);
	dtor(object);
	it->first.Reset();
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

GC::~GC() {};
