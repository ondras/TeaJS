var assert = require("assert");

exports.testAssert = function() {
	assert.assert("true assertion", true);
	
	assert.assertThrows(function(){
		assert.assert(false);
	}, "false assertion");
}

exports.testAssertEquals = function() {
	assert.assertEquals("equality", 1, 3-2);
	
	assert.assertThrows("type inequality", function(){
		assert.assertEquals(1, "1");
	});
}
