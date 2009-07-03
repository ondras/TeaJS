/**
 * Simple json-rpc handler for v8cgi. Each handler method only takes one argument: parameters as a hash.
 *
 * Example:

 var jsonRpcHandler = require("jsonRpcHandler.js").jsonRpcHandler;

 jsonRpcHandler({

	myMethod: function(opts) {
		// Do what you want...
		return opts.a*opts.b;
	}
	
 );
 *
 */
var jsonRpcHandler = function(methods) {
	
	var httpCode = 200;
 
	// Parse json-rpc parameters
	var paramsStr = null;
	for(var k in request.post) { paramsStr = k; }
	var params = JSON.parse( paramsStr );

	// Prepare json response
	var res = {id: params.id, error:null, result: null};

	// Get method
	var method = methods[params.method];
	if(typeof method != "function") {
	   res.error = "Function not found !";
	   httpCode = 500;
	}
	else {
	   try {
	      // Execute method with the right scope
	      res.result = method.call(this, params.params);
	   }
	   catch(ex) {
	      res.error = ex.toString();
	      httpCode = 500;
	   }
	}
    
	response.status(httpCode);
	response.header({"Content-Type":"application/json"});
	response.write(JSON.stringify(res));

};

exports.jsonRpcHandler = jsonRpcHandler;