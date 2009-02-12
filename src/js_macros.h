#ifndef _JS_MACROS_H
#define _JS_MACROS_H

// access()
#ifdef HAVE_UNISTD_H
#	include <unistd.h>
#else
#	include <io.h>
#	define F_OK 0
#	define access(path,mode) _access(path,mode)
#endif

#ifdef HAVE_MMAN_H
#  include <sys/mman.h>
#  include <sys/types.h>
#  include <unistd.h>
#  include <fcntl.h>
#  include <string.h>
#endif

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
#define GLOBAL_PROTO v8::Handle<v8::Object>::Cast(JS_GLOBAL->GetPrototype())
#define APP_PTR reinterpret_cast<v8cgi_App *>(v8::Handle<v8::External>::Cast(GLOBAL_PROTO->GetInternalField(0))->Value());

#ifdef _WIN32
#   define SHARED_INIT() extern "C" __declspec(dllexport) void init(v8::Handle<v8::Object> exports)
#else
#   define SHARED_INIT() extern "C" void init(v8::Handle<v8::Object> exports)
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
#ifdef HAVE_MMAP_H
	int f = open(name, O_RDONLY);
	if (f == -1) { return NULL; }
	*size = lseek(f, 0, SEEK_END);
	void * data = mmap(0, *size, PROT_READ, MAP_SHARED, f, 0);
	close(f);
#else
	FILE * f = fopen(name, "rb");
	if (f == NULL) { return NULL; }
	fseek(f, 0, SEEK_END);
	size_t s = ftell(f);
	*size = s;
	
	rewind(f);
	char * data = new char[s];
	for (unsigned int i=0; i<s;) {
		size_t read = fread(& data[i], 1, s-i, f);
		i += read;
	}
#endif
	return data;
}

inline void my_free(char * data, size_t size) {
#ifdef HAVE_MMAP_H
	munmap(data, size);
#else
	delete[] data;
#endif
}

inline int my_write(char * name, void * data, size_t size) {
#ifdef HAVE_MMAP_H
	int f = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (f == -1) { return -1; }
	lseek(f, size - 1, SEEK_SET);
	write(f, "", 1);
		
	void * dst = mmap(0, size, PROT_WRITE, MAP_SHARED, f, 0);
	memcpy(dst, data, size);
	munmap(dst, size);
	close(f);
#else
	FILE * f = fopen(name, "wb");
	if (f == NULL) { return -1; }
	fwrite(data, size, 1,f);
	fclose(f);
#endif
	return 0;
}

#endif

