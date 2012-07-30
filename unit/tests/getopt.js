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
	assert.equal(go.get("a"), false, "default value #1");
	assert.equal(go.get("e"), 17, "default value #2");
	assert.throws(function() { go.get("x"); }, null, "undefined default value");
}

exports.testGetoptErrors = function() {
	var go = setup();
	assert.throws(function() { go.parse(["-x"]); }, null, "unknown short option");
	
	var go = setup();
	assert.throws(function() { go.parse(["--yz"]); }, null, "unknown long option");

	var go = setup();
	assert.throws(function() { go.parse(["-e"]); }, null, "required argument without value");

	var go = setup();
	assert.throws(function() { go.parse(["-ea", "value"]); }, null, "required argument without value in shortmix");
}

exports.testGetoptOk = function() {
	var go = setup();
	go.parse(["-a", "-b", "4", "-c", "xxx", "-d", "1", "-d", "2", "--"]);
	assert.equal(go.get("a"), true, "value #1");
	assert.equal(go.get("b"), 4, "value #2");
	assert.equal(go.get("c"), "xxx", "value #3");
	assert.equal(go.get("d").join(","), "1,2", "value #4");
	
	var go = setup();
	go.parse(["--blong", "-bc", "yyy", "--long=zzz", "-bb"]);
	assert.equal(go.get("a"), false, "value #5");
	assert.equal(go.get("b"), 4, "value #6");
	assert.equal(go.get("c"), "yyy", "value #7");
	assert.equal(go.get("e"), "zzz", "value #8");
}

exports.testGetoptMain = function() {
	var go = setup();
	go.parse(["a", "b", "c"]);
	assert.equal(go.get("").join(""), "abc", "simple main values");

	var go = setup();
	go.parse(["--along", "b"]);
	assert.equal(go.get("").join(""), "b", "simple main value");

	var go = setup();
	go.parse(["-d", "--", "xx", "-a"]);
	assert.equal(go.get("d")[0], true, "optional value before --");
	assert.equal(go.get("").join(""), "xx-a", "main value after --");
}

exports.testIssue17 = function() {
	var go = setup();
	go.parse(["-c", "a"]);
}

exports.testIssue7 = function() {
	var go = new GO();
	go.add("format", "desc", false, "f", "image-format", GO.REQUIRED_ARGUMENT);
	go.parse(["--image-format=png"]);
	assert.equal(go.get("format"), "png", "long option name with dash");
}
