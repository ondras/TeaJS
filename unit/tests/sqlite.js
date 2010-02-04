/**
 * This file tests the SQLite module.
 * Database is created in memory, so no intermediate files are created.
 */

var assert = require("assert");
var SQLite = require("sqlite").SQLite;

exports.testSQLite = function() {
	var db = new SQLite().open(":memory:");
	
	db.query("create table test(one varchar(10), two integer primary key)");
	db.query("insert into test (one, two) values ('a', 1)");
	db.query("insert into test (one) values ('b')");
	assert.equal(db.changes(), 1, "rows affected by insert");
	assert.equal(db.insertId(), 2, "last insert id");
	
	var r = db.query("select two from test");
	assert.equal(r.numRows(), 2, "result rows");
	assert.equal(r.numFields(), 1, "result fields");
	
	var names = r.fetchNames();
	assert.equal(names.join(","), "two", "fetch names");

	var arr = r.fetchArrays();
	assert.equal(arr[1][0], "2", "fetch arrays");
	
	var obj = r.fetchObjects();
	assert.equal(obj[1]["two"], "2", "fetch objects");

	db.close();
}

