#!../v8cgi

var client = new HTTP.ClientRequest("www.google.com");
var response = client.send(true);

System.stdout(Util.serialize(response._headers, true));
System.stdout(response.data);
