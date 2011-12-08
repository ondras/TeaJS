#!/usr/bin/env v8cgi

/* simple HTTP server; listens on 127.0.0.1:10001 and returns HTTP/200 OK */

var Socket = require("socket").Socket;

var address = "127.0.0.1";
var port = 10001;
var socket = new Socket(Socket.PF_INET, Socket.SOCK_STREAM, Socket.IPPROTO_TCP);
socket.setOption(Socket.SO_REUSEADDR, true);
socket.bind(address, port);
socket.listen(10);

while (1) {
	var connection = socket.accept();
	var data = "", buffer = "";
	while (1) {
		buffer = connection.receive(1000);
		if (!buffer) { break; }
		data += buffer.toString("ascii");
		if (data.indexOf("\n\n") == data.length-2) { break; }
		if (data.indexOf("\r\n\r\n") == data.length-4) { break; }
	}
	connection.send("HTTP/1.0 200 OK\n\nHello world .)");
	connection.close();	
	if (data.match(/quit/i)) { break; }
}
socket.close();
