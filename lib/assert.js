var AssertionError = function(data) {
	this.message = data.message || "";
	this.actual = data.actual || "";
	this.expected = data.expected || "";
};

AssertionError.prototype = Object.create(Error.prototype);

AssertionError.prototype.toString = function() {
	var str = "AssertionError: ";
	str += "expected '" + this.expected + "', ";
	str += "actual '" + this.actual + "'";
	if (this.message) { str += ", message '"+this.message+"'"; }
	return str;
}

/* simple assertion methods */

var equal = function(actual, expected, message) {
	if (actual == expected) { 
	} else {
		throw new AssertionError({actual:actual, expected:expected, message:message}); 
	}
}

var notEqual = function(actual, expected, message) {
	if (actual != expected) {
	} else {
		throw new AssertionError({actual:actual, expected:expected, message:message}); 
	}
}

var strictEqual = function(actual, expected, message) {
	if (actual === expected) { 
	} else {
		throw new AssertionError({actual:actual, expected:expected, message:message}); 
	}
}

var notStrictEqual = function(actual, expected, message) {
	if (actual !== expected) { 
	} else {
		throw new AssertionError({actual:actual, expected:expected, message:message}); 
	}
}

/* deep assertion helpers */

var deepTest = function(a, b) {
	/* 7.1. All identical values are equivalent, as determined by ===.  */
	if (a === b) { return true; }
	
	/* 7.2. If the expected value is a Date object, the actual value is equivalent if it is also a Date object that refers to the same time. */
	if (a instanceof Date && b instanceof Date) { return a.getTime() === b.getTime(); }
	
	/* 7.3. Other pairs that do not both pass typeof value == "object", equivalence is determined by ==.  */
	if (typeof(a) != "object" || typeof(b) != "object") { return a == b; }

	/* 7.4. For all other Object pairs, including Array objects, equivalence is determined by having 
	 * the same number of owned properties (as verified with Object.prototype.hasOwnProperty.call), 
	 * the same set of keys (although not necessarily the same order), equivalent values for every corresponding key, 
	 * and an identical "prototype" property. 
	 * Note: this accounts for both named and indexed properties on Arrays. 
	 */
	if (a.prototype !== b.prototype) { return false; }
	return objectTest(a, b);
}

var objectTest = function(a, b) {
	for (var p in a) {
		if (!deepTest(a[p], b[p])) { return false; }
	}

	for (var p in b) {
		if (!deepTest(a[p], b[p])) { return false; }
	}
	
	return true;
}

/* deep assertion methods */

var deepEqual = function(actual, expected, message) {
	if (deepTest(actual, expected)) {
	} else {
		throw new AssertionError({actual:actual, expected:expected, message:message}); 
	}
}

var notDeepEqual = function(actual, expected, message) {
	if (!deepTest(actual, expected)) {
	} else {
		throw new AssertionError({actual:actual, expected:expected, message:message}); 
	}
}

/* assertion utilities */

var throws = function(block, error, message) {
	try {
		block();
		throw new AssertionError({message:message});
	} catch (e) {
		if (error && !(e instanceof error)) {
			throw new AssertionError({actual:e, expected:error, message:message});
		}
	}
}

var ok = function(guard, message) {
	equal(guard, true, message);
}

exports.AssertionError = AssertionError;
exports.ok = ok;
exports.equal = equal;
exports.notEqual = notEqual;
exports.deepEqual = deepEqual;
exports.notDeepEqual = notDeepEqual;
exports.strictEqual = strictEqual;
exports.notStrictEqual = notStrictEqual;
exports.throws = throws;
