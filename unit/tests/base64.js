/**
 * This file tests the base64 module.
 */

var assert = require("assert");
var base64 = require("base64");
var Buffer = require("binary").Buffer;

var testObject = {
	"abc123": "YWJjMTIz",
	"xyzqwer": "eHl6cXdlcg==",
	"98765432": "OTg3NjU0MzI="
};

exports.testBase64encode = function() {
	for (var p in testObject) {
		var b = new Buffer(p, "utf-8");
		assert.equal(base64.encode(p).toString("utf-8"), testObject[p], "base64 encode string");
		assert.equal(base64.encode(b).toString("utf-8"), testObject[p], "base64 encode buffer");
	}
}

exports.testBase64decode = function() {
	for (var p in testObject) {
		var b = new Buffer(testObject[p], "utf-8");
		assert.equal(base64.decode(testObject[p]).toString("utf-8"), p, "base64 decode string");
		assert.equal(base64.decode(b).toString("utf-8"), p, "base64 decode buffer");
	}
}

