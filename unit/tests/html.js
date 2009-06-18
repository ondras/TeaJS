/**
 * This file tests html HTML module.
 */

var assert = require("assert");
var html = require("html").HTML;

exports.testHtml = function() {
	var s1 = "<a href='a&b'>\"";
	var s2 = "&lt;a href=&apos;a&amp;b&apos;&gt;&quot;";
	assert.assertEquals("html escape", s2, html.escape(s1));
	assert.assertEquals("html unsecape", s1, html.unescape(s2));
}
