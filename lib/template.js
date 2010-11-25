var Template = function(options) {
	this.options = {
		path:"",
		suffix:"template"
	}
	for (var p in options) { this.options[p] = options[p]; }
}

Template.prototype.process = function(file, data) {
	var contents = this._read(file);
	return this.processString(contents, data);
}

Template.prototype.processString = function(str, data) {
	var code = this._process(str);
	return this._evalTemplate(code, data);
}

Template.prototype._evalTemplate = function(code, data) {
	var __output = "";
	eval(code);
	return __output;
}

Template.prototype._read = function(file) {
	var name = this.options.path + file;
	if (this.options.suffix) { name += "."+this.options.suffix; }
	var f = new (require("fs").File)(name);
	if (!f.exists()) { throw new Error("Cannot open '"+name+"'"); }
	return f.open("r").read().toString("utf-8");
}

Template.prototype._tokenStatic = function(str) {
	str = str.replace(/"/g,'\\"').replace(/\n/g,"\\n").replace(/\r/g,"\\r").replace(/\t/g,"\\t"); //'
	return "__output += \""+str+"\";";
}

Template.prototype._tokenCommand = function(str, command) {
	switch (command) {
		case "code":
			return str+";";
		break;
		case "include":
			var file = this._read(str);
			return this._process(file);
		break;
		default:
			return "__output += "+str+";";
		break;
	}
}

Template.prototype._process = function(str) {
	var arr = [];

	var token = ""; /* token being processed */
	var char = ""; /* character being processed */

	var depth = 0;
	var flag = false; /* in command part */
	var command = "";

	for (var i=0;i<str.length;i++) {
		var ch = str.charAt(i);
		switch (ch) {
			case "$":
				if (!depth && !flag) { /* start of js expression */
					flag = true;
					arr.push(this._tokenStatic(token));
					token = "";
				} else {
					token += ch;
				}
			break;

			case "(":
				if (flag) { /* start of js expression content */
					flag = false;
					depth++;
					command = token;
					token = "";
				} else if (depth > 0) { /* inside js expression content */
					depth++;
					token += ch;
				} else {
					token += ch; /* outside js expression */
				}
			 break;

			case ")":
				if (depth > 0) { /* inside js expression */
					depth--;
					if (depth == 0) { /* end of js expression */
						arr.push(this._tokenCommand(token, command));
						token = "";
					} else {
						token += ch;
					}
				} else { /* outside js expression */
					token += ch;
				}
			break;

			default:
				token += ch;
			break;
		}
		if (flag && !token.match(/^[a-z]*$/)) { /* fake dollar alert */
			flag = false;
			token = "$"+token;
		}
	}
	arr.push(this._tokenStatic(token));
	return arr.join("");
}

exports.Template = Template;
