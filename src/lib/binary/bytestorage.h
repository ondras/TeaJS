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
			this->data = (char *) malloc(length);
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
	
	char * getData() {
		return this->data;
	}

private:
	char * data;
	size_t instances;
};

/**
 * Generic byte storage class. Every Buffer instance has this one.
 */
class ByteStorage {
public:
	ByteStorage(size_t length); /* empty */
	ByteStorage(char * data, size_t length); /* with contents (copied) */
	ByteStorage(ByteStorage * master, size_t index1, size_t index2); /* new view */
	~ByteStorage();
	
	ByteStorageData * getStorage();
	
	char * getData();
	size_t getLength();
	char getByte(size_t index);
	void setByte(size_t index, char byte);
	
	void fill(char fill);
	void fill(char * data, size_t length);
	
	ByteStorage * transcode(const char * from, const char * to);

protected:

private:
	char * data;
	size_t length;
	ByteStorageData * storage;
};

#endif
