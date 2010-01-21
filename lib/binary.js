var B = exports.Binary;
var BS = exports.ByteString;
var BA = exports.ByteArray;

var get = function(index) {
	return this[index];
}

/* Binary stuff */

B.prototype.toArray = function(charset) {
	var arr = [];
	var source = this;
	if (charset) { source = this.decodeToString(charset); }

	for (var i=0;i<source.length;i++) {
		arr.push(source.codeAt(i));
	}
	return arr;
}


/* BS stuff */

BS.prototype.get = BS.prototype.valueAt = BS.prototype.byteAt = get;

BS.prototype.toString = function() {
	return "[ByteString "+this.length + "]";
}

BS.prototype.toSource = function() {
	return "ByteString([" + this.toArray().join(", ") + "])";
}

BS.prototype.substring = function(index1, index2) {
	/* swap if necessary */
	var start = Math.min(index1, index2);
	var end = Math.max(index1, index2);
	
	/* both non-negative */
	start = Math.max(start, 0);
	end = Math.max(end, 0);
	
	return this.slice(start, end);
}

BS.prototype.substr = function(index, length) {
	/* non-negative start, default end */
	var start = Math.max(index, 0);
	var end = this.length;
	
	/* length specified */
	if (arguments.length > 1) {
		end = start + length;
		/* length nonnegative */
		end = Math.max(start, end);
	}
	
	return this.slice(start, end);
}

/* BA stuff */

BA.prototype.get = BA.prototype.valueAt = BA.prototype.byteAt = get;

BA.prototype.toString = function() {
	return "[ByteArray "+this.length + "]";
}

BA.prototype.toSource = function() {
	return "ByteArray([" + this.toArray().join(", ") + "])";
}

/* String stuff */

String.prototype.toByteArray = function(charset) {
	return new BA(this, charset);
}

String.prototype.toByteString = function(charset) {
	return new BS(this, charset);
}

String.prototype.charCode = function() {
	var arr = []; 
	for (var i=0;i<this.length;i++) { arr.push(this.charCodeAt(i)); }
	return arr;
}

String.prototype.codeAt = function(index) {
	return this.charCodeAt(index);
}

String.prototype.get = function(index) {
	return this[index];
}

/* Array stuff */

Array.prototype.toByteArray = function(charset) {
	var str = String.fromCharCode.apply(null, this);
	return new BA(str, charset);
}

Array.prototype.toByteString = function(charset) {
	var str = String.fromCharCode.apply(null, this);
	return new BS(str, charset);
}

Array.prototype.get = function(index) {
	return this[index];
}
