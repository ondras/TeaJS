#ifndef _BYTESTORAGE_B_H
#define _BYTESTORAGE_B_H

#include <v8.h>
#include "macros.h"

#define BS_OTHER(object) LOAD_PTR_FROM(object, 0, ByteStorageB *)
#define BS_THIS BS_OTHER(args.This())

/**
 * Generic byte storage class
 */
class ByteStorageB {
public:
	ByteStorageB();
	ByteStorageB(v8::Handle<v8::Array>);
	ByteStorageB(size_t len);
	ByteStorageB(ByteStorageB * bs);
	ByteStorageB(unsigned char * data, size_t len);
	ByteStorageB(ByteStorageB * bs, size_t index1, size_t index2);

	virtual ~ByteStorageB();
	
	unsigned char * getData();
	size_t getLength();
	unsigned char getByte(size_t index);

	void setByte(size_t index, unsigned char byte);
	int indexOf(unsigned char value, size_t start, size_t end, int direction);
	ByteStorageB * transcode(const char * from, const char * to);
	v8::Handle<v8::String> toString();
	void resize(size_t newLength, bool zeroFill);
	void reverse();
	void splice(size_t start, size_t howMany, const v8::Arguments &args);
	
	void push(unsigned char byte);
	void push(ByteStorageB * bs);
	unsigned char pop();
	void unshift(unsigned char byte);
	void unshift(ByteStorageB * bs);
	unsigned char shift();

protected:

private:
	unsigned char * data;
	size_t length;
};

#endif
