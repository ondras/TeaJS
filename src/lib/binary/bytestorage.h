#include <v8.h>

#define BS_OTHER(object) reinterpret_cast<ByteStorage *>(v8::Handle<v8::External>::Cast((object)->GetInternalField(0))->Value())
#define BS_THIS BS_OTHER(args.This())


/**
 * Generic byte storage class
 */
class ByteStorage {
public:
	ByteStorage();
	ByteStorage(v8::Handle<v8::Array>);
	ByteStorage(ByteStorage * bs);
	ByteStorage(ByteStorage * bs, size_t index);
	virtual ~ByteStorage();
	
	unsigned char * getData();
	size_t getLength();
	unsigned char getByte(size_t index);
	int indexOf(unsigned char value, size_t start, size_t end, int direction);

protected:

private:
	unsigned char * data;
	size_t length;
};

