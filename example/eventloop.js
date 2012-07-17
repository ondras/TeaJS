#!/usr/bin/env teajs

var eventloop = require("eventloop");
var iterations = 0;

var id = eventloop.setInterval(function() { 
	iterations++;
	system.stdout.writeLine("tick");
	
	if (iterations == 10) {
		eventloop.setTimeout(function() {
			system.stdout.writeLine("scheduled event");
			eventloop.clearTimeout(id);
		}, 1000);
	}
	
}, 300);

eventloop.run();
