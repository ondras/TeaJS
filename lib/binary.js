var BS = exports.ByteString;

var get = function(index) {
}

BS.prototype.get = function(index) {
	return this[index];
}

BS.prototype.valueAt = BS.prototype.get;
BS.prototype.byteAt = BS.prototype.get;

BS.prototype.toString = function() {
	return "[ByteString "+this.length + "]";
}

BS.prototype.toSource = function() {
	return "ByteString(" + this.toArray().toSource() + ")";
}
