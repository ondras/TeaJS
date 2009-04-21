var fail = function(message, origin) {
	var o = origin || "fail";
	throw new Error("["+o+"] " + message);
}

var assert = function(message, expression) {
	var m = "Assertion failed";
	if (message) { m += " ("+message+")"; }
	if (!expression) { fail(m, "assert"); }
}

var assertEquals = function(message, expected, actual) {
	if (arguments.length > 2) {
		var m = arguments[0];
		var e = arguments[1];
		var a = arguments[2];
	} else {
		m = false;
		var e = arguments[0];
		var a = arguments[1];
	}
	
	var reason = "Expected '"+e+"', received '"+a+"'";
	if (m) { reason += " ("+m+")"; }
	if (e !== a) { fail(reason, "assertEquals"); }
}

var assertThrows = function(message, callback) {
	if (arguments.length > 1) {
		var m = arguments[0];
		var c = arguments[1];
	} else {
		var m = false;
		var c = arguments[0];
	}

	var ok = false;
	try {
		c();
	} catch(e) {
		ok = true;
	} finally {
		var reason = "Exception not thrown";
		if (m) { reason += " ("+m+")"; }
		if (!ok) { fail(reason, "assertThrows"); }
	}
}

exports.fail = fail;
exports.assert = assert;
exports.assertEquals = assertEquals;
exports.assertThrows = assertThrows;