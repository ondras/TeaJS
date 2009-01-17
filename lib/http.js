var HTTP = {};

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
    this._parseQS(this._headers["QUERY_STRING"], this.get);
    if (this.method == "POST") { this._parsePOST(); }
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

HTTP.ServerRequest.prototype._parseQS = function(qs, output) {
    if (!qs) { return; }
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
	
	this._addField(output, name, value);
    }
}

HTTP.ServerRequest.prototype._parsePOST = function() {
    var ct = this._headers["CONTENT_TYPE"] || "";
    var length = parseInt(this._headers["CONTENT_LENGTH"], 10);
    if (!length) { return false; }
    
    if (ct.indexOf("application/x-www-form-urlencoded") != -1) {
		var data = this._input(length);
		this._parseQS(data, this.post);
    } else if (ct.match(/boundary/)) {
		var arr = this._input(length, true);
		var str = String.fromCharCode.apply(this, arr); /* convert from array to string */
		this._parseMultipart(ct, str, false);
    } else {
		return false;
    }
    return true;
}

HTTP.ServerRequest.prototype._addField = function(output, name, value) {
    if (!(name in output)) {
        output[name] = value;
    } else if (output[name] instanceof Array) {
        output[name].push(value);
    } else {
	output[name] = [output[name], value];
    }
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
			this._addField(this.files, name, obj);
		} else { /* form field */
			var utf = Util.utf8encode(obj.data);
			this._addField(this.post, name, utf);
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
		this._output("\n");
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
		if (p.match(/location/i)) { this.status(302, "Found"); }
		var str = p+": "+h[p]+"\n";
		this._output(str);
    }
}

HTTP.ServerResponse.prototype.status = function(number, reason) {
	var text = number.toString();
	if (reason) { text += " "+reason; }
	this.header({"Status":text});
}
