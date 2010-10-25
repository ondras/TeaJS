#include <v8.h>
#include "macros.h"

namespace {

JS_METHOD(_resumeProfiler) {
  v8::V8::ResumeProfiler();
  return v8::Undefined();
}

JS_METHOD(_pauseProfiler) {
  v8::V8::PauseProfiler();
  return v8::Undefined();
}

// TODO: Add specific methods to pause / resume the various different types
// of profilers (like heap, etc).

} /* end namespace */

SHARED_INIT() {
  v8::HandleScope handle_scope;

  v8::Handle<v8::Object> profiler = v8::Object::New();

  profiler->Set(JS_STR("resume"),
      v8::FunctionTemplate::New(_resumeProfiler)->GetFunction());
  profiler->Set(JS_STR("pause"),
      v8::FunctionTemplate::New(_pauseProfiler)->GetFunction());

  exports->Set(JS_STR("V8Profiler"), profiler);
}
