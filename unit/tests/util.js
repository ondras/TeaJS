var assert = require("assert");
var util = require("util").Util;

exports.testBase64 = function() {
	var s1 = "hello";
	var s2 = "aGVsbG8=";
	assert.assertEquals("base64 encode", s2, util.base64encode(s1));
	assert.assertEquals("base64 decode", s1, util.base64decode(s2));
}

exports.testSha1 = function() {
	var s1 = "hello";
	var s2 = "aaf4c61ddcc5e8a2dabede0f3b482cd9aea9434d";
	assert.assertEquals("sha1", s2, util.sha1(s1));
}

exports.testMd5 = function() {
	var s1 = "hello";
	var s2 = "5d41402abc4b2a76b9719d911017c592";
	assert.assertEquals("md5", s2, util.md5(s1));
}

exports.testUtf8 = function() {
	var s1 = "žšČ";
	var s2 = String.fromCharCode(197, 190, 197, 161, 196, 140);
	assert.assertEquals("utf8 decode", s2, util.utf8decode(s1));
	assert.assertEquals("utf8 encode", s1, util.utf8encode(s2));
}

exports.testJson = function() {
	var data = [1,"2",{"\n":[]},null,true];
	var str = "[1,\"2\",{\"\\n\":[]},null,true]";
	assert.assertEquals("json serialize", str, util.serialize(data));
	assert.assertEquals("json deserialize", str, util.serialize(util.deserialize(str)));
	
	var a = [];
	a.push(a);
	assert.assertThrows("cyclic structure", function(){util.serialize(a);});
	assert.assertThrows("function", function(){util.serialize(function(){});});
}
