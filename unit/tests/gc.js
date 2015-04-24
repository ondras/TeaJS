/**
 * This file test functions system.gc() and system.heap_statistics().
 */

var assert = require("assert");

exports.testGC = function() {
	var before_create = system.heap_statistics()['used_heap_size'];
	for (var i = 0; i < 100; i++) {
		var arr = {};
		for (var j = 0; j < 1000; j++) {
			arr[j] = j;
		}
	}
	var after_create = system.heap_statistics()['used_heap_size'];
	system.gc();
	var after_clean = system.heap_statistics()['used_heap_size'];
	
	assert.equal(before_create < after_create, true, "used_heap_size must be bigger after create objects");
	assert.equal(after_clean < after_create, true, "used_heap_size must be less after system.gc()");
}

