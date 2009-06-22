#!../v8cgi

var client = new HTTP.ClientRequest("http://www.seznam.cz/");
var response = client.send(true);

System.stdout(JSON.stringify(response._headers, false, " "));
System.stdout("\n\n");
System.stdout(response.data);
