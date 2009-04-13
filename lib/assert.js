var fail = function(message, origin) {
	var o = origin || "fail";
	throw new Error("["+o+"] " + message);
}

var assert = function(expression, description, origin, reason) {
	var o = origin || "assert";
	var r = reason || "Assertion failed";
	if (description) { r += " ("+description+")"; }
	if (!expression) { fail(r, o); }
}

var assertEquals = function(expected, actual, description) {
	var reason = "Expected '"+expected+"', received '"+actual+"'";
	assert(expected === actual, description, "assertEquals", reason);
}

var assertThrows = function(callback, description) {
	var ok = false;
	try {
		callback();
	} catch(e) {
		ok = true;
	} finally {
		assert(ok, description, "assertThrows", "Exception not thrown");
	}
}

exports.fail = fail;
exports.assert = assert;
exports.assertEquals = assertEquals;
exports.assertThrows = assertThrows;