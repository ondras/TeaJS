#!/usr/bin/env teajs

/* simple websocket echo server: repeats received message to all clients (and logs to console) */

var Server = require("websocket").Server;
var ws = new Server("0.0.0.0", 8888, {idle:150});

var clients = [];
var app = {
	onmessage: function(client, data) {
		system.stdout.writeLine(data);
		for (var i=0;i<clients.length;i++) {
			ws.send(clients[i], data);
		}
	},
	onconnect: function(client, headers) {
		clients.push(client);
	},
	ondisconnect: function(client, code, message) {
		var index = clients.indexOf(client);
		if (index != -1) { clients.splice(index, 1); }
	},
	onidle: function() {
		system.stdout.write(".");
		system.stdout.flush();
	}
};

ws.addApplication(app);
ws.run();
