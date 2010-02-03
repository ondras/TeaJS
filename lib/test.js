var TEST_RE = /^test.+/;
var PREFIX = "\t";
var results = {};

/**
 * Run one test function
 */
var runFunction = function(func, name, depth) {
	var pref = "";
	for (var i=0;i<depth;i++) { pref += PREFIX; }
	
	system.stdout(pref + name + ": ");
	try {
		func();
		results.passed++;
		system.stdout("PASSED\n");
	} catch (e) {
		results.errors++;
		system.stdout("FAILED\n");
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
			failures += runFunction(val, p, depth);
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
	return results.failed + results.errors;
}
