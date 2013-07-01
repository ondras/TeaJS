var parseQueryString = function(qs) {
	var result = {};
	var parts = qs.split("&");
	for (var i=0, len=parts.length;i<len;i++) {
		var item = parts[i];
		if (!item) { continue; }
		var eq = item.indexOf("=");
		var name = "";
		var value = "";
		
		if (eq == -1) {
			name = item;
		} else {
			name = item.substring(0,eq);
			value = item.substring(eq+1);
		}
		
		name = decode(name);
		value = decode(value);
		if (name.substring(name.length-2) == "[]") { name = name.substring(0,name.length-2); }
		
		mixIn(result, name, value);
	}
	return result;
}

var decode = function(str) {
	var s = str.replace(/\+/g, " ");
	try { s = decodeURIComponent(s); } catch(e) {} finally { return s; }
}

var mixIn = function(result, name, value) {
	if (!(name in result)) {
		result[name] = value;
	} else if (result[name] instanceof Array) {
		result[name].push(value);
	} else {
		result[name] = [result[name], value];
	}
}

var ServerRequest = function(input, headers) {
	this._input = input;
	this._headers = headers;

	this.get = {};
	this.post = {};
	this.cookie = {};
	this.files = {};

	this.method = null;
	if (this._headers["REQUEST_METHOD"]) { this.method = this._headers["REQUEST_METHOD"].toUpperCase(); }
	if (!this.method) { return; }

	this._parseCookie();
	this.get = parseQueryString(this._headers["QUERY_STRING"] || "");
	if (this.method == "POST") { this._parsePOST(); }
}

ServerRequest.prototype.headers = function() {
	return this._headers;
}

ServerRequest.prototype.header = function(name) {
	var n = "HTTP_" + name.toUpperCase().replace(/-/g,"_");
	return (n in this._headers ? this._headers[n] : null);
}

ServerRequest.prototype._parseCookie = function() {
	if (!("HTTP_COOKIE" in this._headers)) { return; }
	var all = this._headers["HTTP_COOKIE"].split("; ");
	for (var i=0, len=all.length;i<len;i++) {
		var row = all[i];
		var eq = row.indexOf("=");
		var name = row.substring(0,eq);
		var value = row.substring(eq+1);
		if (!this.cookie[name]) { this.cookie[name] = unescape(value); }
	}
}

ServerRequest.prototype._decode = function(str) {
	var s = str;
	try {
		s = decodeURIComponent(str.replace(/\+/g, " "));
	} catch(e) { };
	return s;
}

ServerRequest.prototype._parsePOST = function() {
	var ct = this._headers["CONTENT_TYPE"] || "";
	var length = parseInt(this._headers["CONTENT_LENGTH"], 10);
	if (!length) { return; }

	if (ct.indexOf("application/x-www-form-urlencoded") != -1) {
		var buffer = this._input(length);
		this.post = parseQueryString(buffer.toString("utf-8"));
	} else {
		var boundary = ct.match(/boundary=(.*)/); /* find boundary */
		if (boundary) {
			var buffer = this._input(length);
			this._parseMultipartBuffer(buffer, boundary[1], null);
		}
    }
}

/**
 * @param {Buffer} buffer data
 * @param {boundary} boundary
 * @param {string || null} fieldName form field name
 */
ServerRequest.prototype._parseMultipartBuffer = function(buffer, boundary, fieldName) {
	var boundary1 = "--"+boundary;
	var boundary2 = "\r\n--"+boundary;
	var index1 = 0; /* start of part in buffer */
	var index2 = -1; /* end of part in buffer (start of next boundary) */
	
	while (1) {
		boundary = (index1 ? boundary2 : boundary1); /* 2nd and next boundaries start with newline */
		index2 = buffer.indexOf(boundary, index1);
		if (index2 == -1) { return; } /* no next boundary -> die */
		if (index1 != 0) { /* both boundaries -> process whats between them */
			var headerBreak = buffer.indexOf("\r\n\r\n", index1);
			if (headerBreak == -1) { throw new Error("No header break in multipart component"); }
			var headerView = buffer.range(index1, headerBreak);
			var bodyView = buffer.range(headerBreak+4, index2);
			this._processMultipartItem(headerView, bodyView, fieldName);
		}
		
		index1 = index2 + boundary.length; /* move forward */
	}
}

/**
 * @param {Buffer} header
 * @param {Buffer} body
 * @param {string} fieldName
 */
ServerRequest.prototype._processMultipartItem = function(header, body, fieldName) {
	var headers = {};
	var headerArray = header.toString("utf-8").split("\r\n");
	for (var i=0, len=headerArray.length;i<len;i++) {
		var line = headerArray[i];
		if (!line) { continue; }
		var r = line.match(/([^:]+): *(.*)/);
		if (!r) { throw new Error("Malformed multipart header '"+line+"'"); }

		var name = r[1].replace(/-/g,"_").toUpperCase();
		var value = r[2];
		headers[name] = value;
	}

	var cd = headers["CONTENT_DISPOSITION"] || "";
	var ct = headers["CONTENT_TYPE"] || "";
	var r = cd.match(/ name="(.*?)"/i); /* form field name in header */
	if (r) { fieldName = r[1]; }

	if (ct.match(/multipart\/mixed/i)) { /* recursive processing */
		var boundary = ct.match(/boundary=(.*)/); /* find boundary */
		if (boundary) {
			this._parseMultipartBuffer(body, boundary[1], fieldName);
		}
	} else { /* no recursion: either file or form field */
		var r = cd.match(/filename="(.*?)"/i);
		if (r) { /* file */
			var file = {
				headers: headers,
				originalName: r[1],
				data: body
			};
			mixIn(this.files, fieldName, file);
		} else { /* form field */
			mixIn(this.post, fieldName, body.toString("utf-8"));
		}
	}
}

ServerResponse = function(output, header) {
	this._output = output;
	this._header = header;
	this._outputStarted = false;
	this._ct = false; /* Content-type - the only header which must be present */
}

ServerResponse.prototype.write = function(str) {
	if (!this._outputStarted) {
		if (!this._ct) { this.header({"Content-type":"text/html"}); }
		this._outputStarted = true;
		if (!global.apache) { this._output("\r\n"); }
	}
	this._output(str);
}

ServerResponse.prototype.cookie = function(name, value, expires, path, domain, secure, httponly) {
	if (expires && !(expires instanceof Date)) { return false; }
	var arr = [];
	arr.push(encodeURIComponent(name)+"="+encodeURIComponent(value));
	if (expires) { arr.push("expires="+expires.toGMTString()); }
	if (path) { arr.push("path="+path); }
	if (domain) { arr.push("domain="+domain); }
	if (secure) { arr.push("secure"); }
	if (httponly) { arr.push("httponly"); }

	var str = arr.join("; ");
	this.header({"Set-Cookie":str});
	return true;
}

ServerResponse.prototype.header = function(h) {
	if (this._outputStarted) { throw new Error("Cannot send headers, output already started."); }
	for (var p in h) {
		if (p.match(/content-type/i)) { this._ct = true; }
		if (p.match(/location/i)) { this.status(303, "See Other"); }
		this._header(p, h[p]);
	}
}

ServerResponse.prototype.status = function(number, reason) {
	var text = number.toString();
	if (reason) { text += " "+reason; }
	this.header({"Status":text});
}

ClientRequest = function(url) {
	this._headers = {};
	this.method = "GET"; 
	this.get = {};
	this.post = {};
	this.cookie = {};

	var u = url;
	var index = u.indexOf("?");
	if (index != -1) { /* parse user-supplied get */
		u = url.substring(0, index);
		var qs = url.substring(index+1);
		this.get = parseQueryString(qs);
	}
	
	if (u.indexOf("://") == -1) { u = "http://"+u; }
	if (u.indexOf("/", 8) == -1) { u += "/"; }
	this._url = u;
}

ClientRequest.prototype.header = function(obj) {
	for (var p in obj) { 
		this._headers[p] = obj[p]; 
	}
}

ClientRequest.prototype.send = function(follow) {
	var Socket = require("socket").Socket;
	var Buffer = require("binary").Buffer;
	var items = this._splitUrl();
	var proto = items[0];
	var host = items[1];
	var port = items[2];
	var url = items[3];
	var hiddenSocket = null;
	this.header({"Host":host + (port == 80 ? "" : ":"+port)});
	
	/* defaults */
	this.header({
		"Connection":"close",
		"Accept-Charset":"utf-8",
		"Accept-Encoding":"identity"
	});
	
	/* add get data */
	var get = this._serialize(this.get);
	if (get) { url += "?"+get; }
	
	/* add cookies */
	var arr = []; 
	for (var p in this.cookie) {
		arr.push(escape(p)+"="+escape(this.cookie[p]));
	}
	if (arr.length) { this.header({"Cookie":arr.join("; ")}); }

	/* add post headers */
	var post = null;
	if (typeof(this.post) == "object") {
		var post = this._serialize(this.post); 
		if (post.length) {
			this.header({
				"Content-Length": post.length,
				"Content-Type": "application/x-www-form-urlencoded"
			});
		}
	} else {
		post = this.post;
		this.header({"Content-Length": post.length});
	}
	
	/* build request */
	var data = this.method + " " + url + " HTTP/1.1\r\n";
	for (var p in this._headers) {
		data += p+": "+this._headers[p]+"\r\n";
	}
	data += "\r\n";
	if (post) { data += post; }

	try {
		var ip = Socket.getAddrInfo(host, Socket.PF_INET6).split('%', 1)[0];
		if (!ip) { throw "Cannot resolve IPv6"; }
		var socket = new Socket(Socket.PF_INET6, Socket.SOCK_STREAM, Socket.IPPROTO_TCP);
		socket.connect(ip, port);
	} catch(e) {
		var ip = Socket.getAddrInfo(host, Socket.PF_INET);
		var socket = new Socket(Socket.PF_INET, Socket.SOCK_STREAM, Socket.IPPROTO_TCP);
		socket.connect(ip, port);
	}
	
	if (proto == "https") { /* wrap in a TLS connection */
		var TLS = require("tls").TLS;
		hiddenSocket = socket;
		socket = new TLS(socket);
		socket.connect();
	}
	
	socket.send(data); /* send request */
	
	var received = new Buffer(0);

	try {
		do {
			var part = socket.receive(1024);
			var tmp = new Buffer(received.length + part.length);
			tmp.copyFrom(received);
			tmp.copyFrom(part, 0, received.length);
			received = tmp;
		} while (part.length > 0);
	} catch (e) {}
	
	if (hiddenSocket) { /* unwrap and close TLS connection */
		socket.close();
		socket = socket.getSocket();
	}
	
	socket.close();
	
	return this._handleResponse(received, follow);
}

ClientRequest.prototype._serialize = function(obj) {
	var arr = [];
	for (var p in obj) {
		var val = obj[p];
		if (!(val instanceof Array)) { val = [val]; }
		for (var i=0, len=val.length;i<len;i++) {
			arr.push(encodeURIComponent(p)+"="+encodeURIComponent(val[i]));
		}
	}
	return arr.join("&");
}

ClientRequest.prototype._splitUrl = function() {
	var parts = this._url.match(/^ *((https?):\/\/)?([^:\/]+)(:([0-9]+))?(.*)$/);
	var proto = parts[2] || "http";
	var host = parts[3];
	var port = parts[5] || (parts[2] == "https" ? 443 : 80);
	var url = parts[6];
	return [proto, host, port, url];
}

/**
 * @param {Buffer} data
 * @param {bool} follow Follow redirects?
 */
ClientRequest.prototype._handleResponse = function(buffer, follow) {
	var codes = [301, 302, 303, 307];
	var r = new ClientResponse(buffer);
	if (!follow) { return r; }
	
	var code = r.status;
	if (codes.indexOf(code) == -1) { return r; }

	var loc = r.header("Location");
	if (!loc) { return r; }
	
	if (code == 302 || code == 303) {
		/* 
			302 should not be used for switching to GET, but... 
			see http://en.wikipedia.org/wiki/HTTP_302 ;)
		*/
		this.method = "GET";
	}
	if (loc.indexOf("://") != -1) { 
		/* absolute URI, standards compliant */
		this._url = loc;
	} else { 
		/* relative URI */
		if (loc.charAt(0) == "/") {
			var i = this._url.indexOf("/", 8);
		} else {
			var i = this._url.lastIndexOf("/")+1;
		}
		this._url = this._url.substring(0, i) + loc;
	}
	return this.send(follow);
}

ClientResponse = function(buffer) {
	var Buffer = require("binary").Buffer;

	this.data = null;
	this.status = 0;
	this.statusReason = "";
	this._headers = {};

	var index = buffer.indexOf("\r\n\r\n");

	if (index == -1) { throw new Error("No header-body separator found"); }
	var head = buffer.range(0, index).toString("utf-8");
	var body = buffer.range(index+4);
	var arr = head.split("\r\n");
	
	var parts = arr.shift().match(/^ *http\/[^ ]+ *([0-9]+) *(.*)$/i);
	this.status = parseInt(parts[1], 10);
	this.statusReason = parts[2] || "";
	
	for (var i=0, len=arr.length;i<len;i++) {
		var parts = arr[i].match(/^ *([^: ]+) *: *(.*)$/);
		if (parts) {
			this._headers[parts[1].toUpperCase()] = parts[2];
		}
	}
	
	if (this.header("Transfer-encoding") == "chunked") {
		this.data = this._parseChunked(body);
	} else {
		this.data = body;
	}
}

ClientResponse.prototype.header = function(name) {
	return this._headers[name.toUpperCase()];
}

ClientResponse.prototype.headers = function() {
	return this._headers;
}

/**
 * @param {Buffer} body
 */
ClientResponse.prototype._parseChunked = function(body) {
	var Buffer = require("binary").Buffer;
	
	var index = 0
	var num, hex;
	var result = new Buffer(0);
	
	while (index < body.length) {
		hex = "";
		
		/* fetch hex number at the beginning of each chunk. this is terminated by \r\n */
		while (index < body.length) {
			num = body[index];
			if (num == 13) { break; }
			hex += String.fromCharCode(num);
			index++; 
		}
		
		/* skip CRLF */
		index += 2; 
		
		var chunkLength = parseInt(hex, 16);
		if (!chunkLength) { break; }

		/* read the chunk */
		var tmp = new Buffer(result.length + chunkLength);
		tmp.copyFrom(result);
		tmp.copyFrom(body, index, result.length);
		result = tmp;
		index += chunkLength;
		
		/* skip CRLF after chunk */
		index += 2;
	}

	return result;
}

exports.ServerRequest = ServerRequest;
exports.ServerResponse = ServerResponse;
exports.ClientRequest = ClientRequest;
exports.ClientResponse = ClientResponse;

if (system.env["SERVER_SOFTWARE"]) {
	if (global.apache) {
		var read = apache.read;
		var write = apache.write;
		var header = apache.header;
	} else {
		var read = system.stdin.read;
		var write = system.stdout.write;
		var header = function(name, value) { write(name + ": " + value + "\r\n"); }
	}
	global.request = new ServerRequest(read, system.env);
	global.response = new ServerResponse(write, header);
}
