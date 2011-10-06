/**
 * TLS library. TLS wraps a (connected) socket.
 */

#include <v8.h>
#include "macros.h"
#include "common.h"
#include <string>

#include <openssl/ssl.h>
#include <openssl/err.h>
#define NOT_SOCKET JS_TYPE_ERROR("Invalid call format. Use 'new TLS(socket)'")
#define LOAD_SOCKET LOAD_VALUE(0)->ToObject()->GetInternalField(0)->Int32Value()
#define LOAD_SSL LOAD_PTR(1, SSL *)
#define SSL_ERROR(ssl, ret) JS_ERROR(formatError(ssl, ret).c_str())

namespace {
	
SSL_CTX * ctx;

std::string formatError(SSL * ssl, int ret) {
    char string[120];
    ERR_error_string_n(SSL_get_error(ssl, ret), string, sizeof(string));
    return std::string(string);
}

void finalize(v8::Handle<v8::Object> obj) {
	SSL * ssl = reinterpret_cast<SSL *>(obj->GetPointerFromInternalField(1));
	SSL_free(ssl);
}

/**
 * TLS constructor
 * @param {Socket} socket
 */
JS_METHOD(_tls) {
	ASSERT_CONSTRUCTOR;
	if (args.Length() < 1 || !args[0]->IsObject()) { return NOT_SOCKET; }
	
	v8::Handle<v8::Value> socket = args[0];

	try {
		v8::Handle<v8::Value> socketproto = socket->ToObject()->GetPrototype();
		v8::Handle<v8::Object> socketmodule = APP_PTR->require("socket", "");
		v8::Handle<v8::Value> prototype = socketmodule->Get(JS_STR("Socket"))->ToObject()->Get(JS_STR("prototype"));
		if (!prototype->Equals(socketproto)) { return NOT_SOCKET; }
	} catch (std::string e) { /* for some reasons, the socket module is not available */
		return JS_ERROR("Socket module not available");
	}

	SAVE_VALUE(0, socket);

	SSL * ssl = SSL_new(ctx);
	SSL_set_fd(ssl, LOAD_SOCKET);
	SAVE_PTR(1, ssl);

	GC * gc = GC_PTR;
	gc->add(args.This(), finalize);

	return args.This();
}

JS_METHOD(_getSocket) {
	return LOAD_VALUE(0);
}

JS_METHOD(_verifyCertificate) {
	return JS_INT(SSL_get_verify_result(LOAD_SSL));
}

JS_METHOD(_accept) {
	SSL * ssl = LOAD_SSL;
	int result = SSL_accept(ssl);
	
	if (result == 1) {
		return args.This();
	} else {
		return SSL_ERROR(ssl, result);
	}
}

JS_METHOD(_connect) {
	SSL * ssl = LOAD_SSL;
	int result = SSL_connect(ssl);
	
	if (result == 1) {
		return args.This();
	} else {
		return SSL_ERROR(ssl, result);
	}
}

JS_METHOD(_receive) {
	SSL * ssl = LOAD_SSL;
	int count = args[0]->Int32Value();
	char * data = new char[count];

	ssize_t result = SSL_read(ssl, data, count);
	if (result >= 0) {
		if (result == 0) {
			int ret = SSL_get_error(ssl, result);
			if (ret != SSL_ERROR_ZERO_RETURN)  {
				delete[] data;
				return SSL_ERROR(ssl, result);
			}
		}
		v8::Handle<v8::Value> buffer = JS_BUFFER(data, result);
		delete[] data;
		return buffer;
	} else {
		delete[] data;
        return SSL_ERROR(ssl, result);
	}
}

JS_METHOD(_send) {
	if (args.Length() < 1) { return JS_TYPE_ERROR("Bad argument count. Use 'tls.send(data)'"); }
	
	SSL * ssl = LOAD_SSL;
	ssize_t result;
	
	if (IS_BUFFER(args[0])) {
		size_t size = 0;
		char * data = JS_BUFFER_TO_CHAR(args[0], &size);	
		result = SSL_write(ssl, data, size);
	} else {
		v8::String::Utf8Value data(args[0]);
		result = SSL_write(ssl, *data, data.length());
	}
	
	if (result > 0) {
		return args.This();
	} else {
		return SSL_ERROR(ssl, result);
	}
}

JS_METHOD(_close) {
	SSL * ssl = LOAD_SSL;
	int result = SSL_shutdown(ssl);
	
	if (result == 0) { return _close(args); }
	
	if (result > 0) {
		return args.This();
	} else {
		return SSL_ERROR(ssl, result);
	}
}

}

SHARED_INIT() {
	SSL_library_init();
	SSL_load_error_strings();
	ctx = SSL_CTX_new(TLSv1_method());

	v8::HandleScope handle_scope;

	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_tls);
	ft->SetClassName(JS_STR("TLS"));
	
	v8::Handle<v8::ObjectTemplate> it = ft->InstanceTemplate();
	it->SetInternalFieldCount(2); /* socket, ssl */

	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
	
	/**
	 * Prototype methods (new TLS().*)
	 */
	pt->Set("getSocket", v8::FunctionTemplate::New(_getSocket));
	pt->Set("verifyCertificate", v8::FunctionTemplate::New(_verifyCertificate));	
	pt->Set("accept", v8::FunctionTemplate::New(_accept));
	pt->Set("connect", v8::FunctionTemplate::New(_connect));
	pt->Set("receive", v8::FunctionTemplate::New(_receive));
	pt->Set("send", v8::FunctionTemplate::New(_send));
	pt->Set("close", v8::FunctionTemplate::New(_close));

	exports->Set(JS_STR("TLS"), ft->GetFunction());
}
