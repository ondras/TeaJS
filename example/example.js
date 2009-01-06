#!../v8cgi
library("http.js");

response.write(Util.serialize(System.env, true));
response.write("Hello :)");
