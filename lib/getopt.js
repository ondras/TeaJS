var GetOpt = function() {
	this.options = {};
	this.add("", null, [], false, false, GetOpt.REQUIRED_ARGUMENT); /* main arguments */
}

/** @constant */ GetOpt.NO_ARGUMENT = 1;
/** @constant */ GetOpt.REQUIRED_ARGUMENT = 2;
/** @constant */ GetOpt.OPTIONAL_ARGUMENT = 3;

/**
 * Adds an option
 * @param {string} id Identifier
 * @param {string} description Textual description
 * @param {?} value Default value
 * @param {char} short Short option character
 * @param {string} long Long option string
 * @param {number} argument Argument type constant
 */
GetOpt.prototype.add = function(id, description, value, short, long, argument) {
	this.options[id] = {
		description:description,
		value:value,
		long:long,
		short:short,
		argument:argument || GetOpt.NO_ARGUMENT
	};
}

/**
 * Retrieve option value
 * @param {string} id Identifier
 */
GetOpt.prototype.get = function(id) {
	var str = id || "";
	if (str in this.options) {
		return this.options[str].value;
	} else {
		throw new Error("Unknown option '"+id+"'");
	}
}

/**
 * Parses list of options
 * @param {array} array Command-line arguments
 */
GetOpt.prototype.parse = function(array) {
	this._pending = false;
	for (var i=0;i<array.length;i++) {
		var str = array[i];
		if (str == "--") { /* separator */
			this._finishPending();
			this._parseRemainder(array, i+1);
			break;
		} else if (this._isOption(str)) { /* option string */
			this._finishPending();
			this._parseOption(str);
		} else { /* value */
			if (this._pending) { /* add to pending option */
				this._addValue(this._pending, str);
				this._pending = false;
			} else { /* add as normal argument */
				this._addValue("", str);
			}
		}
	}
	this._finishPending();
	this._parseRemainder(array, array.length);
}

/**
 * Formats a help
 * @returns {string}
 */
GetOpt.prototype.help = function() {
	var names = [];
	var values = [];

	for (var id in this.options) {
		if (!id) { continue; } /* do not mention main arguments */
		var item = this.options[id];
		names.push(this._helpName(item));
		values.push(item.description);
	}
	
	var indent = 0;
	for (var i=0;i<names.length;i++) {
		if (names[i].length > indent) { indent = names[i].length; }
	}
	indent++;
	
	var str = "";
	for (var i=0;i<names.length;i++) {
		str += names[i];
		for (var j=names[i].length;j<indent;j++) { str += " "; }
		str += values[i] + "\n";
	}
	return str;
}

/**
 * Parse remaining values after '--'
 */
GetOpt.prototype._parseRemainder = function(array, index) {
	for (var i=index; i<array.length;i++) { this._addValue("", array[i]); } /* consume all normal values */
}

GetOpt.prototype._finishPending = function() {
	if (!this._pending) { return; }
	var item = this.options[this._pending];
	if (item.argument == GetOpt.REQUIRED_ARGUMENT) { /* unsatisfied mandatory */
		throw new Error("Missing value for '"+this._pendingString+"'");
	} else { /* unsatisfied optional */
		this._addValue(this._pending, null); 
	}
}

/**
 * Parse an option string
 * @returns {id || false}
 */
GetOpt.prototype._parseOption = function(str) {
	if (str.charAt(1) == "-") {
		this._parseOptionLong(str);
	} else {
		this._parseOptionShort(str);
	}
}

GetOpt.prototype._parseOptionLong = function(str) {
	var re = str.match(/^--([a-zA-Z0-9]+)(=(.*))?$/);
	if (!re) { throw new Error("Cannot parse option '"+str+"'"); }
	
	var id = this._findOptionLong(re[1]);
	if (!id) { throw new Error("Unknown option '--"+re[1]+"'"); }
	
	var item = this.options[id];
	if (re[2]) { /* with a value */
		var value = re[3];
		this._addValue(id, value);
	} else { /* without a value */
		if (item.argument == GetOpt.NO_ARGUMENT) {
			this._addValue(id);
		} else {
			this._pending = id;
			this._pendingString = "--"+re[1];
		}
	}
}

GetOpt.prototype._parseOptionShort = function(str) {
	var re = str.match(/^-([a-zA-Z0-9]+)(=(.*))?$/);
	if (!re) { throw new Error("Cannot parse option '"+str+"'"); }
	
	var list = re[1];
	for (var i=0;i<list.length;i++) {
		var char = list[i];
		var id = this._findOptionShort(char);
		if (!id) { throw new Error("Unknown option '-"+char+"'"); }
		
		var item = this.options[id];
		if (item.argument == GetOpt.NO_ARGUMENT) { /* no argument */
			this._addValue(id);
		} else if (i+1 == list.length) { /* last char */
			if (re[2]) {
				this._addValue(id, re[3]);
			} else {
				this._pending = id;
				this._pendingString = "-"+char;
			}
		} else { /* middle char, argument optional/mandatory */
			if (item.argument == GetOpt.REQUIRED_ARGUMENT) { /* mandatory -> error */
				throw new Error("Missing value for '-"+char+"'");
			} else { /* unsatisfied optional */
				this._addValue(id, null);
			}
		}
	}
}

GetOpt.prototype._isOption = function(str) {
	return (str.length > 1 && str.charAt(0) == "-");
}

GetOpt.prototype._findOptionShort = function(str) {
	for (var id in this.options) {
		if (this.options[id].short == str) { return id; }
	}
	return false;
}

GetOpt.prototype._findOptionLong = function(str) {
	for (var id in this.options) {
		if (this.options[id].long == str) { return id; }
	}
	return false;
}

/**
 * Set/add a value to option
 */
GetOpt.prototype._addValue = function(id, value) {
	var item = this.options[id];
	if (item.argument == GetOpt.NO_ARGUMENT) { /* no argument -> switch to true */
		item.value = true;
		return;
	}
	
	if (item.value instanceof Array) { /* _add_ a new value */
		var val = value;
		if (value === null) { val = true; }
		item.value.push(val);
	} else { /* _set_ a new value */
		if (item.argument == GetOpt.OPTIONAL_ARGUMENT) { /* optional */
			if (typeof(item.value) == "number" && value === null) { /* numeric - increment */
				item.value++;
			} else if (typeof(item.value) == "number") { /* numeric value */
				item.value = parseFloat(value);
			} else { /* other or null value */
				item.value = (value === null ? true : value);
			}
		} else { /* required */
			item.value = value;
		}
	}
}

GetOpt.prototype._helpName = function(item) {
	var str = "";
	if (item.short) {
		str += "-"+item.short;
		if (item.argument != GetOpt.NO_ARGUMENT) { str += " "; }
		if (item.argument == GetOpt.OPTIONAL_ARGUMENT) { str += "["; }
		if (item.argument != GetOpt.NO_ARGUMENT) { str += "value"; }
		if (item.argument == GetOpt.OPTIONAL_ARGUMENT) { str += "]"; }
	}
	
	if (item.short && item.long) { str += ", "; }
	
	if (item.long) {
		str += "--"+item.long;
		if (item.argument == GetOpt.OPTIONAL_ARGUMENT) { str += "["; }
		if (item.argument != GetOpt.NO_ARGUMENT) { str += "="; }
		if (item.argument != GetOpt.NO_ARGUMENT) { str += "value"; }
		if (item.argument == GetOpt.OPTIONAL_ARGUMENT) { str += "]"; }
	}

	return str;
}

exports.GetOpt = GetOpt;
