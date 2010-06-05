/**
 * This file tests some advanced require() features
 */

var assert = require("assert");

exports.testRelative = function() {
	var a = require("./require/a");
	var b1 = require("./require/b");
	var b2 = a.foo();

	assert.equal(b1, b2, "delayed relative require");
}
