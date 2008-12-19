var Table = function(name, db) {
	this.name = name;
	this.db = db;
	this._relation = [];
}

Table.prototype.select = function() {
	var q = new Query(Query.SELECT, this.db);
	return q.table(this).field.apply(q, arguments);
}

Table.prototype.insert = function(data) {
	var q = new Query(Query.INSERT, this.db);
	q.table(this);
	for (var name in data) {
		var o = {};
		o[name] = data[name];
		q.field(o);
	}
	return q;
}

Table.prototype.update = function(data) {
	var q = new Query(Query.UPDATE, this.db);
	q.table(this);
	for (var name in data) {
		var o = {};
		o[name] = data[name];
		q.field(o);
	}
	return q;
}

Table.prototype["delete"] = function() {
	var q = new Query(Query.DELETE, this.db);
	q.table(this);
	return q;
}

Table.prototype.getName = function() {
	return this.name;
}

Table.prototype.addRelation = function(ownfield, foreigntable, foreignfield) {
	var obj = {
		owntable:this,
		ownfield:ownfield,
		foreigntable:foreigntable,
		foreignfield:foreignfield
	}
	this._relation.push(obj);
}

Table.prototype.getRelation = function(table) {
	for (var i=0;i<this._relation.length;i++) {
		var item = this._relation[i];
		if (item.foreigntable == table) { return item; }
	}
	return false;
}

var Query = function(type, db) {
	this._db = db;
	this._type = type;
	this._table = [];
	this._field = []; 
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

Query.prototype.table = function(table, join) {
	var obj = {
	    table:table,
	    join:join
	}
	this._table.push(obj);
	this._field.push([]);
	return this;
}

Query.prototype.join = Query.prototype.table;

Query.prototype.field = function() {
	var f = this._field[this._field.length-1];
	for (var i=0;i<arguments.length;i++) {
		var field = arguments[i];
		if (typeof(field) == "object") {
			for (var p in field) {
				var o = {
					name:p,
					value:field[p]
				}
				f.push(o);
			}
		} else {
			var o = {
				name:field,
				value:null
			};
			f.push(o);
		}
	}
	return this;
}

Query.prototype.where = function(field, operator, value, mode, table) {
	var o = {
		field:field,
		operator:operator,
		value:value,
		mode:mode,
		table:table
	}
	this._where.push(o);
	return this;
}

Query.prototype.order = function(field, mode, table) {
	var o = {
		field:field,
		mode:mode,
		table:table
	}
	this._order.push(o);
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

Query.prototype.group = function(field, table) {
	var o = {
		field:field,
		table:table
	}
	this._group.push(o);
	return this;
}

Query.prototype.having = function(field, operator, value, mode, table) {
	var o = {
		field:field,
		operator:operator,
		value:value,
		mode:mode,
		table:table
	}
	this._where.push(o);
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
	return this._db.query(str);
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
	var arr = [];
	for (var i=0;i<this._order.length;i++) {
		var item = this._order[i];
		var t = item.table || this._table[0].table;

		var tname = this._db.qualify(t.getName());
		var fname = this._db.qualify(item.field);
		
		arr.push(tname+"."+fname+" "+item.mode);
	}
	return (arr.length ? "ORDER BY "+arr.join(", ") : "");
}

Query.prototype._toStringHaving = function() {
	var str = "";
	if (this._having.length) {
		str += "HAVING "+this._toStringCondition(this._having);
	}
	return str;
}

Query.prototype._toStringWhere = function() {
	var str = "";
	if (this._where.length) {
		str += "WHERE "+this._toStringCondition(this._where);
	}
	return str;
}

Query.prototype._toStringCondition = function(list) {
	var arr = [];
	
	for (var i=0;i<list.length;i++) {
		var item = list[i];
		var t = item.table || this._table[0].table;
		var str = "";
		if (i) { str += item.mode+" "; }
		var tname = this._db.qualify(t.getName());
		var fname = this._db.qualify(item.field);
		str += tname+"."+fname+" "+item.operator+" ";
		var value = (item.value === null ? "NULL" : "'"+this._db.escape(item.value)+"'");
		str += value;
		arr.push(str);
	}
	return arr.join(" ");
}

Query.prototype._toStringGroup = function() {
	var arr = [];
	for (var i=0;i<this._group;i++) {
		var item = this._group[i];
		var t = item.table || this._table[0].table;
		var tname = this._db.qualify(t.getName());
		var fname = this._db.qualify(item.field);
		arr.push(tname + "." + fname);
	}
	return arr.join(", ");
}

Query.prototype._toStringTable = function() {
	var arr = [];
	
	for (var i=0;i<this._table.length;i++) {
		var item = this._table[i];
		var table = item.table;
		if (!i) {
			arr.push(this._db.qualify(item.table.getName()));
		} else {
			var str = "";
			if (item.join) { str += item.join+" "; }
			str += "JOIN "+this._db.qualify(table.getName());
			
			var rel = false;
			for (var j=0;j<i;j++) {
				var t2 = this._table[j].table;
				rel = rel || t2.getRelation(table) || table.getRelation(t2);
			}
			if (rel) {
				var owntable = this._db.qualify(rel.owntable.getName());
				var ownfield = this._db.qualify(rel.ownfield);
				var foreigntable = this._db.qualify(rel.foreigntable.getName());
				var foreignfield = this._db.qualify(rel.foreignfield);
				str += " ON "+owntable+"."+ownfield+" = "+foreigntable+"."+foreignfield;
			}
			arr.push(str);
		}
	}
	
	var str = "";
	switch (this._type) {
		case Query.SELECT:
		case Query.DELETE:
			str += "FROM"; break;
		case Query.INSERT: str += "INTO"; break;
	}
	str += " "+arr.join(" ");
	return str;
}

Query.prototype._toStringField = function() {
	switch (this._type) {
		case Query.SELECT:
			var arr = [];
			for (var i=0;i<this._field.length;i++) {
				var fieldset = this._field[i];
				var table = this._table[i].table;
				for (var j=0;j<fieldset.length;j++) {
					var field = fieldset[j];
					if (field.name == "*") {
					    var name = this._db.qualify(table.getName())+".*";
					} else if (field.name.match(/\(/)) {
					    var name = field.name;
					} else {
					    var name = this._db.qualify(table.getName())+"."+this._db.qualify(field.name);
					}
					var alias = field.value;
					if (alias) { name += " AS '"+alias+"'"; }
					arr.push(name);
				}
			}
			return arr.join(", ");
		break;
		
		case Query.INSERT:
			var arr1 = [];
			var arr2 = [];
			for (var i=0;i<this._field.length;i++) {
				var fieldset = this._field[i];
				for (var j=0;j<fieldset.length;j++) {
					var field = fieldset[j];
					var name = this._db.qualify(field.name);
					var value = this._db.escape(field.value);
					arr1.push(name);
					arr2.push("'"+value+"'");
				}
			}
			return "("+arr1.join(", ")+") VALUES ("+arr2.join(", ")+")";
		break;
		
		case Query.UPDATE:
			var arr = [];
			for (var i=0;i<this._field.length;i++) {
				var fieldset = this._field[i];
				for (var j=0;j<fieldset.length;j++) {
					var field = fieldset[j];
					var name = this._db.qualify(field.name);
					var value = this._db.escape(field.value);
					arr.push(name+"='"+value+"'");
				}
			}
			return "SET "+arr.join(", ");
		break;
	}
}
