var assert = require("assert");
require("js");

exports.testString = function() {
	assert.assertEquals("03", "3".lpad(), "lpad without arguments");
	assert.assertEquals("333", "333".lpad(), "redundant lpad without arguments");
	assert.assertEquals("xx3", "3".lpad("x", 3), "lpad with arguments");

	assert.assertEquals("30", "3".rpad(), "rpad without arguments");
	assert.assertEquals("333", "333".rpad(), "redundant rpad without arguments");
	assert.assertEquals("3xx", "3".rpad("x", 3), "rpad with arguments");
	
	assert.assertEquals("hello \r\n dolly", "  \n hello \r\n dolly\t".trim(), "trim");
	assert.assertEquals("hello dolly", "hello dolly".trim(), "redundant trim");
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
	assert.assertEquals(str, result, "date format");
}
