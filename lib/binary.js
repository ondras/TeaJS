var B = exports.Binary;
var BS = exports.ByteString;
var BA = exports.ByteArray;

var Binary_get = function(index) {
	return this[index];
}

var Binary_copy = function(target, start, stop, targetStart) {
	var from = start || 0;
	var to = stop || this.length;
	var targetOffset = targetStart || 0;
	for (var i=0; i<to-from; i++) {
		target[i+targetOffset] = this[i+from];
	}
}

var Binary_join = function(array, separator) {
	var arr = [];
	for (var i=0;i<array.length;i++) {
		if (i && arguments.length > 1) { arr.push(separator); }
		arr.push(array[i]);
	}
	return new this(arr);
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

BS.join = Binary_join;

BS.prototype.get = BS.prototype.valueAt = BS.prototype.byteAt = Binary_get;

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

BS.prototype.copy = Binary_copy;

/* BA stuff */

BA.join = Binary_join;

BA.prototype.get = BA.prototype.valueAt = BA.prototype.byteAt = Binary_get;

BA.prototype.toString = function() {
	return "[ByteArray "+this.length + "]";
}

BA.prototype.toSource = function() {
	return "ByteArray([" + this.toArray().join(", ") + "])";
}

BA.prototype.extendLeft = BA.prototype.unshift;

BA.prototype.extendRight = BA.prototype.push;

BA.prototype.copy = Binary_copy;

/* BA JS 1.6+ Array methods */

BA.prototype.forEach = function(cb, _this) {
	var len = this.length;
	for (var i=0;i<len;i++) { 
		if (i in this) { cb.call(_this, this[i], i, this); }
	}
}

BA.prototype.every = function(cb, _this) {
	var len = this.length;
	for (var i=0;i<len;i++) {
		if (i in this && !cb.call(_this, this[i], i, this)) { return false; }
	}
	return true;
}

BA.prototype.some = function(cb, _this) {
	var len = this.length;
	for (var i=0;i<len;i++) {
		if (i in this && cb.call(_this, this[i], i, this)) { return true; }
	}
	return false;
}

BA.prototype.map = function(cb, _this) {
	var len = this.length;
	var res = new Array(len);
	for (var i=0;i<len;i++) {
		if (i in this) { res[i] = cb.call(_this, this[i], i, this); }
	}
	return res;
}

BA.prototype.filter = function(cb, _this) {
	var len = this.length;
	var res = [];
		for (var i=0;i<len;i++) {
			if (i in this) {
				var val = this[i];
				if (cb.call(_this, val, i, this)) { res.push(val); }
			}
		}
	return res;
}

BA.prototype.reduce = function(fun, initial) {
	var len = this.length >>> 0;
	if (typeof fun != "function") { throw new TypeError(); }

	/* no value to return if no initial value and an empty array */
	if (len == 0 && arguments.length == 1) { throw new TypeError(); }

	var i = 0;
	if (arguments.length >= 2) {
		var rv = initial;
	} else {
		do {
			if (i in this) {
				rv = this[i++];
				break;
			}

			/* if array contains no values, no initial value to return */
			if (++i >= len) { throw new TypeError(); }
		} while (true);
	}

	for (; i < len; i++) {
		if (i in this) { rv = fun.call(null, rv, this[i], i, this); }
	}

	return rv;
}

BA.prototype.reduceRight = function(fun, initial) {
	var len = this.length >>> 0;
	if (typeof fun != "function") { throw new TypeError(); }

	/* no value to return if no initial value, empty array */
	if (len == 0 && arguments.length == 1) { throw new TypeError(); }

	var i = len - 1;
	if (arguments.length >= 2) {
		var rv = initial;
	} else {
		do {
			if (i in this) {
				rv = this[i--];
				break;
			}

			/* if array contains no values, no initial value to return */
			if (--i < 0) { throw new TypeError(); }
		} while (true);
	}

	for (; i >= 0; i--) {
		if (i in this) { rv = fun.call(null, rv, this[i], i, this); }
	}

	return rv;
};

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
