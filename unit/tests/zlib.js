/**
 * This file tests the zlib module.
 */

var assert = require("assert");
var zlib = require("zlib");
var binary = require("binary");

var input = new binary.Buffer(10000);

for (var i=0;i<input.length;i++) { 
	var value = Math.random() * 256;
	input[i] = Math.round(value);
}

exports.testZlib = function() {
	var compressed = zlib.compress(input);
	var decompressed = zlib.decompress(compressed);
	
	for (var i=0;i<Math.max(decompressed.length, input.length);i++) {
		assert.equal(decompressed[i], input[i], "original and decompressed are the same");
	}
}
