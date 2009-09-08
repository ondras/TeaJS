// lib.js
response.start_time = new Date().getTime()/1000;

include('./AppConfig.js');
include('./console.js');

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

dump = function(obj, name) {
	if (name) {
		print('<h1>'+name+'</h1>');
	}
	print('<pre>'+print_r(obj)+'</pre>');
};

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
include('./ErrorHandler.js');
include('./Util.js');
include('./print_r.js');
include('./SQL.js');
include('./Json.js');

