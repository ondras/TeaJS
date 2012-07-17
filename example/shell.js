#!/usr/bin/env teajs

/* simple interactive js shell */

while (1) {
	system.stdout("TeaJS> ");
	var cmd = system.stdin.readLine().toString("utf-8").trim();
	if (cmd == "quit" || cmd == "exit" || cmd == "bye") { break; }

	try {
		var result = eval(cmd);
		if (result !== undefined) { system.stdout.writeLine(result); }
	} catch (e) {
		system.stdout.writeLine(e);
	}
}
