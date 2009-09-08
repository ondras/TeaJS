// lib.js

// This JS file is expected to be include() first!

response.start_time = new Date().getTime()/1000;

// These included first so we can do console.log or
// console.dir right away!

include('./AppConfig.js');
include('./Util.js');
include('./console.js');

// don't we hate to type response.write() all the time?
// these next 3 routines give us shorthand, save us
// some CPU time for computing hashes to lookup functions
// in namespaces, AND give us ability to buffer output.

print = function() {
	for (var i=0,len=arguments.length; i<len; i++) {
		outputBuffers[outputBufferIndex].push(arguments[i]);
//		response.write(arguments[i]);
	}
};

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
	print('<pre>'+Util.print_r(obj)+'</pre>');
};

// PHP style output buffering routines.

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

onexit(function() {
	ob_end_flush();
});

ob_end_clean();

// Include the rest of the basic library code.

include('./ErrorHandler.js');
include('./SQL.js');
include('./Json.js');

