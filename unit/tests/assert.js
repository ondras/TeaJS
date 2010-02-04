/**
 * This file tests some of the assertion funcions.
 */

var assert = require("assert");

exports.testEqual = function() {
	assert.equal(true, 1, "coerced equality");
}

exports.testOK = function() {
	assert.ok(1, "truthy");
}

exports.testNotEqual = function() {
	assert.notEqual(true, "", "coerced inequality");
}

exports.testStrictEqual = function() {
	assert.strictEqual(1, 3-2, "strict equality");
}

exports.testNotStrictEqual = function() {
	assert.notStrictEqual(1, "1", "strict inequality");
}

exports.testThrows = function() {
	assert.throws(function(){
		throw new Error("wtf omg lol");
	}, null, "assert.throws");
}

exports.testDeepEqual = function() {
	assert.deepEqual(3, 2+1, "deep equality of scalars");

	var d1 = new Date();
	var d2 = new Date();
	d2.setTime(d1.getTime());
	assert.deepEqual(d1, d2, "deep equality of dates");
	
	var o1 = {
		prop1: 123,
		prop2: [15, 0]
	}
	var o2 = {
		prop2: [15, 0],
		prop1: 123
	}
	assert.deepEqual(o1, o2, "deep equality of objects");
}

exports.testNotDeepEqual = function() {
	assert.notDeepEqual(3, 2, "deep inequality of scalars");

	var d1 = new Date();
	var d2 = new Date();
	d2.setTime(d1.getTime()+1);
	assert.notDeepEqual(d1, d2, "deep inequality of dates");
	
	var o1 = {
		prop1: 123,
		prop2: [15, null]
	}
	var o2 = {
		prop2: [15, 0],
		prop1: 123
	}
	assert.notDeepEqual(o1, o2, "deep inequality of objects");
}
