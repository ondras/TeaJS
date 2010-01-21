#include <v8.h>
#include <string.h>
#include "bytestorage.h"
#include "macros.h"

ByteStorage::ByteStorage() {
	this->length = 0;
	this->data = NULL;
}

/**
 * Create blank with a given length
 */
ByteStorage::ByteStorage(size_t len) {
	this->length = len;
	this->data = new unsigned char[this->length];
	memset(this->data, 0, this->length);
}

/**
 * Create from an array of numbers
 */
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

/**
 * Copy constructor
 */
ByteStorage::ByteStorage(ByteStorage * bs) {
	this->length = bs->getLength();
	this->data = new unsigned char[this->length];
	memcpy(this->data, bs->getData(), this->length);
}

/**
 * Use a given buffer + length
 */
ByteStorage::ByteStorage(unsigned char * data, size_t len) {
	this->length = len;
	this->data = NULL;
	if (len > 0) {
		this->data = new unsigned char[len];
		memcpy(this->data, data, len);
	}
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
		return;
	}

	this->length = MIN(index2, bs->getLength()) - index1;
	this->data = new unsigned char[this->length];
	memcpy(this->data, bs->getData()+index1, this->length);
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
