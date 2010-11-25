#include <v8.h>
#include <zlib.h>
#include "macros.h"
#include "string.h"

namespace {

JS_METHOD(_compress) {
	if (args.Length() < 1) { return JS_TYPE_ERROR("Bad argument count. Use 'compress(buffer[, level])'"); }
	if (!IS_BUFFER(args[0])) { return JS_TYPE_ERROR("First argument must be an instance of Buffer"); }
	
	size_t inputLength = 0;
	char * data = JS_BUFFER_TO_CHAR(args[0], &inputLength);
	unsigned long outputLength = compressBound(inputLength);

	char * output = (char*) malloc(outputLength);
	int level = 9;
	if (args.Length() > 1) {
		level = args[1]->IntegerValue();
	}
	compress2((uint8_t*) output, &outputLength, (const uint8_t *) data, inputLength, level);
	
	v8::Handle<v8::Value> buffer = JS_BUFFER(output, outputLength);
	free(output);
	
	return buffer;
}

JS_METHOD(_decompress) {
	if (args.Length() < 1) { return JS_TYPE_ERROR("Bad argument count. Use 'decompress(buffer)'"); }
	if (!IS_BUFFER(args[0])) { return JS_TYPE_ERROR("First argument must be an instance of Buffer"); }

	size_t inputLength = 0;
	char * data = JS_BUFFER_TO_CHAR(args[0], &inputLength);
	
	size_t chunkSize = 8192;
	char * chunk = (char *) malloc(chunkSize);
	char * output = (char *) malloc(chunkSize);
	size_t capacity = chunkSize;
	size_t used = 0;

	z_stream stream;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	stream.avail_in = inputLength;
	stream.next_in = (uint8_t*) data;

	if (inflateInit(&stream) != Z_OK) {
		free(chunk);
		free(output);
		return JS_ERROR("Failed to decompress");
	}
	
	int ret = Z_OK;
	
	do {
		if (stream.avail_in == 0) break;

		do {
			stream.next_out = (uint8_t*) chunk;
			stream.avail_out = chunkSize;
			ret = inflate(&stream, Z_NO_FLUSH);
			switch (ret) {
				case Z_MEM_ERROR:
				case Z_NEED_DICT:
				case Z_DATA_ERROR:
					inflateEnd(&stream);
					free(chunk);
					free(output);
					return JS_ERROR("Failed to decompress");
				break;
			}
			
			size_t dataLength = chunkSize - stream.avail_out;
			if (!dataLength) { continue; }
	
			while ((capacity - used) < dataLength) {
				capacity <<= 1;
				output = (char *) realloc(output, capacity);
			}
			memcpy(output + used, chunk, dataLength);
			used += dataLength;
		} while (stream.avail_out == 0);
	} while (ret != Z_STREAM_END);

	inflateEnd(&stream);
	free(chunk);
	v8::Handle<v8::Value> buffer = JS_BUFFER(output, used);
	free(output);
	return buffer;
}

}

SHARED_INIT() {
	v8::HandleScope handle_scope;
	exports->Set(JS_STR("compress"), v8::FunctionTemplate::New(_compress)->GetFunction());
	exports->Set(JS_STR("decompress"), v8::FunctionTemplate::New(_decompress)->GetFunction());
}


