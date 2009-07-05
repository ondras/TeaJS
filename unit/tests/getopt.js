/**
 * This file tests the GetOpt module.
 */

var assert = require("assert");
var GO = require("getopt").GetOpt;

function setup() {
	var go = new GO();
	go.add("a", "desc", false, "a", "along", GO.NO_ARGUMENT);
	go.add("b", "desc", 0, "b", "blong", GO.OPTIONAL_ARGUMENT);
	go.add("c", "desc", "", "c", "clong", GO.REQUIRED_ARGUMENT);
	
	go.add("d", "desc", [], "d", false, GO.OPTIONAL_ARGUMENT);
	go.add("e", "desc", 17, false, "long", GO.REQUIRED_ARGUMENT);
	
	return go;
}

exports.testGetoptInitial = function() {
	var go = setup();
	assert.assertEquals("default value #1", false, go.get("a"));
	assert.assertEquals("default value #2", 17, go.get("e"));
	assert.assertThrows("undefined default value", function() { go.get("x"); });
}

exports.testGetoptErrors = function() {
	var go = setup();
	assert.assertThrows("unknown short option", function() { go.parse(["-x"]); });
	
	var go = setup();
	assert.assertThrows("unknown long option", function() { go.parse(["--yz"]); });

	var go = setup();
	assert.assertThrows("required argument without value", function() { go.parse(["-e"]); });

	var go = setup();
	assert.assertThrows("required argument without value in shortmix", function() { go.parse(["-ea", "value"]); });
}

exports.testGetoptOk = function() {
	var go = setup();
	go.parse(["-a", "-b", "4", "-c", "xxx", "-d", "1", "-d", "2", "--"]);
	assert.assertEquals("value #1", true, go.get("a"));
	assert.assertEquals("value #2", 4, go.get("b"));
	assert.assertEquals("value #3", "xxx", go.get("c"));
	assert.assertEquals("value #4", "1,2", go.get("d").join(","));
	
	var go = setup();
	go.parse(["--blong", "-bc", "yyy", "--long=zzz", "-bb"]);
	assert.assertEquals("value #5", false, go.get("a"));
	assert.assertEquals("value #6", 4, go.get("b"));
	assert.assertEquals("value #7", "yyy", go.get("c"));
	assert.assertEquals("value #8", "zzz", go.get("e"));
}

exports.testGetoptMain = function() {
	var go = setup();
	go.parse(["a", "b", "c"]);
	assert.assertEquals("simple main values", "abc", go.get("").join(""));

	var go = setup();
	go.parse(["--along", "b"]);
	assert.assertEquals("simple main value", "b", go.get("").join(""));

	var go = setup();
	go.parse(["-d", "--", "xx", "-a"]);
	assert.assertEquals("optional value before --", true, go.get("d")[0]);
	assert.assertEquals("main value after --", "xx-a", go.get("").join(""));
}

exports.testIssue17 = function() {
	var go = setup();
	go.parse(["-c", "a"]);
}
