#!../v8cgi

while (1) {
	System.stdout("> ");
	var cmd = "";
	var ch = "";
	while (1) {
		ch = System.stdin(1);
		if (ch == "\n") {
			break;
		} else { 
			cmd += ch;
		}
	}
	if (cmd == "quit") { break; }
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
