var assert = require("assert");

exports.testAssert = function() {
	assert.assert(true, "true assertion");
	
	assert.assertThrows(function(){
		assert.assert(false);
	}, "false assertion");
}

exports.testAssertEquals = function() {
	assert.assertEquals(1, 3-2, "equality");
	
	assert.assertThrows(function(){
		assert.assertEquals(1, "1");
	}, "type inequality");
}
