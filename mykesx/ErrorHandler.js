//
// This function takes an exception object and formats it
// for display on the screen.
//
// To use it, you put code like this in your executable .sjs files:
/*
try {
    // the typical body of whatever the script should do to generate a page...
	foo(); // no such function!
}
catch (e) {
	errorHandler(e);
}
*/

// NOTE: the try/catch should ideally be automatically added by mod_v8 and
// this would be the default errorHandler.  I see it as something like onexit(),
// where applications can override it with their own handlers.

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
	exit();
};

exports.errorHandler = errorHandler;
