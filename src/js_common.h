#ifndef _JS_COMMON_H
#define _JS_COMMON_H

inline v8::Handle<v8::Array> JS_CHARARRAY(char * data, int count) {
	v8::Handle<v8::Array> arr = v8::Array::New(count);
	char ch;
	for (int i=0;i<count;i++) {
		ch = data[i];
		arr->Set(v8::Integer::New(i), v8::Integer::New((int)((unsigned char)data[i])));
	}
	return arr;
}

void * mmap_read(char * name, size_t * size);
void mmap_free(char * data, size_t size);
int mmap_write(char * name, void * data, size_t size);

#endif

