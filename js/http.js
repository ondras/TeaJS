(function(){

var HTTPResponse = function() {
    this._output = false;
    this._ct = false; /* Content-type - the only header which must be present */
}

HTTPResponse.prototype.write = function(str) {
    if (!this._output) {
	this._output = true;
	if (!this._ct) { this.header({"Content-type":"text/html"}); }
	System.stdout("\n");
    }
    System.stdout(str);
}

HTTPResponse.prototype.cookie = function(name, value, expires, path, domain, secure, httponly) {
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

HTTPResponse.prototype.error = function(txt) {
    this.write("<pre>Error: "+txt+"</pre>");
}

HTTPResponse.prototype.header = function(h) {
    for (var p in h) {
	if (p.match(/content-type/i)) { this._ct = true; }
	var str = p+": "+h[p]+"\n";
	System.stdout(str);
    }
}

HTTPResponse.prototype.escape = function(str) {
    if (!str) { return ""; }
    return str.toString().replace(/&/g,"&amp;").replace(/</g,"&lt;").replace(/>/g,"&gt;").replace(/"/g,"&quot;").replace(/'/g,"&apos;"); // "
}

HTTPResponse.prototype.dump = function(obj, depth) {
    var d = depth || 0;
    if (!d) { this.write("<pre>\n"); }
    for (var p in obj) {
	var val = obj[p];
	for (var i=0;i<2*d;i++) { this.write(" "); }
	this.write(p+": "+this.escape(val)+"\n");
	if (typeof(val) == "object") {
	    arguments.callee.call(this, val, d+1);
	}
    }
    if (!d) { this.write("</pre>\n"); }
}

var HTTPRequest = function() {
    this.get = {};
    this.post = {};
    this.cookie = {};
    this.files = {};

    this.method = null;
    if (System.env["REQUEST_METHOD"]) { this.method = System.env["REQUEST_METHOD"].toUpperCase(); }
    if (!this.method) { return; }

    this._parseCookie();
    this._parseQS(System.env["QUERY_STRING"], this.get);
    if (this.method == "POST") { this._parsePOST(); }
}

HTTPRequest.prototype.header = function(name) {
    var n = "HTTP_" + name.toUpperCase().replace(/-/g,"_");
    return (n in System.env ? System.env[n] : null);
}

HTTPRequest.prototype._parseCookie = function() {
    if (!("HTTP_COOKIE" in System.env)) { return; }
    var all = System.env["HTTP_COOKIE"].split("; ");
    for (var i=0;i<all.length;i++) {
	var row = all[i];
	var eq = row.indexOf("=");
	var name = row.substring(0,eq);
	var value = row.substring(eq+1);
	this.cookie[name] = unescape(value);
    }
}

HTTPRequest.prototype._decode = function(str) {
    var s = str;
    var err = false;
    try {
	s = decodeURIComponent(str);
    } catch(e) {
//	response.error("Cannot urldecode string");
    } finally {
	return s;
    }
}

HTTPRequest.prototype._parseQS = function(qs, output) {
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

HTTPRequest.prototype._parsePOST = function() {
    var ct = System.env["CONTENT_TYPE"] || "";
    var length = parseInt(System.env["CONTENT_LENGTH"], 10);
    if (!length) { return false; }
    
    if (System.env["CONTENT_TYPE"] == "application/x-www-form-urlencoded") {
	var data = System.stdin(length);
	this._parseQS(data, this.post);
    } else if (ct.match(/boundary/)) {
	var arr = System.stdin(length, true);
	var str = String.fromCharCode.apply(this, arr); /* convert from array to string */
	this._parseMultipart(ct, str, false);
    } else {
	return false;
    }
    return true;
}

HTTPRequest.prototype._addField = function(output, name, value) {
    if (!(name in output)) {
        output[name] = value;
    } else if (output[name] instanceof Array) {
        output[name].push(value);
    } else {
	output[name] = [output[name], value];
    }
}

HTTPRequest.prototype._parseMultipart = function(header, data, name) {
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

HTTPRequest.prototype._processMultipart = function(obj, n) {
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
	    var arr = [];
	    for (var i=0;i<obj.data.length;i++) {
		arr.push("%" + obj.data.charCodeAt(i).toString(16));
	    }
	    this._addField(this.post, name, decodeURI(arr.join("")));
	}
    }		
}

var HTTPSession = function() {
    this._data = {};
    this._id = null;
    this._file = null;

    this._name = Config.sessionCookie || "V8SID";
    this._path = Config.sessionPath || "/tmp";
    if (this._path.charAt(this._path.length-1) != "/") { this._path += "/"; }
    this._lifetime = Config.sessionTime || 60*60;
    this._gc();
    
    var ok = false;
    if (request.cookie[this._name]) { /* cookie here */
	var id = request.cookie[this._name];
	var f = new File(this._fileName(id));
	if (f.exists()) { /* matching file */
	    this._id = id;
	    this._file = f;
	    this._load();
	    ok = true;
	}
    }
    if (!ok) {
	this.setId();
	this.clear();
    }
    
    var self = this;
    var callback = function() { self.save(); }
    onexit(callback);
}

HTTPSession.prototype.set = function(name, value) {
    this._data[name] = value;
}

HTTPSession.prototype.get = function(name) {
    return this._data[name] || null;
}

HTTPSession.prototype.clear = function() {
    this._data = {};
    if (this._file.exists()) { this._file.remove(); }
}

HTTPSession.prototype.save = function() {
    var propcnt = 0;
    for (var p in this._data) { propcnt++; }
    if (propcnt == 0) {
	if (this._file.exists()) { this._file.remove(); }
	return;
    }
    var str = Util.serialize(this._data);
    this._file.open("w").write(str).close();
}

HTTPSession.prototype.getId = function() {
    return this._id;
}

HTTPSession.prototype.setId = function(id) {
    this._id = id || this._newId();
    this._cookie();
    this._file = new File(this._fileName(this._id));
}

HTTPSession.prototype._newId = function() {
    var str = "";
    for (var i=0;i<3;i++) {
	str += Math.random().toString();
    }
    return Util.sha1(str);
}

HTTPSession.prototype._fileName = function(id) {
    return this._path + Util.sha1(id);
}

HTTPSession.prototype._gc = function() {
    var d = new Directory(this._path);
    var files = d.listFiles();
    var now = Math.round(new Date().getTime()/1000);
    for (var i=0;i<files.length;i++) {
	var file = new File(this._path + files[i]);
	var data = file.stat();
	if (now - data.atime > this._lifetime && now - data.mtime > this._lifetime) {
	    try { file.remove(); } catch(e) { }
	}
    }
}

HTTPSession.prototype._cookie = function() {
    var d = new Date();
    d.setFullYear(100+d.getFullYear());
    response.cookie(this._name, this._id, d);
}

HTTPSession.prototype._load = function() {
    var str = this._file.open("r").read();
    this._file.close();
    this._data = Util.unserialize(str);
}

this.response = new HTTPResponse();
this.request = new HTTPRequest();
this.session = new HTTPSession();

})();
