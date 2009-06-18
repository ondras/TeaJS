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
	assert.assertEquals("rows affected by insert", 1, db.changes());
	assert.assertEquals("last insert id", 2, db.insertId());
	
	var r = db.query("select two from test");
	assert.assertEquals("result rows", 2, r.numRows());
	assert.assertEquals("result fields", 1, r.numFields());
	
	var names = r.fetchNames();
	assert.assertEquals("fetch names", "two", names.join(","));

	var arr = r.fetchArrays();
	assert.assertEquals("fetch arrays", "2", arr[1][0]);
	
	var obj = r.fetchObjects();
	assert.assertEquals("fetch objects", "2", obj[1]["two"]);

	db.close();
}

