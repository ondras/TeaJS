/**
 * Garbage collection support. Every C++ class can subscribe to be notified 
 * when its JS representation gets GC'ed.
 */

#include "gc.h"
#include "macros.h"

void GC::WeakCallback(const v8::WeakCallbackData<v8::Value, void>& data) {
	v8::HandleScope scope(JS_ISOLATE);
	
	GCObject *gcObject = (GCObject *) data.GetParameter();

	v8::Local<v8::Value> _object = v8::Local<v8::Value>::New(JS_ISOLATE, data.GetValue());
	v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(_object);

	if (gcObject->dtor) {
		gcObject->dtor(object);
	}
	if (gcObject->dtor_name) {
		v8::Local<v8::Function> fun = v8::Local<v8::Function>::Cast(object->Get(JS_STR(gcObject->dtor_name)));
		fun->Call(object, 0, NULL);
	}
	
	gcObject->_handle.Reset();
	delete gcObject;
}

void GC::add(v8::Handle<v8::Value> object, GC::dtor_t dtor) {
	GCObject * gcObject = new GCObject();
	gcObject->dtor = dtor;
	gcObject->_handle.Reset(JS_ISOLATE, object);
	gcObject->_handle.SetWeak((void *) gcObject, &WeakCallback);
	gcObject->_handle.MarkIndependent();	
}

void GC::add(v8::Handle<v8::Value> object, const char *name) {
	GCObject * gcObject = new GCObject();
	gcObject->dtor_name = name;
	gcObject->_handle.Reset(JS_ISOLATE, object);
	gcObject->_handle.SetWeak((void *) gcObject, &WeakCallback);
	gcObject->_handle.MarkIndependent();
}

GC::~GC() {};
