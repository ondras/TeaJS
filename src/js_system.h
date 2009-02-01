#include <v8.h>
#include "js_app.h"

void setup_system(v8::Handle<v8::Object> global, char ** envp, reader_func_t reader_func, writer_func_t writer_func, error_func_t error_func);
