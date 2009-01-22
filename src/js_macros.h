#ifndef _JS_MACROS_H
#define _JS_MACROS_H

#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SAVE_PTR(index, ptr) args.This()->SetInternalField(index, v8::External::New((void *)ptr)); 
#define LOAD_PTR(index, type) reinterpret_cast<type>(v8::Handle<v8::External>::Cast(args.This()->GetInternalField(index))->Value());
#define SAVE_VALUE(index, val) args.This()->SetInternalField(index, val)
#define LOAD_VALUE(index) args.This()->GetInternalField(index)
#define JS_STR(...) v8::String::New(__VA_ARGS__)
#define JS_INT(val) v8::Integer::New(val)
#define JS_FLOAT(val) v8::Number::New(val)
#define JS_BOOL(val) v8::Boolean::New(val)
#define JS_METHOD(name) v8::Handle<v8::Value> name(const v8::Arguments& args)
#define JS_EXCEPTION(reason) v8::ThrowException(JS_STR(reason))
#define JS_GLOBAL v8::Context::GetCurrent()->Global()

#ifdef _WIN32
#   define SHARED_INIT() extern "C" __declspec(dllexport) void init(v8::Handle<v8::Object> target)
#else
#   define SHARED_INIT() extern "C" void init(v8::Handle<v8::Object> target)
#endif

inline v8::Handle<v8::Array> JS_CHARARRAY(char * data, int count) {
	v8::Handle<v8::Array> arr = v8::Array::New(count);
	char ch;
	for (int i=0;i<count;i++) {
		ch = data[i];
		arr->Set(v8::Integer::New(i), v8::Integer::New((int)((unsigned char)data[i])));
	}
	return arr;
}

inline void * my_read(char * name, size_t * size) {
	int f = open(name, O_RDONLY);
	if (f == -1) { return NULL; }
	*size = lseek(f, 0, SEEK_END);
	void * data = mmap(0, *size, PROT_READ, MAP_SHARED, f, 0);
	close(f);
	return data;
}

inline void my_free(void * data, size_t size) {
	munmap(data, size);
}

inline int my_write(char * name, void * data, size_t size) {
	int f = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (f == -1) { return -1; }
	lseek(f, size - 1, SEEK_SET);
	write(f, "", 1);
		
	void * dst = mmap(0, size, PROT_WRITE, MAP_SHARED, f, 0);
	memcpy(dst, data, size);
	munmap(dst, size);
	close(f);
	return 0;
}

#endif

