/**
 * This file tests the "template" module.
 */

var assert = require("assert");
var Template = require("template").Template;

exports.testTemplate = function() {
	var source = "1 $(data.a) $code( for(var i=0;i<data.i.length;i++) { ) $(data.i[i]) $code( } ) 2";
	var result = "1 a  x  y  z  2";

	var t = new Template();
	
	var data = {
		a: "a",
		i: ["x", "y", "z"]
	};
	
	assert.equal(t.processString(source, data), result, "Template::processString");
}

