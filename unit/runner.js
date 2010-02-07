#!../v8cgi

var TestRunner = {
	verbosity:0,

	file: function(name, obj) {
		var moduleName = (name[0] == "/" || name[1] == ":" ? name : system.getcwd() + "/"+name);
		obj["test_" + name] = require(moduleName);
	},
	
	dir: function(name, obj) {
		var subobj = {};
		obj["test_" + name] = subobj;
		var d = new Directory(name);
		var list = d.listFiles().filter(function(f) { return f.match(/\.js$/i); });
		for (var i=0;i<list.length;i++) {
			var item = name + "/" + list[i];
			this.file(item, subobj);
		}
	},
	
	go: function(paths) {
		var allTests = {};
		
		for (var i=0;i<paths.length;i++) {
			var name = paths[i];
			var f = new File(name);
			
			if (!f.exists()) {
				system.stdout("Skipping nonexistent '"+name+"'\n");
			} else if (f.isFile()) {
				this.file(name, allTests);
			} else {
				this.dir(name, allTests);
			}
		}
		
		var bad = require("test").run(allTests);
		system.stdout("\n");
		if (bad) {
			system.stdout("Test run was NOT successful! ("+bad+" problems encountered)\n");
		} else {
			system.stdout("Test run was successful!\n");
		}
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
