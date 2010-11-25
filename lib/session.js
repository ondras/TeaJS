var fs = require("fs");

var Session = function(request, response) {
	this.request = request;
	this.response = response;
	this._data = {};
	this._id = null;
	this._file = null;

	this._name = Config.sessionCookie || "V8SID";
	this._path = Config.sessionPath || "/tmp";
	this._domain = Config.sessionDomain || "/";
	if (this._path.charAt(this._path.length-1) != "/") { this._path += "/"; }
	this._lifetime = Config.sessionTime || 60*60;
	this._gc();

	var ok = false;
	if (this.request.cookie[this._name]) { /* cookie here */
		var id = this.request.cookie[this._name];
		var f = new fs.File(this._fileName(id));
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

Session.prototype.set = function(name, value) {
	this._data[name] = value;
}

Session.prototype.get = function(name) {
	return this._data[name] || null;
}

Session.prototype.clear = function() {
	this._data = {};
	if (this._file.exists()) { this._file.remove(); }
}

Session.prototype.save = function() {
	var propcnt = 0;
	for (var p in this._data) { propcnt++; }
		if (propcnt == 0) {
		if (this._file.exists()) { this._file.remove(); }
		return;
	}
	var str = JSON.stringify(this._data);
	this._file.open("w").write(str).close();
}

Session.prototype.getId = function() {
	return this._id;
}

Session.prototype.setId = function(id) {
	this._id = id || this._newId();
	this._cookie();
	this._file = new fs.File(this._fileName(this._id));
}

Session.prototype._newId = function() {
	var str = "";
	for (var i=0;i<3;i++) {
		str += Math.random().toString();
	}
	return require("hash").sha1(str);
}

Session.prototype._fileName = function(id) {
	return this._path + require("hash").sha1(id);
}

Session.prototype._gc = function() {
	var d = new fs.Directory(this._path);
	var files = d.listFiles();
	var now = Math.round(new Date().getTime()/1000);
	for (var i=0;i<files.length;i++) {
		var file = new fs.File(this._path + files[i]);
		var data = file.stat();
		if (now - data.atime > this._lifetime && now - data.mtime > this._lifetime) {
			try { file.remove(); } catch(e) { }
		}
	}
}

Session.prototype._cookie = function() {
	var d = new Date();
	d.setFullYear(100+d.getFullYear());
	this.response.cookie(this._name, this._id, d, this._domain);
}

Session.prototype._load = function() {
	var str = this._file.open("r").read().toString("utf-8");
	this._file.close();
	this._data = JSON.parse(str);
}

exports.Session = Session;
global.session = new Session(global.request, global.response);
