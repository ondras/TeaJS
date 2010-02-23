#ifndef _BYTESTORAGE_H
#define _BYTESTORAGE_H

#include <v8.h>
#include <string>
#include <stdlib.h>

class ByteStorageData {
public:
	ByteStorageData(size_t length) {
		this->instances = 1;
		if (length) {
			this->data = (unsigned char *) malloc(length);
			if (!this->data) { throw std::string("Cannot allocate enough memory"); }
		} else {
			this->data = NULL;
		}
	}
	
	~ByteStorageData() {
		if (this->data) { free(this->data); }
	}
	
	size_t getInstances() {
		return this->instances;
	}
	
	void setInstances(size_t instances) {
		this->instances = instances;
	}
	
	unsigned char * getData() {
		return this->data;
	}

private:
	unsigned char * data;
	size_t instances;
};

/**
 * Generic byte storage class. Every Buffer instance has this one.
 */
class ByteStorage {
public:
	ByteStorage(size_t length);
	ByteStorage(unsigned char * data, size_t length); /* new buffer with contents */
	ByteStorage(ByteStorage * master, size_t index1, size_t index2); /* new view/copy */
	~ByteStorage();
	
	ByteStorageData * getStorage();
	
	unsigned char * getData();
	size_t getLength();
	unsigned char getByte(size_t index);
	void setByte(size_t index, unsigned char byte);
	
	void fill(unsigned char fill);
	void fill(unsigned char * data, size_t length);
	
	ByteStorage * transcode(const char * from, const char * to);

protected:

private:
	unsigned char * data;
	size_t length;
	ByteStorageData * storage;
};

#endif
