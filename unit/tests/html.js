var assert = require("assert");
var html = require("html").HTML;

exports.testHtml = function() {
	var s1 = "<a href='a&b'>\"";
	var s2 = "&lt;a href=&apos;a&amp;b&apos;&gt;&quot;";
	assert.assertEquals(s2, html.escape(s1), "html escape");
	assert.assertEquals(s1, html.unescape(s2), "unescape");
}
