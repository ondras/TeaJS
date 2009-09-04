/*
 *	Testbench for the PostgreSQL database module
 *
 */

var assert = require("assert");
var req = new require("pgsql");

exports.testFile = function() {
  var pgsql = new req.PostgreSQL();
  var db = pgsql.connect("host=/var/run/postgresql/ dbname=template1 user=postgres");
  var query = db.query('SELECT COUNT(*) AS val FROM information_schema.sql_implementation_info');  
  var val = query.fetchAll();
  for (var i in val) {
    assert.assertEquals('val '+i+' [Number]', Number('12'), Number(val[i]));
    assert.assertEquals('val '+i+' [String]', String('12'), val[i].toString());
  }
}
