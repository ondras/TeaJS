#!../v8cgi

var TestRunner = {
	add: function(base, data) {
		for (var p in base) {
			if (p in data) { base[p] += data[p]; }
		}
	},	

	test: function(f, name) {
		System.stdout("    Test '"+name+"': ");
		try {
			f();
			System.stdout("passed\n");
			return {passed:1};
		} catch(e) {
			System.stdout(e.message+"\n");
			return {failed:1}
		}
	},

	file: function(name) {
		var results = {failed:0, passed:0, errors:0};
		System.stdout("  File '"+name+"'\n");
		
		try {
			var data = require("./"+name);
			for (var p in data) {
				if (!p.match(/^test/i)) { continue; }
				var result = TestRunner.test(data[p], p);
				TestRunner.add(results, result);
			}
		} catch(e) {
			results.errors++;
			System.stdout("  syntax error ("+e+")\n");
			return results;
		} 
		
		var total = results.failed + results.passed;
		System.stdout("  done ("+total+" tests, "+results.passed+" passed, "+results.failed+" failed)\n");
		return results;
	},

	dir: function(name) {
		var results = {failed:0, passed:0, files:0, errors:0};
		var d = new Directory(name);
		System.stdout("Directory '"+name+"'\n");
		var list = d.listFiles().filter(function(f) { return f.match(/\.js$/i); });
		
		for (var i=0;i<list.length;i++) {
			var result = TestRunner.file(name+"/"+list[i]);
			TestRunner.add(results, result);
			results.files++;
		}
		
		var total = results.failed + results.passed;
		System.stdout("done ("+results.files+" files, "+total+" tests, "+results.passed+" passed, "+results.failed+" failed, "+results.errors+" errors)\n");
		return results;
	},

	go: function() {
		var results = {failed:0, passed:0, files:0, directories:0, errors:0};
		for (var i=0;i<global.arguments.length;i++) {
			var result = TestRunner.dir(global.arguments[i]);
			TestRunner.add(results, result);
			results.directories++;
		}
		
		var total = results.failed + results.passed;
		System.stdout("\nRESULTS:\n");
		System.stdout("  "+results.directories+" directories\n");
		System.stdout("  "+results.files+" files\n");
		System.stdout("  "+total+" tests\n");
		System.stdout("  "+results.passed+" passed\n");
		System.stdout("  "+results.failed+" failed\n");
		System.stdout("  "+results.errors+" errors\n");
	}
}

TestRunner.go();
