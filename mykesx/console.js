console = {
	log: function(s) {
		if (AppConfig.consoleFile) {
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
