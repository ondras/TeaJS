#include <v8.h>
#include <stdlib.h>

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
