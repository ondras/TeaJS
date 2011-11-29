/**
 * Socket library. Provides a simple OO abstraction atop several socket-related functions.
 */

#include <v8.h>
#include "macros.h"
#include "common.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#ifdef windows
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  define close(s) closesocket(s)
#else
#  include <unistd.h>
#  include <sys/socket.h>
#  include <sys/un.h>
#  include <sys/param.h>
#  include <arpa/inet.h>
#  include <netinet/in.h>
#  include <netinet/tcp.h>
#  include <netdb.h>
#endif 

#ifndef EWOULDBLOCK
#  define EWOULDBLOCK EAGAIN
#endif

#ifndef EINPROGRESS
#  define EINPROGRESS WSAEINPROGRESS
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

v8::Handle<v8::Value> FormatError() {
#ifdef windows
	int size = 0xFF;
	char buf[size];
	buf[size-1] = '\0';
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, WSAGetLastError(), 0, buf, size-1, NULL);
	return JS_ERROR(buf);
#else
	return JS_ERROR(strerror(errno));
#endif
}

namespace {

#ifndef HAVE_PTON
int inet_pton(int family, const char *src, void *dst) {
	struct addrinfo hints, *res, *ressave;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = family;
	if (getaddrinfo(src, NULL, &hints, &res) != 0) { return 0; }
	
	if (family == PF_INET) {
		memcpy(dst, &((sockaddr_in *) res->ai_addr)->sin_addr.s_addr, sizeof(struct in_addr));
	} else {
		memcpy(dst, &((sockaddr_in6 *) res->ai_addr)->sin6_addr.s6_addr, sizeof(struct in6_addr));
	}

	freeaddrinfo(ressave);
	return 1;
}
#endif

#ifndef HAVE_NTOP
const char * inet_ntop(int family, const void *src, char *dst, socklen_t cnt) {
    switch (family) {
		case PF_INET: {
			struct sockaddr_in in;
			memset(&in, 0, sizeof(in));
			in.sin_family = PF_INET;
			memcpy(&in.sin_addr, src, sizeof(struct in_addr));
			getnameinfo((struct sockaddr *)&in, sizeof(struct sockaddr_in), dst, cnt, NULL, 0, NI_NUMERICHOST);
			return dst;
		}
		case PF_INET6: {
			struct sockaddr_in6 in;
			memset(&in, 0, sizeof(in));
			in.sin6_family = PF_INET6;
			memcpy(&in.sin6_addr, src, sizeof(struct in_addr6));
			getnameinfo((struct sockaddr *)&in, sizeof(struct sockaddr_in6), dst, cnt, NULL, 0, NI_NUMERICHOST);
			return dst;
		}
	}
	return NULL;
}
#endif

v8::Persistent<v8::Function> socketFunc;
v8::Persistent<v8::FunctionTemplate> socketTemplate;

typedef union sock_addr {
    struct sockaddr_in in;
#ifndef windows
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
   switch (family) {
#ifndef windows
		case PF_UNIX: {
			unsigned int length = strlen(address);
 			struct sockaddr_un *addr = (struct sockaddr_un*) result;
			memset(addr, 0, sizeof(sockaddr_un));

			if (length >= sizeof(addr->sun_path)) { return 1; }
			addr->sun_family = PF_UNIX;
			memcpy(addr->sun_path, address, length);
			addr->sun_path[length] = '\0';
			*len = length + (sizeof(*addr) - sizeof(addr->sun_path));
		} break;
#endif
		case PF_INET: {
			struct sockaddr_in *addr = (struct sockaddr_in*) result;
			memset(addr, 0, sizeof(*addr)); 
			addr->sin_family = PF_INET;
			int pton_ret = inet_pton(PF_INET, address, & addr->sin_addr.s_addr);
			if (pton_ret == 0) { return 1; }
			addr->sin_port = htons((short)port);
			*len = sizeof(*addr);
		} break;
		case PF_INET6: {
			struct sockaddr_in6 *addr = (struct sockaddr_in6*) result;
			memset(addr, 0, sizeof(*addr));
			addr->sin6_family = PF_INET6;
			int pton_ret = inet_pton(PF_INET6, address, & addr->sin6_addr.s6_addr);
			if (pton_ret == 0) { return 1; }
			addr->sin6_port = htons((short)port);
			*len = sizeof(*addr);
		} break;
    }
	return 0;
}

/**
 * Returns JS array with values describing remote address.
 * For UNIX socket, only one item is present. For PF_INET and
 * PF_INET6, array contains [address, port].
 */
inline v8::Handle<v8::Value> create_peer(sockaddr * addr) {
    switch (addr->sa_family) {
#ifndef windows
		case PF_UNIX: {
			v8::Handle<v8::Array> result = v8::Array::New(1);
			sockaddr_un * addr_un = (sockaddr_un *) addr;
			result->Set(JS_INT(0), JS_STR(addr_un->sun_path));
			return result;
		} break;
#endif
		case PF_INET6: {
			v8::Handle<v8::Array> result = v8::Array::New(2);
			char * buf = new char[INET6_ADDRSTRLEN];
			sockaddr_in6 * addr_in6 = (sockaddr_in6 *) addr;
			inet_ntop(PF_INET6, addr_in6->sin6_addr.s6_addr, buf, INET6_ADDRSTRLEN);
			result->Set(JS_INT(0), JS_STR(buf));
			result->Set(JS_INT(1), JS_INT(ntohs(addr_in6->sin6_port)));
			delete[] buf;
			return result;
		} break;
		case PF_INET: {
			v8::Handle<v8::Array> result = v8::Array::New(2);
			char * buf = new char[INET_ADDRSTRLEN];
			sockaddr_in * addr_in = (sockaddr_in *) addr;
			inet_ntop(PF_INET, & addr_in->sin_addr.s_addr, buf, INET_ADDRSTRLEN);
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
	if (args.Length() < 2) { return JS_TYPE_ERROR("Invalid call format. Use 'new Socket(family, type, [proto])'"); }
	
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
		return FormatError();
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
		return JS_ERROR("Cannot retrieve protocol number");
	}
}

JS_METHOD(_getaddrinfo) {
	v8::String::Utf8Value name(args[0]);
	int family = args[1]->IntegerValue();
	if (family == 0) { family = PF_INET; }
	
	struct addrinfo hints, * servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;

	int result = getaddrinfo(*name, NULL, &hints, &servinfo);
	if (result != 0) {
		return JS_ERROR(gai_strerror(result));
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
		return JS_ERROR("Malformed address");
	}
	
	result = getnameinfo((sockaddr *) & addr, len, hostname, NI_MAXHOST, NULL, 0, 0);
	if (result != 0) {
		return JS_ERROR(gai_strerror(result));
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

JS_METHOD(_select) {
	if (args.Length() != 4) {
		return JS_TYPE_ERROR("Bad argument count. Socket.select must be called with 4 arguments.");
	}
	
	int max = 0;
	fd_set fds[3];

	/* fill descriptors */
	for (int i=0;i<3;i++) {
		FD_ZERO(&fds[i]);
		
		if (!args[i]->IsArray()) { continue; }
		v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[i]);
		int len = arr->Length();
		for (int j=0;j<len;j++) {
			v8::Handle<v8::Value> member = arr->Get(JS_INT(j));
			if (!INSTANCEOF(member, socketTemplate)) { return JS_ERROR("Arguments must be arrays of Socket instances"); }
			int fd = member->ToObject()->GetInternalField(0)->IntegerValue();
			if (fd > max) { max = fd; }
			FD_SET(fd, &fds[i]);
		}
	}
	
	/* prepare time info */
	timeval * tv = NULL;
	if (!args[3]->IsNull()) {
		int time = args[3]->IntegerValue();
		tv = new timeval;
		tv->tv_sec = time / 1000;
		tv->tv_usec = time % 1000;
	}
	
	
	int ret = select(max+1, &fds[0], &fds[1], &fds[2], tv);
	if (tv != NULL) { delete tv; } /* clean up time */
	if (ret == SOCKET_ERROR) { return FormatError(); }
	
	/* delete unused sockets */
	for (int i=0;i<3;i++) {
		if (!args[i]->IsArray()) { continue; }
		v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(args[i]);
		int len = arr->Length();
		for (int j=0;j<len;j++) {
			v8::Handle<v8::Value> member = arr->Get(JS_INT(j));
			int fd = member->ToObject()->GetInternalField(0)->IntegerValue();
			if (!FD_ISSET(fd, &fds[i])) { arr->ForceDelete(JS_INT(j)); }
		}
	}

	return JS_INT(ret);
}

JS_METHOD(_connect) {
	int family = args.This()->Get(JS_STR("family"))->Int32Value();
	int sock = LOAD_VALUE(0)->Int32Value();

	int argcount = 1;
	if (family != PF_UNIX) { argcount = 2; }
	if (args.Length() < argcount) {
		return JS_TYPE_ERROR("Bad argument count. Use 'socket.connect(address, [port])'");
	}
	
	v8::String::Utf8Value address(args[0]);
	int port = args[1]->Int32Value();
	sock_addr_t addr;
	socklen_t len = 0;

	int result = create_addr(*address, port, family, &addr, &len);
	if (result != 0) {
        return JS_ERROR("Malformed address");
	}
	
	result = connect(sock, (sockaddr *) &addr, len);
	
	if (!result) { return JS_BOOL(true); }
	if (errno == EINPROGRESS) { return JS_BOOL(false); }
	return FormatError();
}

JS_METHOD(_bind) {
	int family = args.This()->Get(JS_STR("family"))->Int32Value();
	int sock = LOAD_VALUE(0)->Int32Value();

	if (args.Length() < 1) {
		return JS_TYPE_ERROR("Bad argument count. Use 'socket.bind(address, [port])'");
	}
	
	v8::String::Utf8Value address(args[0]);
	int port = args[1]->Int32Value();
	sock_addr_t addr;
	socklen_t len = 0;
	int result = create_addr(*address, port, family, &addr, &len);
	if (result != 0) {
		return JS_ERROR("Malformed address");
	}

	result = bind(sock, (sockaddr *) &addr, len);
	if (result) {
		return FormatError();
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
		return FormatError();
	} else {
		return args.This();
	}
}

JS_METHOD(_accept) {
	int sock = LOAD_VALUE(0)->Int32Value();
	int sock2 = accept(sock, NULL, NULL);
	if (sock2 != INVALID_SOCKET) { 
		v8::Handle<v8::Value> argv[4];
		argv[0] = v8::External::New(&sock2); // dummy field
		argv[1] = args.This()->Get(JS_STR("family"));
		argv[2] = args.This()->Get(JS_STR("type"));
		argv[3] = args.This()->Get(JS_STR("proto"));
		return socketFunc->NewInstance(4, argv);
	}
	if (errno == EAGAIN || errno == EWOULDBLOCK) { return JS_BOOL(false); }
	return FormatError();
}

JS_METHOD(_send) {
	int sock = LOAD_VALUE(0)->Int32Value();

	if (args.Length() < 1) {
		return JS_TYPE_ERROR("Bad argument count. Use 'socket.send(data, [address], [port])'");
	}
	
	
	sock_addr_t taddr;
	sockaddr * target = NULL;
	socklen_t len = 0;
	ssize_t result;
	
	if (args.Length() > 1) {
		int family = args.This()->Get(JS_STR("family"))->Int32Value();
		v8::String::Utf8Value address(args[1]);
		int port = args[2]->Int32Value();
		int r = create_addr(*address, port, family, &taddr, &len);
		if (r != 0) { return JS_ERROR("Malformed address"); }
		target = (sockaddr *) &taddr;
	}
	
	if (IS_BUFFER(args[0])) {
		size_t size = 0;
		char * data = JS_BUFFER_TO_CHAR(args[0], &size);
		result = sendto(sock, data, size, 0, target, len);
	} else {
		v8::String::Utf8Value data(args[0]);
		result = sendto(sock, *data, data.length(), 0, target, len);
	}
	
	if (result != SOCKET_ERROR) { return JS_BOOL(true); }
	if (errno == EAGAIN || errno == EWOULDBLOCK) { return JS_BOOL(false); }
	return FormatError();
}

JS_METHOD(_receive) {
	int sock = LOAD_VALUE(0)->Int32Value();
	int count = args[0]->Int32Value();
	int type = args.This()->Get(JS_STR("type"))->Int32Value();
	
	char * data = new char[count];
	sock_addr_t addr;
	socklen_t len = 0;

	ssize_t result = recvfrom(sock, data, count, 0, (sockaddr *) &addr, &len);
	if (result != SOCKET_ERROR) {
		v8::Handle<v8::Value> buffer = JS_BUFFER(data, result);
		delete[] data;
		if (type == SOCK_DGRAM) { SAVE_VALUE(1, create_peer((sockaddr *) &addr)); }
		return buffer;
	}
	
	delete[] data;
	if (errno == EAGAIN || errno == EWOULDBLOCK) { return JS_BOOL(false); }
	return FormatError();
}

JS_METHOD(_socketclose) {
	int sock = LOAD_VALUE(0)->Int32Value();
	
	int result = close(sock);
	if (result == SOCKET_ERROR) {
		return FormatError();
	} else {
		return v8::Undefined();
	}
}

JS_METHOD(_setoption) {
	if (args.Length() != 2) {
		return JS_TYPE_ERROR("Bad argument count. Use 'socket.setOption(name, value)'");
	}
	int sock = LOAD_VALUE(0)->Int32Value();
	int name = args[0]->Int32Value();
	int value = args[1]->Int32Value();

	int level;
	switch (name) {
		case TCP_NODELAY:
			level = IPPROTO_TCP;
		break;
		default:
			level = SOL_SOCKET;
		break;
	}
	
	int result = setsockopt(sock, level, name, (char *) &value, sizeof(int));
	if (result == 0) {
		return args.This();
	} else {
		return FormatError();
	}
}

JS_METHOD(_getoption) {
	if (args.Length() < 1) {
		return JS_TYPE_ERROR("Bad argument count. Use 'socket.getOption(name)'");
	}
	int sock = LOAD_VALUE(0)->Int32Value();
	int name = args[0]->Int32Value();
	int level;
	switch (name) {
		case TCP_NODELAY:
			level = IPPROTO_TCP;
		break;
		default:
			level = SOL_SOCKET;
		break;
	}
	
	int value;
	socklen_t len = sizeof(value);
	int result = getsockopt(sock, level, name, &value, &len);

	if (result != 0) { return FormatError(); }
	if (len != sizeof(value)) { return JS_ERROR("getsockopt returned truncated value"); }
	return JS_INT(value);
}

JS_METHOD(_setblocking) {
	if (args.Length() < 1) {
		return JS_TYPE_ERROR("Bad argument count. Use 'socket.setBlocking(true/false)'");
	}
	
	int sock = LOAD_VALUE(0)->Int32Value();
	
#ifdef windows
	unsigned long flag = !args[0]->ToBoolean()->Value(); /* with ioctlsocket, a non-zero sets nonblocking, a zero sets blocking */
	if (ioctlsocket(sock, FIONBIO, &flag) == SOCKET_ERROR) {
		return FormatError();
	} else {
		return v8::Undefined();
	}

#else 
	int flags = fcntl(sock, F_GETFL);

	if (args[0]->ToBoolean()->Value()) {
		flags &= ~O_NONBLOCK;
	} else {
		flags |= O_NONBLOCK;
	}
	
	if (fcntl(sock, F_SETFL, flags) == -1) {
		return FormatError();
	} else {
		return v8::Undefined();
	}
#endif

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
			return FormatError();
		}
	}
	
	return LOAD_VALUE(1);
}

}

SHARED_INIT() {
	v8::HandleScope handle_scope;

#ifdef windows
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 0);
	WSAStartup(wVersionRequested, &wsaData);
#endif

	socketTemplate = v8::Persistent<v8::FunctionTemplate>::New(v8::FunctionTemplate::New(_socket)); 
	socketTemplate->SetClassName(JS_STR("Socket"));

	/**
	 * Constants (Socket.*)
	 */
	socketTemplate->Set(JS_STR("PF_INET"), JS_INT(PF_INET)); 
	socketTemplate->Set(JS_STR("PF_INET6"), JS_INT(PF_INET6)); 
	socketTemplate->Set(JS_STR("PF_UNIX"), JS_INT(PF_UNIX)); 
	socketTemplate->Set(JS_STR("IPPROTO_TCP"), JS_INT(IPPROTO_TCP)); 
	socketTemplate->Set(JS_STR("IPPROTO_UDP"), JS_INT(IPPROTO_UDP)); 
	socketTemplate->Set(JS_STR("SOCK_STREAM"), JS_INT(SOCK_STREAM)); 
	socketTemplate->Set(JS_STR("SOCK_DGRAM"), JS_INT(SOCK_DGRAM)); 
	socketTemplate->Set(JS_STR("SOCK_RAW"), JS_INT(SOCK_RAW)); 
	socketTemplate->Set(JS_STR("SO_REUSEADDR"), JS_INT(SO_REUSEADDR)); 
	socketTemplate->Set(JS_STR("SO_BROADCAST"), JS_INT(SO_BROADCAST)); 
	socketTemplate->Set(JS_STR("SO_KEEPALIVE"), JS_INT(SO_KEEPALIVE)); 
	socketTemplate->Set(JS_STR("SO_ERROR"), JS_INT(SO_ERROR)); 
	socketTemplate->Set(JS_STR("TCP_NODELAY"), JS_INT(TCP_NODELAY)); 
	
	socketTemplate->Set(JS_STR("getProtoByName"), v8::FunctionTemplate::New(_getprotobyname)->GetFunction()); 
	socketTemplate->Set(JS_STR("getAddrInfo"), v8::FunctionTemplate::New(_getaddrinfo)->GetFunction()); 
	socketTemplate->Set(JS_STR("getNameInfo"), v8::FunctionTemplate::New(_getnameinfo)->GetFunction()); 
	socketTemplate->Set(JS_STR("getHostName"), v8::FunctionTemplate::New(_gethostname)->GetFunction()); 
	socketTemplate->Set(JS_STR("select"), v8::FunctionTemplate::New(_select)->GetFunction()); 
	
	v8::Handle<v8::ObjectTemplate> it = socketTemplate->InstanceTemplate();
	it->SetInternalFieldCount(2); /* sock, peername */

	v8::Handle<v8::ObjectTemplate> pt = socketTemplate->PrototypeTemplate();
	
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
	pt->Set("setBlocking", v8::FunctionTemplate::New(_setblocking));
	pt->Set("getPeerName", v8::FunctionTemplate::New(_getpeername));

	exports->Set(JS_STR("Socket"), socketTemplate->GetFunction());
	socketFunc = v8::Persistent<v8::Function>::New(socketTemplate->GetFunction());
}
