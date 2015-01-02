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
	std::pair<GC::dtor_t, const char *> fun(dtor, NULL);
	this->data.push_back(std::pair<v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value> >, std::pair<GC::dtor_t, const char *> >(p, fun));
}

void GC::add(v8::Handle<v8::Value> object, const char *name) {
	v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value> > p;
	p.Reset(JS_ISOLATE, object);
	p.SetWeak((void *) this, &handler);
	std::pair<GC::dtor_t, const char *> fun(NULL, name);
	this->data.push_back(std::pair<v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value> >, std::pair<GC::dtor_t, const char *> >(p, fun));
}

/**
 * Execute ongarbagecollection callback
 */
void GC::go(objlist::iterator it) {
	dtor_t dtor = it->second.first;
	const char *fun_name = it->second.second;
	v8::Local<v8::Value> _object = v8::Local<v8::Value>::New(JS_ISOLATE, it->first);
	v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(_object);
	if (dtor) {
		dtor(object);
	} else {
		v8::Local<v8::Function> fun = v8::Local<v8::Function>::Cast(object->Get(JS_STR(fun_name)));
		fun->Call(object, 0, NULL);
	}
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
