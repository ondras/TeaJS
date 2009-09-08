errorHandler = function(e) {
	response.status(500);
	ob_end_clean();
	println("<h1>500 Error</h1>");
	var stack = e.stack.split('\n');
	println('<h2>' + stack[0] + '</h2>');
	for (var i=1; i<stack.length; i++) {
		print('&nbsp;&nbsp;&nbsp;&nbsp;' + stack[i] + '<br/>');
	}
	println("<h2>Dump of Exception Object:</h2>");
	dump(e);
	println("<h2>Server Environment:</h2>");
	dump(system.env);
	
	println(JSON.stringify(e));
	exit();
};

//exports.errorHandler = errorHandler;
