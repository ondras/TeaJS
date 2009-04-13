var assert = require("assert");
require("js");

exports.testString = function() {
	assert.assertEquals("3".lpad(), "03", "lpad without arguments");
	assert.assertEquals("333".lpad(), "333", "redundant lpad without arguments");
	assert.assertEquals("3".lpad("x", 3), "xx3", "lpad with arguments");

	assert.assertEquals("3".rpad(), "30", "rpad without arguments");
	assert.assertEquals("333".rpad(), "333", "redundant rpad without arguments");
	assert.assertEquals("3".rpad("x", 3), "3xx", "rpad with arguments");
	
	assert.assertEquals("  \n hello \r\n dolly\t".trim(), "hello \r\n dolly", "trim");
	assert.assertEquals("hello dolly".trim(), "hello dolly", "redundant trim");
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
	var str = "! 04 4 3 th 3 3 01 01 1 31 0 2006 06 am AM 3 3 03 03 02 01 1136340121";
	assert.assertEquals(result, str, "date format");
}
