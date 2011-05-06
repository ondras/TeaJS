
var assert = require("assert");
var Buffer = require("binary").Buffer;

exports.testBuffer = function() {
	assert.throws(function() { var s=Buffer(-1); },RangeError,"Bad size");
	assert.throws(function() { var s=Buffer(); },TypeError,"No arguments");
	assert.throws(function() { var s=Buffer("a"); },TypeError,"Missing encoding");
	assert.throws(function() { var s=Buffer([65,66,67],2,1); },RangeError,"fromArray invalid numbers");
	assert.throws(function() { var s=Buffer({}); },TypeError,"fail on object");

	assert.ok(Buffer(Buffer([65,66,67,68]))?true:false,"fromBuffer");
	assert.ok(Buffer([65,66,67,68],1,2)?true:false,"fromArray");
	assert.ok(Buffer([65,66,67])?true:false,"fromArray");
	assert.ok(Buffer("abc",'utf-8')?true:false,'abc','Buffer(string)');
}

exports.testRange = function() {
	var s=Buffer("abc",'utf-8');
	assert.throws(function() { s.range(2,1); },RangeError,'bad range');
	assert.ok(s.range(1,3).toString('utf-8')=="bc",'range 1-2');
}

exports.testToString = function() {
	var s=Buffer("abc",'utf-8');

	assert.throws(function() { Buffer("\x83",'ascii'); },null,'bad ascii characters');
	assert.equal(s.toString('utf-8'),'abc','toString("utf-8")');
}

