#include <v8.h>
#include <cerrno>
#include <string.h>
#include <string>
#include <iconv.h>
#include <stdlib.h>
#include "bytestorage.h"
#include "macros.h"

#define ALLOC_ERROR throw std::string("Cannot allocate enough memory")

#ifdef windows
#	define ICONV_INPUT_T const char * 
#else
#	define ICONV_INPUT_T char *
#endif

ByteStorage::ByteStorage() {
	this->length = 0;
	this->data = NULL;
}

/**
 * Create blank with a given length
 */
ByteStorage::ByteStorage(size_t len) {
	this->length = 0;
	this->data = NULL;

	this->resize(len, true);
}

/**
 * Create from an array of numbers
 */
ByteStorage::ByteStorage(v8::Handle<v8::Array> arr) {
	this->length = 0;
	this->data = NULL;
	v8::Handle<v8::Object> arrobj = v8::Handle<v8::Object>::Cast(arr);
	size_t len = arr->Length();
	this->resize(len, false);

	for (size_t i = 0; i<len;i++) {
		int num = arrobj->Get(JS_INT(i))->IntegerValue();
		this->data[i] = (unsigned char) num;
	}
}

/**
 * Copy constructor
 */
ByteStorage::ByteStorage(ByteStorage * bs) {
	this->length = 0;
	this->data = NULL;
	
	this->resize(bs->getLength(), false);
	memcpy(this->data, bs->getData(), this->length);
}

/**
 * Use a given buffer + length
 */
ByteStorage::ByteStorage(unsigned char * data, size_t len) {
	this->length = 0;
	this->data = NULL;
	
	this->resize(len, false);
	memcpy(this->data, data, len);
}

/**
 * Copy a portion of other bytestorage
 * @param {ByteStorage *}
 * @param {size_t} index1 where to start
 * @param {size_t} index2 end pointer (this will NOT be copied)
 */
ByteStorage::ByteStorage(ByteStorage * bs, size_t index1, size_t index2) {
	this->length = 0;
	this->data = NULL;
	
	if (index2 <= index1 || index1 >= bs->getLength()) {
	} else {
		size_t len = MIN(index2, bs->getLength()) - index1;
		this->resize(len, false);
		memcpy(this->data, bs->getData()+index1, len);
	}
}

ByteStorage::~ByteStorage() {
	if (this->length) { free(this->data); }
}

size_t ByteStorage::getLength() {
	return this->length;
}

void ByteStorage::setByte(size_t index, unsigned char byte) {
	this->data[index] = byte;
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

v8::Handle<v8::String> ByteStorage::toString() {
	return JS_STR((const char *)this->data, this->length);
}

void ByteStorage::resize(size_t newLength, bool zeroFill) {
	if (!newLength) {
		if (this->length) { free(this->data); }
		this->data = NULL;
	} else {
		this->data = (unsigned char *) realloc(this->data, newLength);
		if (!this->data) { ALLOC_ERROR; }
		if (zeroFill && newLength > this->length) { memset(this->data + this->length, 0, newLength-this->length); }
	}	
	this->length = newLength;
}
	
void ByteStorage::push(unsigned char byte) {
	this->resize(this->length+1, false);
	this->data[this->length-1] = byte;
}

void ByteStorage::push(ByteStorage * bs) {
	size_t len = bs->getLength();
	if (!len) { return; }
	
	this->resize(this->length + len, false);
	memcpy(this->data + (this->length-len), bs->getData(), len);
}	

unsigned char ByteStorage::pop() {
	if (!this->length) { return 0; }
	unsigned char byte = this->data[this->length-1];
	this->resize(this->length-1, false);
	return byte;
}

void ByteStorage::unshift(unsigned char byte) {
	this->resize(this->length+1, false);
	memmove(this->data + 1, this->data, this->length-1);
	this->data[0] = byte;
}

void ByteStorage::unshift(ByteStorage * bs) {
	size_t len = bs->getLength();
	if (!len) { return; }
	
	this->resize(this->length + len, false);
	memcpy(this->data, bs->getData(), len);
}

unsigned char ByteStorage::shift() {
	if (!this->length) { return 0; }
	unsigned char byte = this->data[0];
	
	memmove(this->data, this->data + 1, this->length-1);
	this->resize(this->length-1, false);
	return byte;
}

void ByteStorage::reverse() {
	if (!this->length) { return; }
	size_t b = this->length;
	unsigned char byte;

	for (size_t a=0;a<--b;a++) {
		byte = this->data[a];
		this->data[a] = this->data[b];
		this->data[b] = byte;
	}
}

void ByteStorage::splice(size_t start, size_t howMany, const v8::Arguments &args) {
	if (start >= this->length) { return; }
	size_t end = start+howMany;
	if (end > this->length) { end = this->length; }

	/* cut existing data */
	if (howMany && end < this->length) {
		memmove(this->data + start, this->data + end, this->length-end);
	}
	this->resize(this->length - howMany, false);
	
	/* resize to accomodate new elements */
	int added = args.Length()-2;
	if (added <= 0) { return; }
	this->resize(this->length + added, false);
	memmove(this->data + start + added, this->data + start, added);
	
	unsigned char byte;
	for (int i=2; i<args.Length(); i++) {
		byte = (unsigned char) args[i]->IntegerValue();
		this->data[start+i-2] = byte;
	}
	
}

ByteStorage * ByteStorage::transcode(const char * from, const char * to) {
	/* no data */
	if (!this->length) { return new ByteStorage(); }

	/* source and target are the same -> copy */
	if ((from == to) || (from && to && (strcasecmp(from, to) == 0))) {
		return new ByteStorage(this);
	}

	iconv_t cd = iconv_open(to, from);
	if (cd == (iconv_t)(-1)) { 
		std::string error = "Cannot transcode from ";
		error += from;
		error += " to ";
		error += to;
		throw error;
	}
	
	size_t allocated = this->length + (this->length/8) + 32; /* WAG */
	char * output = (char *) malloc(allocated);
	if (!output) {
		iconv_close(cd);
		ALLOC_ERROR;
	}
	
	size_t inBytesLeft = this->length;
	size_t outBytesLeft = allocated;
	ICONV_INPUT_T inBuf = (ICONV_INPUT_T) this->data;
	char * outBuf = output;

	size_t result = 0;
	do {
		result = iconv(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
		if (result == (size_t)(-1)) {
			switch (errno) {
				case E2BIG: {
					/* estimate a new buffer size */
					size_t newAllocated = allocated + inBytesLeft + (inBytesLeft/4) + 32; /* WAG -- +32 implies output charset cannot exceed 32 bytes per character */

					char * newOutput = (char *) realloc(output, newAllocated);
					if (!newOutput) {
						free(output);
						iconv_close(cd);
						ALLOC_ERROR;
					}

					/* so far, outBuf-output bytes were used; move outBuf to this position in newOutput */
					outBuf = newOutput + (outBuf - output);

					/* adjust target pointer */
					output = newOutput;

					/* we allocated this much new bytes */
					outBytesLeft += newAllocated - allocated;
					allocated = newAllocated;
				} break;

				default: {
					free(output);
					iconv_close(cd);
					std::string error = "Transcoding error at source byte ";
					
					size_t tmpSize = 100;
					char * tmp = (char *) malloc(tmpSize);
					if (tmp) {
						size_t result = snprintf(tmp, tmpSize, "%zu", inBuf-(char *)this->data);
						if (result < tmpSize) { error += tmp; }
						free(tmp);
					}
					error += " - ";
					switch (errno) {
						case EILSEQ: 
							error += "an invalid multibyte sequence has been encountered in the input";
						break;
						case EINVAL:
							error += "an incomplete multibyte sequence has been encountered in the input";
						default:
							error += "unknown error";
						break;
					}
					throw error;
				} break;
			}
		}
	} while (result == (size_t)(-1));

	iconv_close(cd);

	/* this is the resulting length */
	size_t len = outBuf - output;
	ByteStorage * bs = new ByteStorage((unsigned char *) output, len);

	free(output);
	return bs;
}
