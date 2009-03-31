#include "js_gc.h"

void GC::handler(v8::Persistent<v8::Value> object, void * ptr) {
	GC * gc = (GC *) ptr;
	GC::objlist::iterator it = gc->data.begin();
	GC::objlist::iterator end = gc->data.end();
	while (it != end && it->first != object) { it++; }
	if (it != end) { /* only if we have this one */
		gc->go(it);
	}
}

void GC::add(v8::Handle<v8::Value> object, char * method) {
	v8::Persistent<v8::Value> p = v8::Persistent<v8::Value>::New(object);
	p.MakeWeak((void *) this, &handler);
	this->data.push_back(std::pair<v8::Persistent<v8::Value>, char *>(p, method));
}

void GC::go(objlist::iterator it) {
	v8::HandleScope handle_scope;
	v8::Handle<v8::Object> obj = it->first->ToObject();
	v8::Local<v8::Function> fun = v8::Local<v8::Function>::Cast(obj->Get(JS_STR(it->second)));
	fun->Call(obj, 0, NULL);
	this->data.erase(it);
}

void GC::finish() {
	while (!this->data.empty()) {
		this->go(this->data.begin());
	}
	this->data.clear();
}
