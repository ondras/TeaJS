/**
 * This file tests the hash module.
 */

var assert = require("assert");
var hash = require("hash");
var Buffer = require("binary").Buffer;

var testString = "abc123\n";

exports.testMD5 = function() {
	assert.equal(hash.md5(""), 								"d41d8cd98f00b204e9800998ecf8427e", "md5 empty string");
	assert.equal(hash.md5(new Buffer("", "utf-8")),			"d41d8cd98f00b204e9800998ecf8427e", "md5 empty bufer");

	assert.equal(hash.md5(testString), 						"2c6c8ab6ba8b9c98a1939450eb4089ed", "md5 test string");
	assert.equal(hash.md5(new Buffer(testString, "utf-8")),	"2c6c8ab6ba8b9c98a1939450eb4089ed", "md5 test buffer");
}

exports.testSHA1 = function() {
	assert.equal(hash.sha1(""), 								"da39a3ee5e6b4b0d3255bfef95601890afd80709", "sha1 empty string");
	assert.equal(hash.sha1(new Buffer("", "utf-8")),			"da39a3ee5e6b4b0d3255bfef95601890afd80709", "sha1 empty bufer");

	assert.equal(hash.sha1(testString), 						"61ee8b5601a84d5154387578466c8998848ba089", "sha1 test string");
	assert.equal(hash.sha1(new Buffer(testString, "utf-8")),	"61ee8b5601a84d5154387578466c8998848ba089", "sha1 test buffer");
}

