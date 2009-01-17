#!../v8cgi

var client = new HTTP.ClientRequest("www.google.com");
var data = client.send(true);

System.stdout(Util.serialize(data, true));
