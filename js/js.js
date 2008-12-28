String.prototype.lpad = function(char, count) {
    var ch = char || "0";
    var cnt = count || 2;
    var s = this;
    while (s.length < cnt) { s = ch+s; }
    return s;
}

String.prototype.rpad = function(char, count) {
    var ch = char || "0";
    var cnt = count || 2;
    var s = this;
    while (s.length < cnt) { s += ch; }
    return s;
}

String.prototype.trim = function() {
    return this.match(/^\s*(.*?)\s*$/)[1];
}

Date.prototype.format = function(str) {
    var result = "";
    for (var i=0;i<str.length;i++) {
	var ch = str.charAt(i);
	switch (ch) {
	    case "d": result += this.getDate().toString().lpad(); break;
	    case "j": result += this.getDate(); break;
	    case "w": result += this.getDay(); break;
	    case "N": result += this.getDay() || 7; break;

	    case "m": result += (this.getMonth()+1).toString().lpad(); break;
	    case "n": result += (this.getMonth()+1); break;

	    case "Y": result += this.getFullYear().toString().lpad(); break;
	    case "y": result += this.getFullYear().toString().lpad().substring(2); break;

	    case "G": result += this.getHours(); break;
	    case "H": result += this.getHours().toString().lpad(); break;
	    case "g": result += (this.getHours() % 12)+1; break;
	    case "h": result += ((this.getHours() % 12)+1).toString().lpad(); break;
	    case "i": result += this.getMinutes().toString().lpad(); break;
	    case "s": result += this.getSeconds().toString().lpad(); break;
	    
	    case "Z": result += -60*this.getTimezoneOffset(); break;
	    
	    case "O": 
	    case "P": 
		var base = this.getTimezoneOffset()/-60;
		var o = Math.abs(base).toString().lpad();
		if (ch == "P") { o += ":"; }
		o += "00";
		result += (base >= 0 ? "+" : "-")+o;
	    break;

	    case "U": result += this.getTime()/1000; break; 
	    case "c": result += arguments.callee.call(this, "Y-m-d")+"T"+arguments.callee.call(this, "H:i:sP"); break; 


	    
	    default: result += ch; break;
	}
    }
    return result;
}
