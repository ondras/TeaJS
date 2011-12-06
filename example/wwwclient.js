#!v8cgi

/* simple http client application - downloads an URL and outputs its contents */

var http = require("http");
var client = new http.ClientRequest("http://www.seznam.cz/");
var response = client.send(true);

system.stdout(JSON.stringify(response.headers(), false, " "));
system.stdout("\n\n");
system.stdout(response.data.toString("utf-8"));
