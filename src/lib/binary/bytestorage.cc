#include <v8.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "bytestorage.h"
#include "macros.h"

#define CHECK_ALLOC(ptr) if (!ptr) { throw std::string("Cannot allocate enough memory"); }

ByteStorage::ByteStorage() {
	this->length = 0;
	this->data = NULL;
}

/**
 * Create blank with a given length
 */
ByteStorage::ByteStorage(size_t len) {
	this->data = (unsigned char *) malloc(len);
	CHECK_ALLOC(this->data);

	this->length = len;
	memset(this->data, 0, this->length);
}

/**
 * Create from an array of numbers
 */
ByteStorage::ByteStorage(v8::Handle<v8::Array> arr) {
	v8::Handle<v8::Object> arrobj = v8::Handle<v8::Object>::Cast(arr);
	
	this->data = NULL;
	size_t len = arr->Length();
	
	if (len) {
		this->data = (unsigned char *) malloc(len);
		CHECK_ALLOC(this->data);
	}
	
	this->length = len;
	for (size_t i = 0; i<len;i++) {
		int num = arrobj->Get(JS_INT(i))->IntegerValue();
		this->data[i] = (unsigned char) num;
	}
}

/**
 * Copy constructor
 */
ByteStorage::ByteStorage(ByteStorage * bs) {
	size_t len = bs->getLength();
	this->data = NULL;
	
	if (len) {
		this->data = (unsigned char *) malloc(len);
		CHECK_ALLOC(this->data);
	}
	
	this->length = len;
	memcpy(this->data, bs->getData(), this->length);
}

/**
 * Use a given buffer + length
 */
ByteStorage::ByteStorage(unsigned char * data, size_t len) {
	this->data = NULL;
	if (len > 0) {
		this->data = (unsigned char *) malloc(len);
		CHECK_ALLOC(this->data);
	}

	this->length = len;
	memcpy(this->data, data, len);
}

/**
 * Copy a portion of other bytestorage
 * @param {ByteStorage *}
 * @param {size_t} index1 where to start
 * @param {size_t} index2 end pointer (this will NOT be copied)
 */
ByteStorage::ByteStorage(ByteStorage * bs, size_t index1, size_t index2) {
	if (index2 <= index1 || index1 >= bs->getLength()) {
		this->length = 0;
		this->data = NULL;
	} else {
		size_t len = MIN(index2, bs->getLength()) - index1;
		this->data = (unsigned char *) malloc(len);
		CHECK_ALLOC(this->data);
		
		this->length = len;
		memcpy(this->data, bs->getData()+index1, len);
	}
}

ByteStorage::~ByteStorage() {
	this->length = 0;
	free(this->data);
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

int ByteStorage::indexOf(unsigned char value, size_t index1, size_t index2, int direction) {
	size_t from = index1;
	size_t to = index2;
	
	/* check for values too large */
	if (from >= this->length) { return -1; }
	if (to >= this->length) { to = this->length-1; }
	
	size_t index = (direction == 1 ? from : to);
	do {
		if (this->data[index] == value) { return index; }
		index += direction;
	} while (index >= from && index <= to);

	return -1;
}

ByteStorage * ByteStorage::transcode(const char * from, const char * to) {
	/* FIXME! */
	printf("transcodor.");
	return new ByteStorage(this->data, this->length);
}

v8::Handle<v8::String> ByteStorage::toString() {
	return JS_STR((const char *)this->data, this->length);
}

void ByteStorage::concat(ByteStorage * bs) {
	size_t len = bs->getLength();
	if (!len) { return; }
	
	this->data = (unsigned char *) realloc(this->data, this->length + len);
	CHECK_ALLOC(this->data);
	this->length += len;
	memcpy(this->data, bs->getData(), len);
}
