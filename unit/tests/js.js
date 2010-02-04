/**
 * This file tests the JS module
 */

var assert = require("assert");
require("js");

exports.testString = function() {
	assert.equal("3".lpad(), "03", "lpad without arguments");
	assert.equal("333".lpad(), "333", "redundant lpad without arguments");
	assert.equal("3".lpad("x", 3), "xx3", "lpad with arguments");

	assert.equal("3".rpad(), "30", "rpad without arguments");
	assert.equal("333".rpad(), "333", "redundant rpad without arguments");
	assert.equal("3".rpad("x", 3), "3xx", "rpad with arguments");
	
	assert.equal("  \n hello \r\n dolly\t".trim(), "hello \r\n dolly", "trim");
	assert.equal("hello dolly".trim(), "hello dolly", "redundant trim");
}

exports.testDate = function() {
	var d = new Date();
	d.setMilliseconds(0);
	d.setSeconds(1);
	d.setMinutes(2);
	d.setHours(3);
	d.setDate(4);
	d.setMonth(0);
	d.setFullYear(2006);
	
	var result = d.format("! d j N S w z W m n t L Y y a A g G h H i s U");
	var ts = 1136343721 + d.getTimezoneOffset()*60;
	var str = "! 04 4 3 th 3 3 01 01 1 31 0 2006 06 am AM 3 3 03 03 02 01 "+ts;
	assert.equal(result, str, "date format");
}
