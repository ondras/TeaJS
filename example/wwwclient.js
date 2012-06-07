#!/usr/bin/env v8cgi

/* simple http client application - downloads an URL and outputs its contents */

var http = require("http");
var client = new http.ClientRequest("http://ondras.zarovi.cz/");
var response = client.send(true);

system.stdout(JSON.stringify(response.headers(), false, " "));
system.stdout("\n\n");
system.stdout(response.data.toString("utf-8"));
