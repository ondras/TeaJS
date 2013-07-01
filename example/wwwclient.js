#!/usr/bin/env teajs

/* simple http client application - downloads an URL and outputs its contents */

var http = require("http");
var client = new http.ClientRequest("https://www.google.com/");
var response = client.send(true);

system.stdout.writeLine(JSON.stringify(response.headers(), false, " "));
system.stdout.writeLine();
system.stdout.writeLine(response.data);
