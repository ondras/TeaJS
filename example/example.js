#!../v8cgi

include("../js/http.js");

response.dump(request.get);
response.dump(request.post);
