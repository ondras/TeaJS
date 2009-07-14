/**
 * Socket library. Provides a simple OO abstraction atop several socket-related functions.
 */

#include <v8.h>
#include "js_macros.h"
#include "js_common.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef HAVE_WINSOCK
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  define close(s) closesocket(s)
#  define errno WSAGetLastError()
#  define h_errno WSAGetLastError()
#  define ssize_t SSIZE_T
#else
#  include <unistd.h>
#  include <sys/socket.h>
#  include <sys/un.h>
#  include <sys/param.h>
#  include <arpa/inet.h>
#  include <netinet/in.h>
#  include <netdb.h>
#endif 


#ifndef MAXHOSTNAMELEN
#  define MAXHOSTNAMELEN 64
#endif

#ifndef INVALID_SOCKET
#  define INVALID_SOCKET -1
#endif

#ifndef SOCKET_ERROR
#  define SOCKET_ERROR -1
#endif


namespace {

typedef union sock_addr {
    struct sockaddr_in in;
#ifndef HAVE_WINSOCK
    struct sockaddr_un un;
#endif
    struct sockaddr_in6 in6;
} sock_addr_t;

/**
 * Universal address creator.
 * @param {char *} address Stringified addres
 * @param {int} port Port number
 * @param {int} family Address family
 * @param {sock_addr_t *} result Target data structure
 * @param {socklen_t *} len Result length
 */
inline int create_addr(char * address, int port, int family, sock_addr_t * result, socklen_t * len) {
	unsigned int length = strlen(address);
    switch (family) {
#ifndef HAVE_WINSOCK
		case PF_UNIX: {
			struct sockaddr_un *addr = (struct sockaddr_un*) result;
			memset(addr, 0, sizeof(sockaddr_un));

			if (length >= sizeof(addr->sun_path)) {
				JS_EXCEPTION("Unix socket path too long");
				return 1;
			}
			addr->sun_family = AF_UNIX;
			memcpy(addr->sun_path, address, length);
			addr->sun_path[length] = '\0';
			*len = length + (sizeof(*addr) - sizeof(addr->sun_path));
		} break;
#endif
		case PF_INET: {
			struct sockaddr_in *addr = (struct sockaddr_in*) result;
			memset(addr, 0, sizeof(*addr)); 
			addr->sin_family = AF_INET;

#ifdef HAVE_WINSOCK
			int size = sizeof(struct sockaddr_in);
			int pton_ret = WSAStringToAddress(address, AF_INET, NULL, (sockaddr *) result, &size);
			if (pton_ret != 0) { return 1; }
#else 
			int pton_ret = inet_pton(AF_INET, address, & addr->sin_addr.s_addr);
			if (pton_ret == 0) { return 1; }
#endif

			addr->sin_port = htons((short)port);
			*len = sizeof(*addr);
		} break;
		case PF_INET6: {
			struct sockaddr_in6 *addr = (struct sockaddr_in6*) result;
			memset(addr, 0, sizeof(*addr));
			addr->sin6_family = AF_INET6;

#ifdef HAVE_WINSOCK
			int size = sizeof(struct sockaddr_in6);
			int pton_ret = WSAStringToAddress(address, AF_INET6, NULL, (sockaddr *) result, &size);
			if (pton_ret != 0) { return 1; }
#else 
			int pton_ret = inet_pton(AF_INET6, address, addr->sin6_addr.s6_addr);
			if (pton_ret == 0) { return 1; }
#endif			
			
			addr->sin6_port = htons((short)port);
			*len = sizeof(*addr);
		} break;
    }
	return 0;
}

/**
 * Returns JS array with values describing remote address.
 * For UNIX socket, only one item is present. For AF_INET and
 * AF_INET6, array contains [address, port].
 */
inline v8::Handle<v8::Value> create_peer(sockaddr * addr) {
    switch (addr->sa_family) {
#ifndef HAVE_WINSOCK
		case AF_UNIX: {
			v8::Handle<v8::Array> result = v8::Array::New(1);
			sockaddr_un * addr_un = (sockaddr_un *) addr;
			result->Set(JS_INT(0), JS_STR(addr_un->sun_path));
			return result;
		} break;
#endif
		case AF_INET6: {
			v8::Handle<v8::Array> result = v8::Array::New(2);
			char * buf = new char[INET6_ADDRSTRLEN];
			sockaddr_in6 * addr_in6 = (sockaddr_in6 *) addr;

#ifdef HAVE_WINSOCK
			DWORD len = INET6_ADDRSTRLEN;
			WSAAddressToString(addr, sizeof(struct sockaddr), NULL, buf, &len);
#else			
			inet_ntop(AF_INET6, addr_in6->sin6_addr.s6_addr, buf, INET6_ADDRSTRLEN);
#endif
			
			result->Set(JS_INT(0), JS_STR(buf));
			result->Set(JS_INT(1), JS_INT(ntohs(addr_in6->sin6_port)));
			delete[] buf;
			return result;
		} break;
		case AF_INET: {
			v8::Handle<v8::Array> result = v8::Array::New(2);
			char * buf = new char[INET_ADDRSTRLEN];
			sockaddr_in * addr_in = (sockaddr_in *) addr;

#ifdef HAVE_WINSOCK
			DWORD len = INET_ADDRSTRLEN;
			WSAAddressToString(addr, sizeof(struct sockaddr), NULL, buf, &len);
#else			
			inet_ntop(AF_INET, & addr_in->sin_addr.s_addr, buf, INET_ADDRSTRLEN);
#endif
			result->Set(JS_INT(0), JS_STR(buf));
			result->Set(JS_INT(1), JS_INT(ntohs(addr_in->sin_port)));
			delete[] buf;
			return result;
		} break;
	}
    return v8::Undefined();
}

/**
 * Socket constructor
 * @param {int} family
 * @param {int} type
 * @param {int} [proto]
 */
JS_METHOD(_socket) {
	ASSERT_CONSTRUCTOR;
	if (args.Length() < 2) { return JS_EXCEPTION("Invalid call format. Use 'new Socket(family, type, [proto])'"); }						
	
	int offset = (args[0]->IsExternal() ? 1 : 0);
	int family = args[offset + 0]->Int32Value();
	int type = args[offset + 1]->Int32Value();
	int proto = args[offset + 2]->Int32Value();
	int s = -1;
	
	if (args[0]->IsExternal()) {	
		v8::Handle<v8::External> tmp = v8::Handle<v8::External>::Cast(args[0]);
		s = *((int *) tmp->Value());
	} else {
		s = socket(family, type, proto);
	}
	SAVE_VALUE(0, JS_INT(s));
	SAVE_VALUE(1, JS_BOOL(false));
	args.This()->Set(JS_STR("family"), JS_INT(family));
	args.This()->Set(JS_STR("type"), JS_INT(type));
	args.This()->Set(JS_STR("proto"), JS_INT(proto));									
	
	if (s == INVALID_SOCKET) {
		return JS_EXCEPTION(strerror(errno));
	} else {
		return args.This();
	}
}

JS_METHOD(_getprotobyname) {
	v8::String::Utf8Value name(args[0]);
	struct protoent * result = getprotobyname(*name);
	if (result) {
		return JS_INT(result->p_proto);
	} else {
		return JS_EXCEPTION("Cannot retrieve protocol number");
	}
}

JS_METHOD(_getaddrinfo) {
	v8::String::Utf8Value name(args[0]);
	int family = args[1]->IntegerValue();
	
	struct addrinfo hints, * servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;

	int result = getaddrinfo(*name, NULL, &hints, &servinfo);
	if (result != 0) {
		return JS_EXCEPTION(gai_strerror(result));
	}
	
	v8::Local<v8::Object> item = create_peer(servinfo->ai_addr)->ToObject();
	freeaddrinfo(servinfo);
	return item->Get(JS_INT(0));
}

JS_METHOD(_getnameinfo) {
	v8::String::Utf8Value name(args[0]);
	int family = args[1]->IntegerValue();
	if (family == 0) { family = PF_INET; }

	char hostname[NI_MAXHOST];
    sock_addr_t addr;
    socklen_t len = 0;

	int result = create_addr(*name, 0, family, &addr, &len);
	if (result != 0) {
		return JS_EXCEPTION("Malformed address");
	}
	
	result = getnameinfo((sockaddr *) & addr, len, hostname, NI_MAXHOST, NULL, 0, 0);
	if (result != 0) {
		return JS_EXCEPTION(gai_strerror(result));
	} else {
		return JS_STR(hostname);
	}
}

JS_METHOD(_gethostname) {
	v8::HandleScope handle_scope;
    char * buf = new char[MAXHOSTNAMELEN+1];
    gethostname(buf, MAXHOSTNAMELEN);
	v8::Handle<v8::Value> result = JS_STR(buf);
	delete[] buf;
	return result;
}

JS_METHOD(_connect) {
	int family = args.This()->Get(JS_STR("family"))->Int32Value();
	int sock = LOAD_VALUE(0)->Int32Value();

	int argcount = 1;
	if (family != PF_UNIX) { argcount = 2; }
	if (args.Length() < argcount) {
		return JS_EXCEPTION("Bad argument count. Use 'socket.connect(address, [port])'");
	}
	
	v8::String::Utf8Value address(args[0]);
	int port = args[1]->Int32Value();
    sock_addr_t addr;
    socklen_t len = 0;
    
	int result = create_addr(* address, port, family, &addr, &len);
	if (result != 0) {
        return JS_EXCEPTION("Malformed address");
	}
	
	result = connect(sock, (sockaddr *) &addr, len);
    if (result) {
        return JS_EXCEPTION(strerror(errno));
    } else {
		return args.This();
    }
}

JS_METHOD(_bind) {
	int family = args.This()->Get(JS_STR("family"))->Int32Value();
	int sock = LOAD_VALUE(0)->Int32Value();

	if (args.Length() < 1) {
		return JS_EXCEPTION("Bad argument count. Use 'socket.bind(address, [port])'");
	}
	
	v8::String::Utf8Value address(args[0]);
	int port = args[1]->Int32Value();
    sock_addr_t addr;
    socklen_t len = 0;
    int result = create_addr(*address, port, family, &addr, &len);
	if (result != 0) {
		return JS_EXCEPTION("Malformed address");
	}

	result = bind(sock, (sockaddr *) &addr, len);
    if (result) {
        return JS_EXCEPTION(strerror(errno));
    } else {
		return args.This();
    }
}

JS_METHOD(_listen) {
	int sock = LOAD_VALUE(0)->Int32Value();

	int num = args[0]->Int32Value();
	if (args.Length() == 0) { num = 5; }
	
	int result = listen(sock, num);
    if (result) {
        return JS_EXCEPTION(strerror(errno));
    } else {
		return args.This();
    }
}

JS_METHOD(_accept) {
	int sock = LOAD_VALUE(0)->Int32Value();

	int sock2 = accept(sock, NULL, NULL);
    if (sock2 == INVALID_SOCKET) {
        return JS_EXCEPTION(strerror(errno));
    } else {
		v8::Handle<v8::Value> argv[4];
		argv[0] = v8::External::New(&sock2); // dummy field
		argv[1] = args.This()->Get(JS_STR("family"));
		argv[2] = args.This()->Get(JS_STR("type"));
		argv[3] = args.This()->Get(JS_STR("proto"));
		v8::Handle<v8::Value> s = JS_GLOBAL->Get(JS_STR("Socket"));
		v8::Handle<v8::Function> news = v8::Handle<v8::Function>::Cast(s);
		return news->NewInstance(4, argv);
    }
}

JS_METHOD(_send) {
	int sock = LOAD_VALUE(0)->Int32Value();

	if (args.Length() < 1) {
		return JS_EXCEPTION("Bad argument count. Use 'socket.send(data, [address], [port])'");
	}
	
	v8::String::Utf8Value data(args[0]);
	
	sock_addr_t taddr;
	sockaddr * target = NULL;
	socklen_t len = 0;
	
	if (args.Length() > 1) {
		int family = args.This()->Get(JS_STR("family"))->Int32Value();
		v8::String::Utf8Value address(args[1]);
		int port = args[2]->Int32Value();
		int r = create_addr(*address, port, family, &taddr, &len);
		if (r != 0) {
			return JS_EXCEPTION("Malformed address");
		}
		target = (sockaddr *) &taddr;
	}
	
	ssize_t result = sendto(sock, *data, data.length(), 0, target, len);
    if (result == SOCKET_ERROR) {
        return JS_EXCEPTION(strerror(errno));
    } else {
		return args.This();
    }
}

JS_METHOD(_receive) {
	int sock = LOAD_VALUE(0)->Int32Value();
	int count = args[0]->Int32Value();
	int type = args.This()->Get(JS_STR("type"))->Int32Value();
	
	char * data = new char[count];
    sock_addr_t addr;
    socklen_t len = 0;

	ssize_t result = recvfrom(sock, data, count, 0, (sockaddr *) &addr, &len);
    if (result == SOCKET_ERROR) {
		delete[] data;
        return JS_EXCEPTION(strerror(errno));
    } else {
		v8::Handle<v8::Value> output;
		
		if (args.Length() > 1 && args[1]->IsTrue()) {
			output = JS_CHARARRAY((char *) data, result);
		} else {
			output = JS_STR(data, result);
		}
		
		v8::Handle<v8::Value> text = JS_STR(data, result);
		delete[] data;
		if (type == SOCK_DGRAM) { SAVE_VALUE(1, create_peer((sockaddr *) &addr)); }
		return output;
    }
}

JS_METHOD(_socketclose) {
	int sock = LOAD_VALUE(0)->Int32Value();
	
	int result = close(sock);
    if (result == SOCKET_ERROR) {
        return JS_EXCEPTION(strerror(errno));
    } else {
		return v8::Undefined();
    }
}

JS_METHOD(_setoption) {
	if (args.Length() != 2) {
		return JS_EXCEPTION("Bad argument count. Use 'socket.setOption(name, value)'");
	}
	int sock = LOAD_VALUE(0)->Int32Value();
	int name = args[0]->Int32Value();
	int value = args[1]->Int32Value();

    int result = setsockopt(sock, SOL_SOCKET, name, (char *) &value, sizeof(int));
	if (result == 0) {
        return args.This();
    } else {
        return JS_EXCEPTION(strerror(errno));
    }
}

JS_METHOD(_getoption) {
	if (args.Length() < 1) {
		return JS_EXCEPTION("Bad argument count. Use 'socket.getOption(name, [length])'");
	}
	int sock = LOAD_VALUE(0)->Int32Value();
	int name = args[0]->Int32Value();

    if (args.Length() == 2) {
		int length = args[1]->Int32Value();
        char * buf = new char[length];
		int result = getsockopt(sock, SOL_SOCKET, name, buf, (socklen_t *) &length);
		if (result == 0) {
			v8::Handle<v8::Value> response = JS_STR(buf, length);
			delete[] buf;
            return response;
        } else {
			delete[] buf;
			return JS_EXCEPTION(strerror(errno));
        }
    } else {
        unsigned int buf;
        int length = sizeof(buf);
		int result = getsockopt(sock, SOL_SOCKET, name, (char *) &buf, (socklen_t *) &length);
		if (result == 0) {
            return JS_INT(buf);
        } else {
			return JS_EXCEPTION(strerror(errno));
        }
    }
}

JS_METHOD(_getpeername) {
	int sock = LOAD_VALUE(0)->Int32Value();

	if (!LOAD_VALUE(1)->IsTrue()) {
	    sock_addr_t addr;
		socklen_t len = sizeof(sock_addr_t);
		int result = getpeername(sock, (sockaddr *) &addr, &len);
		if (result == 0) {
			SAVE_VALUE(1, create_peer((sockaddr *) &addr));
		} else {
			return JS_EXCEPTION(strerror(errno));
		}
	}
	
	return LOAD_VALUE(1);
}

}

SHARED_INIT() {
	v8::HandleScope handle_scope;

#ifdef HAVE_WINSOCK
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    WSAStartup(wVersionRequested, &wsaData);
#endif

	v8::Handle<v8::FunctionTemplate> ft = v8::FunctionTemplate::New(_socket);
	ft->SetClassName(JS_STR("Socket"));
	
	/**
	 * Constants (Socket.*)
	 */
	ft->Set(JS_STR("PF_INET"), JS_INT(PF_INET)); 
	ft->Set(JS_STR("PF_INET6"), JS_INT(PF_INET6)); 
	ft->Set(JS_STR("PF_UNIX"), JS_INT(PF_UNIX)); 
	ft->Set(JS_STR("IPPROTO_TCP"), JS_INT(IPPROTO_TCP)); 
	ft->Set(JS_STR("IPPROTO_UDP"), JS_INT(IPPROTO_UDP)); 
	ft->Set(JS_STR("SOCK_STREAM"), JS_INT(SOCK_STREAM)); 
	ft->Set(JS_STR("SOCK_DGRAM"), JS_INT(SOCK_DGRAM)); 
	ft->Set(JS_STR("SOCK_RAW"), JS_INT(SOCK_RAW)); 
	ft->Set(JS_STR("SO_REUSEADDR"), JS_INT(SO_REUSEADDR)); 
	ft->Set(JS_STR("SO_BROADCAST"), JS_INT(SO_BROADCAST)); 
	ft->Set(JS_STR("SO_KEEPALIVE"), JS_INT(SO_KEEPALIVE)); 
	
	ft->Set(JS_STR("getProtoByName"), v8::FunctionTemplate::New(_getprotobyname)->GetFunction()); 
	ft->Set(JS_STR("getAddrInfo"), v8::FunctionTemplate::New(_getaddrinfo)->GetFunction()); 
	ft->Set(JS_STR("getNameInfo"), v8::FunctionTemplate::New(_getnameinfo)->GetFunction()); 
	ft->Set(JS_STR("getHostName"), v8::FunctionTemplate::New(_gethostname)->GetFunction()); 
	
	v8::Handle<v8::ObjectTemplate> it = ft->InstanceTemplate();
	it->SetInternalFieldCount(2); /* sock, peername */

	v8::Handle<v8::ObjectTemplate> pt = ft->PrototypeTemplate();
	
	/**
	 * Prototype methods (new Socket().*)
	 */
	pt->Set("connect", v8::FunctionTemplate::New(_connect));
	pt->Set("send", v8::FunctionTemplate::New(_send));
	pt->Set("receive", v8::FunctionTemplate::New(_receive));
	pt->Set("bind", v8::FunctionTemplate::New(_bind));
	pt->Set("listen", v8::FunctionTemplate::New(_listen));
	pt->Set("accept", v8::FunctionTemplate::New(_accept));
	pt->Set("close", v8::FunctionTemplate::New(_socketclose));
	pt->Set("setOption", v8::FunctionTemplate::New(_setoption));
	pt->Set("getOption", v8::FunctionTemplate::New(_getoption));
	pt->Set("getPeerName", v8::FunctionTemplate::New(_getpeername));

	exports->Set(JS_STR("Socket"), ft->GetFunction());			
}
