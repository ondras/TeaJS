var TEST_RE = /^test.+/;
var PREFIX = "\t";
var results = {};
var assert = require("assert");

/**
 * Run one test function
 */
var runFunction = function(func, name, depth) {
	var pref = "";
	for (var i=0;i<depth;i++) { pref += PREFIX; }
	
	system.stdout(pref + name + "\n");
	try {
		func();
		results.passed++;
	} catch (e) {
		if (e instanceof assert.AssertionError) {
			results.failed++;
		} else {
			results.errors++;
		}
		system.stdout(pref + PREFIX + e + "\n");
	}
}

/**
 * Recursive run
 */
var runBatch = function(object, depth) {
	var delayed = {};
	for (var p in object) {
		if (!p.match(TEST_RE)) { continue; } /* only properties starting with "test" */
		
		var val = object[p];
		if (typeof(val) == "function") { /* function to be done */
			runFunction(val, p, depth);
		} else {
			delayed[p] = val; /* subtests */
		}
	}
	
	var pref = "";
	for (var i=0;i<depth;i++) { pref += PREFIX; }
	for (var p in delayed) {
		system.stdout(pref + p + ":\n");
		arguments.callee(delayed[p], depth+1);
	}
}

exports.run = function(object) {
	results = {
		passed: 0,
		failed: 0,
		errors: 0
	};
	runBatch(object, 0);
	
	system.stdout("RESULTS:\n");
	system.stdout("\tpassed: "+results.passed+"\n");
	system.stdout("\tfailed: "+results.failed+"\n");
	system.stdout("\terrors: "+results.errors+"\n");
	
	return results.failed + results.errors;
}
