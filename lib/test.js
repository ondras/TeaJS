var TEST_RE = /^test.+/;
var PREFIX = "\t";

/**
 * Run one test function
 */
var runFunction = function(func, name, depth) {
	var pref = "";
	for (var i=0;i<depth;i++) { pref += PREFIX; }
	
	system.stdout(pref + name + ": ");
	try {
		func();
		system.stdout("PASSED\n");
		return 0;
	} catch (e) {
		system.stdout("FAILED\n");
		system.stdout(pref + PREFIX + e + "\n");
		return 1;
	}
}

/**
 * Recursive run
 */
var runBatch = function(object, depth) {
	var failures = 0;
	
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
		failures += arguments.callee(delayed[p], depth+1);
	}

	return failures;
}

exports.run = function(object) {
	return runBatch(object, 0);
}
