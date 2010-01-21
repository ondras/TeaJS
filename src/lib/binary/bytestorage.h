#ifndef _BYTESTORAGE_H
#define _BYTESTORAGE_H

#include <v8.h>

#define BS_OTHER(object) reinterpret_cast<ByteStorage *>(object->GetPointerFromInternalField(0))
#define BS_THIS BS_OTHER(args.This())


/**
 * Generic byte storage class
 */
class ByteStorage {
public:
	ByteStorage();
	ByteStorage(v8::Handle<v8::Array>);
	ByteStorage(size_t len);
	ByteStorage(ByteStorage * bs);
	ByteStorage(unsigned char * data, size_t len);
	ByteStorage(ByteStorage * bs, size_t index1, size_t index2);

	virtual ~ByteStorage();
	
	unsigned char * getData();
	size_t getLength();
	unsigned char getByte(size_t index);
	int indexOf(unsigned char value, size_t start, size_t end, int direction);
	ByteStorage * transcode(const char * from, const char * to);
	v8::Handle<v8::String> toString();
	void concat(ByteStorage * bs);

protected:

private:
	unsigned char * data;
	size_t length;
};

#endif
