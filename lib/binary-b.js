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

var Binary_split = function(delimiter, options) {
	var o = {
		count: -1,
		includeDelimiter: true
	}
	for (var p in options) { o[p] = options[p]; }
	
	var result = [];
	var start = 0;
	var index = -1;
	do {
		if (result.length == o.count) { return result; }

		index = this.indexOf(delimiter, start);
		system.stdout("index: "+index+"\n");
		if (index == -1) { break; }

		var end = index;
		if (o.includeDelimiter) { end += 1; } /* delimiter.length */
		system.stdout("slice from "+start+" to "+end+"\n");
		result.push(this.slice(start, end));
		start = index + 1; /* delimiter.length */
	} while (index != -1);
	
	if (start < this.length) {
		result.push(this.slice(start));
	}
	
	return result;
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

B.prototype.join = Binary_join;

B.prototype.split = Binary_split;

B.prototype.copy = Binary_copy;

/* BS stuff */

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

/* BA stuff */

BA.prototype.get = BA.prototype.valueAt = BA.prototype.byteAt = Binary_get;

BA.prototype.toString = function() {
	return "[ByteArray "+this.length + "]";
}

BA.prototype.toSource = function() {
	return "ByteArray([" + this.toArray().join(", ") + "])";
}

BA.prototype.extendLeft = BA.prototype.unshift;

BA.prototype.extendRight = BA.prototype.push;

BA.prototype.fill = function(value, start, stop) {
	var num = (value instanceof B ? value[0] : value);
	var from = start || 0;
	var to = stop || this.length;
	for (var i=from; i<to; i++) {
		this[i] = num;
	}
	return this;
}

/* BA JS 1.6+ Array methods */

var list = ["forEach", "every", "some", "map", "filter", "reduce", "reduceRight"];
for (var i=0;i<list.length;i++) {
	var name = list[i];
	BA.prototype[name] = Array.prototype[name];
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
