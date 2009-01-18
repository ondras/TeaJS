#ifndef _JS_COMMON_H
#define _JS_COMMON_H

#include <v8.h>
#ifdef FASTCGI
#  include <fcgi_stdio.h>
#endif

size_t afread(char ** ptr, size_t count, FILE * stream);

#endif
