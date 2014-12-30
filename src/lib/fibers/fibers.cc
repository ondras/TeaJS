#include <v8.h>
#include <map>
#include "macros.h"

#include <pthread.h>
#include <stdlib.h>
#include <string>

// Adds a fiber API to TeaJS.
//
// Create a fiber to run a function:
//   var fiber = new Fiber(name_string, function);
//
// Make the fiber runnable. Fibers are suspended when they are created:
//   fiber.becomeRunnable();
//
// Suspend (make unrunnable) a fiber. Only call this on the current fiber.
//   fiber.suspend();
//
// Find the current fiber and store some fiber-local state on it:
//   var current = Fiber.current;
//   current.my_state = something;
//
// Get all fibers that have started executing their functions but not yet
// finished. Suspended fibers that have started executing are included.
//  var fibers = Fibers.allRunningFibers();
//
// Wait for a fiber to complete:
//   fiber.join();
//
// Notes:
// - This actually uses pthreads so these are not technically fibers. But they
//   behave like fibers in that only one can be running at a time.
// - Control only switches from one fiber to another when suspend or join is
//   called. The OS determines which thread/fiber executes next. If you want
//   determinism then you should ensure that only one fiber is runnable when
//   you call suspend.
//
// There are many things that need to be done to this code before we can use it
// for real:
// TODO: check that there are no runnable fibers at exit. Without this we get
// segfaults when these fibers run after the JS context is destroyed.
// TODO: consider adding support yielding to a fiber (rather than suspending and
// resuming different fibers). This would make our code more deterministic.
// TODO: figure out why we get seg faults in some cases when we call a method
// that we forgot to add to the Fiber prototype.
// TODO: our methods seem to seg fault when called with an undefined this. Fix.
// TODO: move this into v8, where it could use v8's thread abstractions. This
// would make it more portable.

namespace {

//#define FIBER_LOGGING
#if defined(FIBER_LOGGING)
#  define FIBER_LOG(args...) fprintf(stdout, ## args)
#else
#  define FIBER_LOG(args...)
#endif

// JS fields are annoying to access so we keep all of the native values in a
// struct in one JS field.
struct NativeData {
  std::string name;

  bool thread_created;
  pthread_t thread;
  uint64_t local_id;

  v8::Persistent<v8::Object> js_fiber;
  pthread_mutex_t condition_mutex;
  pthread_cond_t condition;
  v8::Persistent<v8::Value> func;
  v8::Persistent<v8::Context> context;
};

enum FiberFields {
  FiberFieldNativeDataPtr,
  FiberFieldMax
};
#define FIELDS_NATIVE_DATA_PTR LOAD_PTR(FiberFieldNativeDataPtr, NativeData *)

#define RETURN_ON_ERROR(status, message) \
  if (status != 0) { \
    JS_ERROR(message); \
    return; \
  }
#define EXIT_ON_ERROR(status, message) \
  if (status != 0) { \
    printf("%s\n", message); \
    exit(1); \
  }

uint64_t num_fibers_created = 0;
NativeData * main_fiber_native_data = NULL;
pthread_key_t tls_key;
v8::Persistent<v8::Object> _js_fiber_class;

typedef std::map<uint64_t, NativeData*> FiberIdToNativeDataMap;
FiberIdToNativeDataMap fiber_id_to_native_data_map;


void registerFiber(NativeData* native_data) {
  native_data->local_id = num_fibers_created++;
  fiber_id_to_native_data_map[native_data->local_id] = native_data;
}

void unregisterFiber(NativeData* native_data) {
  fiber_id_to_native_data_map.erase(native_data->local_id);
}

void* runJsFunc(void* opaque_native_data) {
  int status;

  NativeData* native_data = reinterpret_cast<NativeData*>(opaque_native_data);
  status = pthread_setspecific(tls_key, native_data);
  EXIT_ON_ERROR(status, "Could not set tls for non-main fiber");

  {
    v8::Locker locker(JS_ISOLATE);
    v8::HandleScope handle_scope(JS_ISOLATE);

    v8::Local<v8::Object> js_fiber_class = v8::Local<v8::Object>::New(JS_ISOLATE, _js_fiber_class);
    v8::Local<v8::Object> js_fiber = v8::Local<v8::Object>::New(JS_ISOLATE, native_data->js_fiber);
    js_fiber_class->Set(JS_STR("current"), js_fiber);

    v8::Local<v8::Value> _func = v8::Local<v8::Value>::New(JS_ISOLATE, native_data->func);
    v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(_func);

    registerFiber(native_data);

    v8::Local<v8::Context> context = v8::Local<v8::Context>::New(JS_ISOLATE, native_data->context);
    context->Enter();
    func->Call(func, 0, NULL);
    context->Exit();
    unregisterFiber(native_data);
  }

  status = pthread_mutex_destroy(&native_data->condition_mutex);
  EXIT_ON_ERROR(status, "Failed to delete condition_mutex");
  status = pthread_cond_destroy(&native_data->condition);
  EXIT_ON_ERROR(status, "Failed to delete condition");
  native_data->js_fiber.Reset();
  native_data->func.Reset();
  native_data->context.Reset();
  delete native_data;

  return NULL;
}

JS_METHOD(_Fiber) {
  ASSERT_CONSTRUCTOR;

  int status;

  NativeData* native_data = new NativeData();

  v8::Handle<v8::Value> func;
  std::string name;
  if (main_fiber_native_data != NULL) {
    if (args.Length() != 2 ||
        !args[0]->IsString() ||
        !args[1]->IsFunction()) {
      JS_ERROR("Invalid arguments. Use 'new Fiber(name{string}, func{function() : void})'");
      return;
    }
    func = args[1];
    name = *v8::String::Utf8Value(args[0]);
  } else {
    if (args.Length() != 0) {
      JS_ERROR("Invalid arguments. Main fiber should not have args");
      return;
    }
    main_fiber_native_data = native_data;
    func = v8::Null(JS_ISOLATE);
    name = "main";
  }

  SAVE_PTR(FiberFieldNativeDataPtr, native_data);

  native_data->name = name;
  native_data->thread_created = false;
  status = pthread_mutex_init(&native_data->condition_mutex, NULL);
  RETURN_ON_ERROR(status, "Failed to create condition_mutex");
  status = pthread_cond_init(&native_data->condition, NULL);
  RETURN_ON_ERROR(status, "Failed to create condition");

  native_data->js_fiber.Reset(JS_ISOLATE, args.This());
  native_data->func.Reset(JS_ISOLATE, func);
  native_data->context.Reset(JS_ISOLATE, JS_ISOLATE->GetCurrentContext());

  v8::Local<v8::Object> js_fiber = v8::Local<v8::Object>::New(JS_ISOLATE, native_data->js_fiber);
  js_fiber->Set(JS_STR("name"), v8::String::NewFromUtf8(JS_ISOLATE, name.c_str()));

  args.GetReturnValue().Set(args.This());
}

/**
 * Returns the curent fiber. This takes about four times as long as
 * Fiber.current but is useful for checking that Fiber.current is correct.
 */
JS_METHOD(_getCurrentFiber) {
  if (args.Length() != 0) {
    JS_ERROR("Invalid arguments. Use current().'");
    return;
  }

  NativeData * native_data =
      reinterpret_cast<NativeData*>(pthread_getspecific(tls_key));
  args.GetReturnValue().Set(v8::Local<v8::Object>::New(JS_ISOLATE, native_data->js_fiber));
}

/**
 * Returns the main fiber.
 */
JS_METHOD(_main) {
  if (args.Length() != 0) {
    JS_ERROR("Invalid arguments. Use main().'");
    return;
  }

  args.GetReturnValue().Set(v8::Local<v8::Object>::New(JS_ISOLATE, main_fiber_native_data->js_fiber));
}

/**
 * Returns all running fibers.
 */
JS_METHOD(_allRunningFibers) {
  if (args.Length() != 0) {
    JS_ERROR("Invalid arguments. Use allRunningFibers().'");
    return;
  }

  v8::HandleScope handle_scope(JS_ISOLATE);
  v8::Local<v8::Array> result =
      v8::Array::New(JS_ISOLATE, fiber_id_to_native_data_map.size());

  FiberIdToNativeDataMap::iterator fiber = fiber_id_to_native_data_map.begin();
  int index = 0;
  while (fiber != fiber_id_to_native_data_map.end()) {
    v8::Local<v8::Object> js_fiber = v8::Local<v8::Object>::New(JS_ISOLATE, fiber->second->js_fiber);
    result->Set(v8::Number::New(JS_ISOLATE, index), js_fiber);
    fiber++;
    index++;
  }

  args.GetReturnValue().Set(result);
}

JS_METHOD(_becomeRunnable) {
  if (args.Length() != 0) {
    JS_ERROR("Invalid arguments. Use becomeRunnable().'");
    return;
  }

  NativeData * native_data = FIELDS_NATIVE_DATA_PTR;
  if (!native_data->thread_created) {
    FIBER_LOG("fiber '%s': becomeRunnable -- creating thread\n", native_data->name.c_str());
    native_data->thread_created = true;

    int status;

    pthread_attr_t attributes;
    status = pthread_attr_init(&attributes);
    RETURN_ON_ERROR(status, "Failed to create thread attributes");
    status = pthread_attr_setguardsize(&attributes, 4 * 1024);
    RETURN_ON_ERROR(status, "Failed to create thread guard size");
    status = pthread_attr_setstacksize(&attributes, 64 * 1024);
    RETURN_ON_ERROR(status, "Failed to set thread stack size");

    status = pthread_create(
        &native_data->thread, &attributes, runJsFunc, native_data);
    RETURN_ON_ERROR(status, "Failed to create thread");
  } else {
    FIBER_LOG("fiber '%s': becomeRunnable -- resuming\n", native_data->name.c_str());
    pthread_mutex_lock(&native_data->condition_mutex);
    pthread_cond_signal(&native_data->condition);
    pthread_mutex_unlock(&native_data->condition_mutex);
    FIBER_LOG("fiber '%s': becomeRunnable -- finished resuming\n", native_data->name.c_str());
  }

  args.GetReturnValue().Set(args.This());
}

void become_main(v8::Handle<v8::Object> js_this) {
  int status;

  NativeData* native_data = LOAD_PTR_FROM(js_this, FiberFieldNativeDataPtr, NativeData *);
  native_data->thread = pthread_self();
  native_data->thread_created = true;
  status = pthread_setspecific(tls_key, native_data);
  EXIT_ON_ERROR(status, "Could not set tls for main fiber");
  registerFiber(native_data);
  v8::Local<v8::Object> js_fiber_class = v8::Local<v8::Object>::New(JS_ISOLATE, _js_fiber_class);
  v8::Local<v8::Object> js_fiber = v8::Local<v8::Object>::New(JS_ISOLATE, native_data->js_fiber);
  js_fiber_class->Set(JS_STR("current"), js_fiber);
}

JS_METHOD(_suspend) {
  if (args.Length() != 0) {
    JS_ERROR("Invalid arguments. Use suspend().'");
    return;
  }
  // TODO: assert that This is current fiber

  NativeData * native_data = FIELDS_NATIVE_DATA_PTR;
  {
    pthread_mutex_lock(&native_data->condition_mutex);
    FIBER_LOG("fiber '%s': suspending, still has v8 lock\n", native_data->name.c_str());
    // By releasing the lock after we grab the mutex we ensure that
    // another thread can't signal the mutex before we wait on
    // it. (Note: pthread_cond_wait releases the mutex until it
    // returns.)
    v8::Unlocker unlocker(JS_ISOLATE);
    FIBER_LOG("fiber '%s': suspending, released v8 lock\n", native_data->name.c_str());
    pthread_cond_wait(&native_data->condition, &native_data->condition_mutex);
    pthread_mutex_unlock(&native_data->condition_mutex);
    FIBER_LOG("fiber '%s': unsuspending, waiting for v8 lock\n", native_data->name.c_str());
  }
  v8::Local<v8::Object> js_fiber_class = v8::Local<v8::Object>::New(JS_ISOLATE, _js_fiber_class);
  v8::Local<v8::Object> js_fiber = v8::Local<v8::Object>::New(JS_ISOLATE, native_data->js_fiber);
  js_fiber_class->Set(JS_STR("current"), js_fiber);
  FIBER_LOG("fiber '%s': unsuspended, acquired v8 lock\n", native_data->name.c_str());

  args.GetReturnValue().Set(args.This());
}

JS_METHOD(_join) {
  if (args.Length() != 0) {
    JS_ERROR("Invalid arguments. Use join().'");
    return;
  }

  // TODO: check that the fiber is started

  v8::Local<v8::Object> js_fiber_class = v8::Local<v8::Object>::New(JS_ISOLATE, _js_fiber_class);
  v8::Local<v8::Value> caller_js_fiber = js_fiber_class->Get(JS_STR("current"));
  NativeData * native_data = FIELDS_NATIVE_DATA_PTR;

  if (!native_data->thread_created) {
    JS_ERROR("Must call becomeRunnable() on a fiber before joining with it");
    return;
  }

  {
    v8::Unlocker unlocker(JS_ISOLATE);
    FIBER_LOG("fiber '%s': joining\n", native_data->name.c_str());
    pthread_join(native_data->thread, NULL);
    FIBER_LOG("fiber '%s': finished joining\n", native_data->name.c_str());
  }
  js_fiber_class->Set(JS_STR("current"), caller_js_fiber);

  args.GetReturnValue().Set(args.This());
}

} /* end namespace */

SHARED_INIT() {
  int status;

  status = pthread_key_create(&tls_key, NULL);
  EXIT_ON_ERROR(status, "Could not create tls");

  v8::HandleScope handle_scope(JS_ISOLATE);
  v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(JS_ISOLATE, _Fiber);
  ft->SetClassName(JS_STR("Fiber"));

  v8::Handle<v8::ObjectTemplate> ot = ft->InstanceTemplate();
  ot->SetInternalFieldCount(FiberFieldMax);

  v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
  pt->Set(JS_STR("becomeRunnable"), v8::FunctionTemplate::New(JS_ISOLATE, _becomeRunnable));
  pt->Set(JS_STR("suspend"), v8::FunctionTemplate::New(JS_ISOLATE, _suspend));
  pt->Set(JS_STR("join"), v8::FunctionTemplate::New(JS_ISOLATE, _join));

  v8::Local<v8::Function> f = ft->GetFunction();

  v8::Local<v8::Object> main = f->NewInstance();
  _js_fiber_class.Reset(JS_ISOLATE, f);
  become_main(main);
  f->Set(JS_STR("_getCurrentFiber"), v8::FunctionTemplate::New(JS_ISOLATE, _getCurrentFiber)->GetFunction());
  f->Set(JS_STR("allRunningFibers"), v8::FunctionTemplate::New(JS_ISOLATE, _allRunningFibers)->GetFunction());
  f->Set(JS_STR("current"), main);
  f->Set(JS_STR("main"), main);

  exports->Set(JS_STR("Fiber"), f);
}
