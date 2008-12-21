var Table = function(name) {
	this._name = name;
}

Table.prototype.select = function() {
	var q = new Query(Query.SELECT);
	q.table(this._name);
	for (var i=0;i<arguments.length;i++) {
		q.field(arguments[i]);
	}
	return q;
}

Table.prototype.insert = function(values) {
	var q = new Query(Query.INSERT);
	q.table(this._name);
	for (var name in values) {
		var value = values[name];
		q.field(name);
		q.value(value);
	}
	return q;
}

Table.prototype.update = function(values) {
	var q = new Query(Query.UPDATE);
	q.table(this._name);
	for (var name in values) {
		var value = values[name];
		q.field(name);
		q.value(value);
	}
	return q;
}

Table.prototype.delete = function(values) {
	var q = new Query(Query.DELETE);
	q.table(this._name);
	return q;
}


var Query = function(type) {
	this._type = type;
	this._table = [];
	this._field = []; 
	this._value = []; 
	this._where = [];
	this._order = [];
	this._limit = null;
	this._offset = 0;
	this._group = [];
	this._having = [];
}

Query.SELECT = 0;
Query.INSERT = 1;
Query.UPDATE = 2;
Query.DELETE = 3;
Query._relations = [];
Query._db = null;

Query.setDB = function(db) {
	this._db = db;
}

Query.addRelation = function(t1,f1,t2,f2) {
	this._relations.push([t1,f1,t2,f2]);
}

Query.findRelation = function(t1, t2, joinfield) {
	for (var i=0;i<this._relations.length;i++) {
		var rel = this._relations[i];
		if (rel[0] != t1 && rel[0] != t2 && rel[2] != t1 && rel[2] != t2) { continue; }
		if (joinfield && joinfield != rel[1] && joinfield != rel[3]) { continue; }
		return rel;
	}
	return null;
}

Query.prototype.table = function(name, jointype, joinfield) {
	var obj = {
	    name:name,
	    jointype:jointype,
	    joinfield:joinfield
	}
	this._table.push(obj);
	return this;
}

Query.prototype.join = Query.prototype.table;

Query.prototype.field = function(fieldDef) {
	var str = "";
	if (arguments.length == 1) {
		str = this._qualify(fieldDef);
	} else {
		str = this._expand.apply(this, arguments);
	}
	this._field.push(str);
	return this;
}

Query.prototype.value = function(value, noescape) {
	var val = value;
	if (!noescape) { val = "'" + this._escape(val)+ "'"; }
	this._value.push(val);
	return this;
}

Query.prototype.where = function(conditionDef) {
	this._where.push(this._expand.apply(this, arguments));
	return this;
}

Query.prototype.order = function(fieldDef, mode) {
	var arr = [];
	for (var i=0;i<arguments.length;i++) {
		if (i != 1) { arr.push(arguments[i]); }
	}
	var str = this._expand.apply(this, arr) + " " + (mode || "ASC");
	this._order.push(str);
	return this;
}

Query.prototype.limit = function(limit) {
	this._limit = limit;
	return this;
}

Query.prototype.offset = function(offset) {
	this._offset = offset;
	return this;
}

Query.prototype.group = function(field) {
	this._group.push(this._qualify(field));
	return this;
}

Query.prototype.having = function(conditionDef) {
	this._where.push(this._expand.apply(this, arguments));
	return this;
}

Query.prototype.toString = function() {
	if (!this._field.length) { this.field("*"); }
	switch (this._type) {
		case Query.SELECT: return this._toStringSelect();
		case Query.INSERT: return this._toStringInsert();
		case Query.UPDATE: return this._toStringUpdate();
		case Query.DELETE: return this._toStringDelete();
		default: return false;
	}
}

Query.prototype.execute = function() {
	var str = this.toString();
	return Query._db.query(str);
}

Query.prototype._toStringSelect = function() {
	var arr = [];
	arr.push("SELECT");
	arr.push(this._toStringField());
	arr.push(this._toStringTable());
	arr.push(this._toStringWhere());
	arr.push(this._toStringGroup());
	arr.push(this._toStringHaving());
	arr.push(this._toStringOrder());
	arr.push(this._toStringLimit());
	arr.push(this._toStringOffset());
	return arr.join(" ");
}

Query.prototype._toStringInsert = function() {
	var arr = [];
	arr.push("INSERT");
	arr.push(this._toStringTable());
	arr.push(this._toStringField());
	return arr.join(" ");
}

Query.prototype._toStringUpdate = function() {
	var arr = [];
	arr.push("UPDATE");
	arr.push(this._toStringTable());
	arr.push(this._toStringField());
	arr.push(this._toStringWhere());
	arr.push(this._toStringOrder());
	arr.push(this._toStringLimit());
	arr.push(this._toStringOffset());
	return arr.join(" ");
}

Query.prototype._toStringDelete = function() {
	var arr = [];
	arr.push("DELETE");
	arr.push(this._toStringTable());
	arr.push(this._toStringWhere());
	arr.push(this._toStringOrder());
	arr.push(this._toStringLimit());
	arr.push(this._toStringOffset());
	return arr.join(" ");
}

Query.prototype._toStringOffset = function() {
	return (this._offset ? "OFFSET "+this._offset : "");
}

Query.prototype._toStringLimit = function() {
	return (this._limit !== null ? "LIMIT "+this._limit : "");
}

Query.prototype._toStringOrder = function() {
	return (this._order.length ? "ORDER BY "+this._order.join(", ") : "");
}

Query.prototype._toStringHaving = function() {
	var str = "";
	if (this._having.length) {
		str += "HAVING "+this._having.join(" ");
	}
	return str;
}

Query.prototype._toStringWhere = function() {
	var str = "";
	if (this._where.length) {
		str += "WHERE "+this._where.join(" ");
	}
	return str;
}

Query.prototype._toStringGroup = function() {
	return this._group.join(", ");
}

Query.prototype._toStringTable = function() {
	var cache = {};
	switch (this._type) {
		case Query.SELECT:
			var arr = [];
			for (var i=0;i<this._table.length;i++) {
				var item = this._table[i];
				var name = item.name;
				if (name in cache) {
					cache[name]++;
				} else {
					cache[name] = 1;
				}
				var alias = this._qualify(name+"#"+cache[name]);
				var full = this._qualify(name) + " AS "+alias;
				
				if (!i) {
					arr.push(full);
				} else {
					var str = "";
					if (item.jointype) { str += item.jointype+" "; }
					str += "JOIN "+full;
					
					var rel = false;
					for (var j=0;j<i;j++) {
						var t2 = this._table[j].name;
						rel = rel || Query.findRelation(name, t2, item.joinfield);
					}
					if (rel) {
						var tmp1 = rel[0] + "#" + cache[rel[0]] + "." + rel[1];
						var tmp2 = rel[2] + "#" + cache[rel[2]] + "." + rel[3];
						str += " ON "+this._qualify(tmp1)+" = "+this._qualify(tmp2);
					}
					arr.push(str);
				}
			}
			return " FROM "+arr.join(" ");
		break;
		
		case Query.INSERT:
			return " INTO "+this._qualify(this._table[0].name);
		break;
		
		case Query.UPDATE:
			return " "+this._qualify(this._table[0].name);
		break;
		
		case Query.DELETE: 
			return " FROM "+this._qualify(this._table[0].name);
		break;
	}
}

Query.prototype._toStringField = function() {
	switch (this._type) {
		case Query.SELECT:
			return this._field.join(", ");
		break;
		
		case Query.INSERT:
			return "("+this._field.join(", ")+") VALUES ("+this._value.join(", ")+")";
		break;
		
		case Query.UPDATE:
			var arr = [];
			for (var i=0;i<this._field.length;i++) {
				arr.push(this._field[i]+"="+this._value[i]);
			}
			return "SET "+arr.join(", ");
		break;
	}
}

Query.prototype._qualify = function(str) {
	var parts = str.split(".");
	var arr = [];
	for (var i=0;i<parts.length;i++) {
		var val = parts[i];
		arr.push(val == "*" ? val : Query._db.qualify(val));
	}
	return arr.join(".");
}

Query.prototype._escape = function(str) {
	return Query._db.escape(str);
}

Query.prototype._expand = function(str) {
	if (arguments.length == 1) { return str; }
	var s = "";
	var argptr = 1;
	var index = 0;
	var start = false;
	
	while (index < str.length) {
		var ch = str.charAt(index);
		switch (ch) {
			case "%":
				start = !start;
				if (!start) { s += ch; }
			break;
			
			case "f":
				if (start) {
					start = false;
					s += this._qualify(arguments[argptr++]);
				} else {
					s += ch;
				}
			break;
			
			case "s":
				if (start) {
					start = false;
					s += "'"+this._escape(arguments[argptr++])+"'";
				} else {
					s += ch;
				}
			break;
			
			default:
				s += ch;
			break;
		}
		index++;
	}
	return s;
}
