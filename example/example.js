#!../v8cgi

include("../http.js");

response.dump(request.get);
response.dump(request.post);
