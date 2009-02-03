#include <v8.h>
#include "js_app.h"

void setup_system(
	v8::Handle<v8::Object> global, 
	char ** envp, 
	v8cgi_App::reader_func_t reader_func, 
	v8cgi_App::writer_func_t writer_func, 
	v8cgi_App::error_func_t error_func,
	v8cgi_App::header_func_t header_func
);
