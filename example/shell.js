#!/usr/bin/env teajs

/* simple interactive js shell */

while (1) {
	system.stdout("> ");
	var cmd = "";
	var ch = "";
	while (1) {
		ch = system.stdin(1).toString("utf-8");
		if (ch == "\n") {
			break;
		} else { 
			cmd += ch;
		}
	}
	if (cmd == "quit" || cmd == "exit" || cmd == "bye") { break; }
	var error = false;
	try {
		var result = eval(cmd);
	} catch(e) {
		error = true;
		system.stdout(e+"\n");
	} finally {
		if (!error && typeof(result) != "undefined") { system.stdout(result+"\n"); }
	}
}
