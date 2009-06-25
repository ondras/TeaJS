#!../v8cgi

var TestRunner = {
	depth:0,
	verbosity:0,
	
	indent: function() {
		for (var i=0;i<this.depth;i++) { system.stdout("\t"); }
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
				system.stdout("Test '"+name+"': passed\n"); 
			}
			return {passed:1};
		} catch(e) {
			var msg = e || e.toString();
			if (this.verbosity > 0) { 
				this.indent();
				system.stdout("Test '"+name+"': "+msg+"\n"); 
			}
			return {failed:1}
		}
	},

	file: function(name) {
		var results = {failed:0, passed:0, errors:0};
		if (this.verbosity > 0) { 
			this.indent();
			system.stdout("File '"+name+"'\n"); 
		}
		this.depth++;
		try {
			var data = require(system.getcwd() + "/" + name);
			for (var p in data) {
				if (!p.match(/^test/i)) { continue; }
				var result = this.test(data[p], p);
				this.add(results, result);
			}
		} catch(e) {
			results.errors++;
			if (this.verbosity > 0) { 
				this.indent();
				system.stdout("error ("+e+")\n"); 
			}
			this.depth--;
			return results;
		} 
		
		this.depth--;
		var total = results.failed + results.passed;
		if (this.verbosity > 0) { 
			this.indent();
			system.stdout("done ("+total+" tests, "+results.passed+" passed, "+results.failed+" failed)\n"); 
		}
		return results;
	},

	dir: function(name) {
		var results = {failed:0, passed:0, files:0, errors:0};
		var d = new Directory(name);
		if (this.verbosity > 0) { system.stdout("Directory '"+name+"'\n"); }
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
			system.stdout("done ("+results.files+" files, "+total+" tests, "+results.passed+" passed, "+results.failed+" failed, "+results.errors+" errors)\n");
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
				system.stdout("Skipping nonexistent '"+name+"'\n");
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
		system.stdout("\nRESULTS:\n");
		system.stdout("  "+results.directories+" directories\n");
		system.stdout("  "+results.files+" files\n");
		system.stdout("  "+total+" tests\n");
		system.stdout("  "+results.passed+" passed\n");
		system.stdout("  "+results.failed+" failed\n");
		system.stdout("  "+results.errors+" errors\n");
	},
	
	init: function() {
		var GetOpt = require("getopt").GetOpt;
		this.options = new GetOpt();
		this.options.add("help", "Print help message", false, "h", "help");
		this.options.add("verbosity", "Verbosity level (0-2)", 0, "v", "", GetOpt.OPTIONAL_ARGUMENT);
		try {
			var args = [];
			for (var i=1;i<system.args.length;i++) { args.push(system.args[i]); }
			this.options.parse(args);
		} catch(e) {
			system.stdout("Bad arguments.\n");
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
		system.stdout("Usage: ./runner.js [options] [file|dir] [file|dir] [...]\n\n");
		system.stdout(this.options.help());
	}
}

TestRunner.init();
