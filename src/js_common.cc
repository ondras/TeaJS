#include <v8.h>
#include <stdlib.h>
#include <string.h>
#include "js_common.h"

v8::Handle<v8::Array> char2array(char * data, int count) {
	v8::Handle<v8::Array> arr = v8::Array::New(count);
	char ch;
	for (int i=0;i<count;i++) {
		ch = data[i];
		arr->Set(v8::Integer::New(i), v8::Integer::New((int)((unsigned char)data[i])));
	}
	return arr;
}

v8::Handle<v8::String> char2string(char * data, int count) {
	return v8::String::New(data, count);
}

/**
 * count:
 *   -1 - read all bytes
 *    0 - read until newline
 *   >0 - read `count` bytes
 */ 
size_t afread(char ** ptr, size_t count, FILE * stream) {
	size_t limit = 1024;
	char * buffer = (char *) malloc(limit * sizeof(char));
	size_t size = 0; /* num of received bytes */
	bool done = false;
	
	switch (count) {
		case -1: /* whole file */
			size_t tmp;
			do {
				tmp = fread(buffer, sizeof(char), limit, stream);
				if (tmp) {
					size += tmp;
					*ptr = (char *) realloc(*ptr, size);
					strncpy(*ptr, buffer, tmp);
				} else { done = true; }
			} while (!done);
		break;
		
		case 0: /* one line */
			char ch;
			do {
				size++;
				ch = (char) fgetc(stream);
				*ptr = (char *) realloc(*ptr, size);
				(*ptr)[size-1] = ch;
			} while (ch != '\n');
			
		break;
		
		default: /* `count` bytes */
			*ptr = (char *) malloc(count * sizeof(char));
			size = fread(*ptr, sizeof(char), count, stream);
		break;
	}

	return size;
}
