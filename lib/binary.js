exports.Buffer.prototype.Content = Number;

exports.Buffer.prototype.toSource = function() {
	var arr = [];
	for (var i=0;i<this.length;i++) { arr.push(this[i]); }
	return 'require("binary").Buffer([' + arr.join(", ") + '])';
}

/**
 * v8cgi-specific Buffer enhancement
 */
exports.Buffer.prototype.indexOf = function(what, start) {
	if (!(what instanceof exports.Buffer)) { 
		if (typeof(what) == "number") {
			what = new exports.Buffer([what]); 
		} else {
			what = new exports.Buffer(what, "utf-8"); 
		}
	}
	
	var index = start || 0;
	while (index + what.length <= this.length) {
		var ok = true;
		for (var i=0;i<what.length;i++) {
			if (what[i] != this[index+i]) {
				ok = false; 
				break;
			}
		}
		if (ok) { return index; }
		index++;
	}
	
	return -1;
}
