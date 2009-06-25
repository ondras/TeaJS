#!../v8cgi

var client = new HTTP.ClientRequest("http://www.seznam.cz/");
var response = client.send(true);

system.stdout(JSON.stringify(response._headers, false, " "));
system.stdout("\n\n");
system.stdout(response.data);
