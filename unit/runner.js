#!../v8cgi

var TestRunner = {
	depth:0,
	verbosity:0,
	
	indent: function() {
		for (var i=0;i<this.depth;i++) { System.stdout("\t"); }
	},
	
	add: function(base, data) {
		for (var p in base) {
			if (p in data) { base[p] += data[p]; }
		}
	},	

	test: function(f, name) {
		try {
			f();
			if (this.verbosity > 1) { 
				this.indent();
				System.stdout("Test '"+name+"': passed\n"); 
			}
			return {passed:1};
		} catch(e) {
			var msg = e || e.toString();
			if (this.verbosity > 0) { 
				this.indent();
				System.stdout("Test '"+name+"': "+msg+"\n"); 
			}
			return {failed:1}
		}
	},

	file: function(name) {
		var results = {failed:0, passed:0, errors:0};
		if (this.verbosity > 0) { 
			this.indent();
			System.stdout("File '"+name+"'\n"); 
		}
		this.depth++;
		try {
			var data = require(System.getcwd() + "/" + name);
			for (var p in data) {
				if (!p.match(/^test/i)) { continue; }
				var result = this.test(data[p], p);
				this.add(results, result);
			}
		} catch(e) {
			results.errors++;
			if (this.verbosity > 0) { 
				this.indent();
				System.stdout("syntax error ("+e+")\n"); 
			}
			this.depth--;
			return results;
		} 
		
		this.depth--;
		var total = results.failed + results.passed;
		if (this.verbosity > 0) { 
			this.indent();
			System.stdout("done ("+total+" tests, "+results.passed+" passed, "+results.failed+" failed)\n"); 
		}
		return results;
	},

	dir: function(name) {
		var results = {failed:0, passed:0, files:0, errors:0};
		var d = new Directory(name);
		if (this.verbosity > 0) { System.stdout("Directory '"+name+"'\n"); }
		var list = d.listFiles().filter(function(f) { return f.match(/\.js$/i); });
		
		for (var i=0;i<list.length;i++) {
			this.depth++;
			var result = this.file(name+"/"+list[i]);
			this.depth--;
			this.add(results, result);
			results.files++;
		}
		
		var total = results.failed + results.passed;
		if (this.verbosity > 0) {
			System.stdout("done ("+results.files+" files, "+total+" tests, "+results.passed+" passed, "+results.failed+" failed, "+results.errors+" errors)\n");
		}
		return results;
	},

	go: function(paths) {
		var results = {failed:0, passed:0, files:0, directories:0, errors:0};
		for (var i=0;i<paths.length;i++) {
			var name = paths[i];
			var f = new File(name);
			var result = {};
			
			if (!f.exists()) {
				System.stdout("Skipping nonexistent '"+name+"'\n");
			} else if (f.isFile()) {
				var result = this.file(name);
				results.files++;
			} else {
				var result = this.dir(name);
			}
			
			this.add(results, result);
			results.directories++;
		}
		
		var total = results.failed + results.passed;
		System.stdout("\nRESULTS:\n");
		System.stdout("  "+results.directories+" directories\n");
		System.stdout("  "+results.files+" files\n");
		System.stdout("  "+total+" tests\n");
		System.stdout("  "+results.passed+" passed\n");
		System.stdout("  "+results.failed+" failed\n");
		System.stdout("  "+results.errors+" syntax errors\n");
	},
	
	init: function() {
		var GetOpt = require("getopt").GetOpt;
		this.options = new GetOpt();
		this.options.add("help", "Print help message", false, "h", "help");
		this.options.add("verbosity", "Verbosity level (0-2)", 0, "v", "", GetOpt.OPTIONAL_ARGUMENT);
		try {
			this.options.parse(global.arguments);
		} catch(e) {
			System.stdout("Bad arguments.\n");
			this.help();
			return;
		}
		
		if (this.options.get("help")) {
			this.help();
		} else {
			this.verbosity = this.options.get("verbosity");
			this.go(this.options.get());
		}
	},
	
	help: function() {
		System.stdout("Usage: ./runner.js [options] [file|dir] [file|dir] [...]\n\n");
		System.stdout(this.options.help());
	}
}

TestRunner.init();
