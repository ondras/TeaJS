#ifndef _JS_COMMON_H
#define _JS_COMMON_H

void * mmap_read(char * name, size_t * size);
void mmap_free(char * data, size_t size);
int mmap_write(char * name, void * data, size_t size);

#endif

