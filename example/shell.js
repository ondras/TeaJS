#!../v8cgi

while (1) {
    System.stdout("> ");
    var cmd = System.stdin();
    var error = false;
    try {
        var result = eval(cmd);
    } catch(e) {
	error = true;
	System.stdout(e+"\n");
    } finally {
        if (!error && typeof(result) != "undefined") { System.stdout(result+"\n"); }
    }
}
