// mimicks console object in firefox/firebug.
// useful for server-side script debugging.
// output is written to a file, specified in AppConfig class.
// typically, I'd tail -f on the output file to see the messages as they occur

console = {
	log: function(s) {
		if (AppConfig && AppConfig.consoleFile) {
			var f = new File(AppConfig.consoleFile);
			if (f.open('a')) {
				f.write(s + '\n');
				f.close();
			}
		}
	},
	dir: function(o) {
		console.log(Util.print_r(o));
	}
};
