#include <v8.h>

#define BS_OTHER(object) reinterpret_cast<ByteStorage *>(v8::Handle<v8::External>::Cast((object)->GetInternalField(0))->Value())
#define BS_THIS BS_OTHER(args.This());


/**
 * Generic byte storage class
 */
class ByteStorage {
public:
	ByteStorage();
	ByteStorage(v8::Handle<v8::Array>);
	ByteStorage(ByteStorage * bs);
	virtual ~ByteStorage();
	
	unsigned char * getData();
	size_t getLength();
	unsigned char getByte(size_t index);

protected:

private:
	unsigned char * data;
	size_t length;
};

