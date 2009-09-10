include('Jst.js');
include('session.js');

/**
 * Concatenates the values of a variable into an easily readable string
 * by Matt Hackett [scriptnode.com]
 * @param {Object} x The variable to debug
 * @param {Number} max The maximum number of recursions allowed (keep low, around 5 for HTML elements to prevent errors) [default: 10]
 * @param {String} sep The separator to use between [default: a single space ' ']
 * @param {Number} l The current level deep (amount of recursion). Do not use this parameter: it's for the function's own use
 */
function print_r(x, max, sep, l) {

	l = l || 0;
	max = max || 10;
	sep = sep || ' ';

	if (l > max) {
		return "[WARNING: Too much recursion]\n";
	}

	var
		i,
		r = '',
		t = typeof x,
		tab = '';

//	r += t + '\n';
	if (x === null) {
		r += "(null)\n";
	} else if (t === 'function') {
		r += '(function)\n';
		x = 'function';
	} else if (t === 'object') {

		l++;

		for (i = 0; i < l; i++) {
			tab += sep;
		}

		if (x && x.length) {
			t = 'array';
		}

		r += '(' + t + ") :\n";

		for (i in x) {
			if (i === 'class') continue;
			try {
				r += tab + '[' + i + '] : ' + print_r(x[i], max, sep, (l + 1));
			} catch(e) {
				return "[ERROR: " + e + "]\n";
			}
		}

	} else {

		if (t == 'string') {
			if (x == '') {
				x = '(empty)';
			}
		}

		r += '(' + t + ') ' + x + "\n";

	}

	return r;

};
	
// Attempt to read in application's configuration
try {
	include('./AppConfig.js');
}
catch (e) {
	// do nothing
}
		
ob_end_clean = function() {
	outputBuffers = [[]];
	outputBufferIndex = 0;
};
	
ob_end_flush = function() {
	while (outputBuffers.length) {
		response.write(outputBuffers.pop().join(''));
	}
	ob_end_clean();
};
	
ob_get_contents = function() {
	return outputBuffers[outputBufferIndex];
};
	
ob_end_clean();

onexit(ob_end_flush);
	
// mimicks console object in firefox/firebug.
// useful for server-side script debugging.
// output is written to a file, specified in AppConfig class.
// typically, I'd tail -f on the output file to see the messages as they occur
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
		console.log(print_r(o));
	}
};

function print(s) {
	for (var i=0,len=arguments.length; i<len; i++) {
		outputBuffers[outputBufferIndex].push(arguments[i]);
//		response.write(arguments[i]);
	}
}

println = function(s) {
	print(s + '\n');
};

printbr = function(s) {
	print(s + '<br/>\n');
};

// Handy helper to dump (php var_dump style) an object to the
// web page for debugging.

dump = function(obj, name) {
	if (name) {
		print('<h1>'+name+'</h1>');
	}
	print('<pre>'+print_r(obj)+'</pre>');
};

errorHandler = function(e) {
	response.status(500);
	println("<h1>500 Error</h1>");
	if (e.stack) {
		println('<h2>Stack Trace</h2>');
		var stack = e.stack.split('\n');
	//	println('<h2>' + stack[0] + '</h2>');
		for (var i=0; i<stack.length; i++) {
			print('&nbsp;&nbsp;&nbsp;&nbsp;' + stack[i] + '<br/>');
		}
	}
	else {
		printbr(e);
	}
	println('<hr>');
	println("<h2>Dump of Exception Object:</h2>");
	dump(e);
	println("<h2>Server Environment:</h2>");
	dump(system.env);
//	system.exit();
};
	
file_get_contents = function(fn) {
	var f = new File(fn);
	f.open('r');
	var contents = f.read();
	f.close();
	return contents;
};

readFile = function(fn) {
	println(file_get_contents(fn));
};

	
try {
//	(function() {
//		try {
			if (system.env.SCRIPT_FILENAME.match(/\.jst$/)) {
				var tpl = file_get_contents(system.env.SCRIPT_FILENAME);
				var parsed = Jst.parse(tpl);
				println(Jst.executeParsed(parsed, { }));
			}
			else {
				try {
					include(system.env.SCRIPT_FILENAME);
				}
				catch (e) {
					throw new Error(e);
				}
			}
		//}
		//catch (e) {
		//	throw new Error(e);
		//}
	//})();
//	dump(Session);
}
catch (e) {
	ob_end_clean();
	errorHandler(e);
	
}

