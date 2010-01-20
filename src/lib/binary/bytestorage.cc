#include <v8.h>
#include <string.h>
#include "bytestorage.h"
#include "macros.h"

ByteStorage::ByteStorage() {
	this->length = 0;
	this->data = NULL;
}

ByteStorage::ByteStorage(v8::Handle<v8::Array> arr) {
	v8::Handle<v8::Object> arrobj = v8::Handle<v8::Object>::Cast(arr);
	
	size_t len = arr->Length();
	
	this->length = len;
	this->data = (len ? new unsigned char[len] : NULL);
	for (size_t i = 0; i<len;i++) {
		int num = arrobj->Get(JS_INT(i))->IntegerValue();
		this->data[i] = (unsigned char) num;
	}
}

ByteStorage::ByteStorage(ByteStorage * bs) {
	this->length = bs->getLength();
	this->data = new unsigned char[this->length];
	memcpy(this->data, bs->getData(), this->length);
}

ByteStorage::ByteStorage(ByteStorage * bs, size_t index) {
	this->length = 1;
	this->data = new unsigned char[1];
	this->data[0] = bs->getByte(index);
}

ByteStorage::~ByteStorage() {
	delete[] this->data;
}

size_t ByteStorage::getLength() {
	return this->length;
}

unsigned char ByteStorage::getByte(size_t index) {
	if (index >= this->length) { return NULL; }
	return this->data[index];
}

unsigned char * ByteStorage::getData() {
	return this->data;
}

int ByteStorage::indexOf(unsigned char value, size_t start, size_t end, int direction) {
	size_t from = MIN(start, end);
	size_t to = MAX(start, end);
	if (from >= this->length) { return -1; }
	if (to >= this->length) { to = this->length-1; }
	
	size_t index = (direction == 1 ? from : to);
	do {
		if (this->data[index] == value) { return index; }
		index += direction;
	} while (index >= from && index <= to);

	return -1;
}
