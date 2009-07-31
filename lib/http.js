var HTTP = {
	_parseQueryString: function(qs) {
		var result = {};
		var parts = qs.split("&");
		for (var i=0;i<parts.length;i++) {
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
			if (name.substring(name.length-2) == "[]") { name = name.substring(0,name.length-2); }
			
			name = this._decode(name);
			value = this._decode(value);
			
			this._mixIn(result, name, value);
		}
		return result;
	},
	_decode: function(str) {
		var s = str.replace(/\+/g, " ");
		try { s = decodeURIComponent(s); } catch(e) {} finally { return s; }
	},
	_mixIn: function(result, name, value) {
		if (!(name in result)) {
			result[name] = value;
		} else if (result[name] instanceof Array) {
			result[name].push(value);
		} else {
			result[name] = [result[name], value];
		}
	}
};

HTTP.ServerRequest = function(input, headers) {
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
    this.get = HTTP._parseQueryString(this._headers["QUERY_STRING"] || "");
    if (this.method == "POST") { this._parsePOST(); }
}

HTTP.ServerRequest.prototype.headers = function() {
	return this._headers;
}

HTTP.ServerRequest.prototype.header = function(name) {
    var n = "HTTP_" + name.toUpperCase().replace(/-/g,"_");
    return (n in this._headers ? this._headers[n] : null);
}

HTTP.ServerRequest.prototype._parseCookie = function() {
    if (!("HTTP_COOKIE" in this._headers)) { return; }
    var all = this._headers["HTTP_COOKIE"].split("; ");
    for (var i=0;i<all.length;i++) {
		var row = all[i];
		var eq = row.indexOf("=");
		var name = row.substring(0,eq);
		var value = row.substring(eq+1);
		if (!this.cookie[name]) { this.cookie[name] = unescape(value); }
    }
}

HTTP.ServerRequest.prototype._decode = function(str) {
    var s = str;
    try {
		s = decodeURIComponent(str.replace(/\+/g, " "));
	} catch(e) {
    } finally {
		return s;
    }
}

HTTP.ServerRequest.prototype._parsePOST = function() {
	
    var ct = this._headers["CONTENT_TYPE"] || "";
    var length = parseInt(this._headers["CONTENT_LENGTH"], 10);
    if (!length) { return false; }
    
    if (ct.indexOf("application/x-www-form-urlencoded") != -1) {
		var retstr = this._readPostToString(length);
		this.post = HTTP._parseQueryString(retstr);
    } else if (ct.match(/boundary/)) {
		var retstr = this._readPostToString(length);
		this._parseMultipart(ct, retstr, false);
    } else {
		return false;
    }
    return true;
}

HTTP.ServerRequest.prototype._readPostToString = function(length) {
    		var datarr = [];
		while(datarr.length < length){
			var tmp = this._input(length, true);
			for (var i=0;i<tmp.length;i++) { datarr.push(tmp[i]); }
		}
		var retstr = "";
		for (var i=0;i<datarr.length;i++) { 
			retstr += String.fromCharCode(datarr[i]); 
		}
		return retstr;
}

HTTP.ServerRequest.prototype._parseMultipart = function(header, data, name) {
    var boundary = header.match(/boundary=(.*)/); /* find boundary */
    boundary = boundary[1];
    var start = "--"+boundary+"\r\n";
    var end = "--"+boundary+"--";
    var parts = data.split(start); /* split by boundary */
    for (var i=0;i<parts.length;i++) { /* all multipart parts */
		var item = parts[i].substring(0, parts[i].length-2);
		if (item == "" || item == "--") { continue; }
		
		var lines = item.split("\r\n");
		var done = false;
		var obj = {
			headers:{},
			data:""
		};
		for (var j=0;j<lines.length;j++) {
			if (lines[j] == end) { continue; }
			if (done) { /* data */
				obj.data += (obj.data.length ? "\r\n" : "")+lines[j];
			} else { /* headers */
				if (lines[j] == "") { done = true; continue; } /* headers done */
				var r = lines[j].match(/([^:]+): *(.*)/);
				var name = r[1].replace(/-/g,"_").toUpperCase();
				var value = r[2];
				obj.headers[name] = value;
			}
		}
		this._processMultipart(obj, name); /* content parsed, decide how to handle it */
    }
}

HTTP.ServerRequest.prototype._processMultipart = function(obj, n) {
    var name = n;
    var cd = obj.headers["CONTENT_DISPOSITION"] || "";
    var ct = obj.headers["CONTENT_TYPE"] || "";
    var r = cd.match(/ name="(.*?)"/i); /* form field name */
    if (r) { name = r[1]; }
    if (ct.match(/multipart\/mixed/i)) { /* recursive processing */
		this._parseMultipart(ct, obj.data, name);
    } else { /* no recursion: either file or form field */
        var r = cd.match(/filename="(.*?)"/i);
		if (r) { /* file */
			obj.originalName = r[1];
			HTTP._mixIn(this.files, name, obj);
		} else { /* form field */
			var utf = Util.utf8encode(obj.data);
			HTTP._mixIn(this.post, name, utf);
		}
	}
}

HTTP.ServerResponse = function(output) {
	this._output = output;
    this._outputStarted = false;
    this._ct = false; /* Content-type - the only header which must be present */
}

HTTP.ServerResponse.prototype.write = function(str) {
    if (!this._outputStarted) {
		this._outputStarted = true;
		if (!this._ct) { this.header({"Content-type":"text/html"}); }
		this._output("\r\n");
    }
    this._output(str);
}

HTTP.ServerResponse.prototype.cookie = function(name, value, expires, path, domain, secure, httponly) {
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

HTTP.ServerResponse.prototype.header = function(h) {
    for (var p in h) {
		if (p.match(/content-type/i)) { this._ct = true; }
		if (p.match(/location/i)) { this.status(303, "See Other"); }
		this._output(p+": "+h[p]+"\r\n");
    }
}

HTTP.ServerResponse.prototype.status = function(number, reason) {
	var text = number.toString();
	if (reason) { text += " "+reason; }
	this.header({"Status":text});
}

HTTP.ClientRequest = function(url) {
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
		this.get = HTTP._parseQueryString(qs);
	}
	
	if (u.indexOf("://") == -1) { u = "http://"+u; }
	if (u.indexOf("/", 8) == -1) { u += "/"; }
	this._url = u;
}

HTTP.ClientRequest.prototype.header = function(obj) {
	for (var p in obj) { 
		this._headers[p] = obj[p]; 
	}
}

HTTP.ClientRequest.prototype.send = function(follow) {
	var Socket = require("socket").Socket;
	
	var items = this._splitUrl();
	var host = items[0];
	var port = items[1];
	var url = items[2];
	var ip = Socket.getAddrInfo(host);
	this.header({"Host":host});
	
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
	if (post) {
		data += post+"\r\n";
		data += "\r\n";
	}

	var s = new Socket(Socket.PF_INET, Socket.SOCK_STREAM, Socket.IPPROTO_TCP);
	s.connect(ip, port);
	s.send(data);
	
	var received = "";
	do {
		var part = s.receive(1024, true);
		for (var i=0;i<part.length;i++) {
			received += String.fromCharCode(part[i]);
		}
	} while (part.length > 0);
	s.close();
	received = Util.utf8encode(received);
	
	return this._handleResponse(received, follow);
}

HTTP.ClientRequest.prototype._serialize = function(obj) {
	var arr = [];
	for (var p in obj) {
		var val = obj[p];
		if (!(val instanceof Array)) { val = [val]; }
		for (var i=0;i<val.length;i++) {
			arr.push(encodeURIComponent(p)+"="+encodeURIComponent(val[i]));
		}
	}
	return arr.join("&");
}

HTTP.ClientRequest.prototype._splitUrl = function() {
	var parts = this._url.match(/^ *(http:\/\/)?([^:\/]+)(:([0-9]+))?(.*)$/);
	var host = parts[2];
	var port = parts[4] || 80;
	var url = parts[5];
	return [host, port, url];
}

HTTP.ClientRequest.prototype._handleResponse = function(data, follow) {
	var codes = [301, 302, 303, 307];
	var r = new HTTP.ClientResponse(data);
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

HTTP.ClientResponse = function(data) {
	this.data = "";
	this.status = 0;
	this.statusReason = "";
	this._headers = {};
	
	var index = data.indexOf("\r\n\r\n");
	var body = data.substring(index+4);
	var h = data.substring(0, index);
	var arr = h.split("\r\n");
	
	var parts = arr.shift().match(/^ *http\/[^ ]+ *([0-9]+) *(.*)$/i);
	this.status = parseInt(parts[1], 10);
	this.statusReason = parts[2] || "";
	
	for (var i=0;i<arr.length;i++) {
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

HTTP.ClientResponse.prototype.header = function(name) {
	return this._headers[name.toUpperCase()];
}

HTTP.ClientResponse.prototype.headers = function() {
	return this._headers;
}

HTTP.ClientResponse.prototype._parseChunked = function(origBody) {
	var index = 0
	var ch;
	var result = "";
	var body = Util.utf8decode(origBody);
	
	while (index < body.length) {
		hex = "";
		
		/* fetch hex number at the beginning of each chunk. this is terminated by \r\n */
		while (index < body.length) {
			ch = body.charAt(index);
			if (ch == "\r") { break; }
			hex += ch;
			index++; 
		}
		
		/* skip CRLF */
		index += 2; 
		
		var chunkLength = parseInt(hex, 16);
		if (!chunkLength) { break; }

		/* read the chunk */
		result += body.substring(index, index + chunkLength);
		index += chunkLength;
		
		/* skip CRLF after chunk */
		index += 2;
	}
	
	return Util.utf8encode(result);
}

exports.HTTP = HTTP;
