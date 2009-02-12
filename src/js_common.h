#ifndef _JS_COMMON_H
#define _JS_COMMON_H

#ifdef HAVE_MMAN_H
#  include <sys/mman.h>
#  include <sys/types.h>
#  include <unistd.h>
#  include <fcntl.h>
#  include <string.h>
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

