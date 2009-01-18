#include <v8.h>
#include <stdlib.h>
#include <string.h>
#include "js_macros.h"
#include "js_common.h"

/**
 * count:
 *   -1 - read all bytes
 *    0 - read until newline
 *   >0 - read `count` bytes
 */ 
size_t afread(char ** ptr, size_t count, FILE * stream) {
	char buffer[1024];
	size_t size = 0; /* num of received bytes */
	bool done = false;
	
	switch (count) {
		case -1: /* whole file */
			size_t tmp;
			do {
				tmp = fread(buffer, sizeof(char), sizeof(buffer), stream);
				if (tmp) {
					*ptr = (char *) realloc(*ptr, size+tmp);
					strncpy((*ptr)+size, buffer, tmp);
					size += tmp;
				}
				if (tmp != sizeof(buffer)) { done = true; }
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
