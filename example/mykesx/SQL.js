// SQL class
// Lean but flexible SQL class for querying MySQL.

// The application will use SQL.update() to do queries that write to the database.
// To read from the database, getDataRow(), getDataRows(), or getScalar() is used.

// This separation of read and write allows us to have distinct read and write
// MySQL connections.  The backend can be scaled using MySQL's built-in replication
// and the application code is already set up to use it.  The only real change
// would be in the AppConfig class/file, where the read/write connection information
// is defined.

// The functions honor / maintain numRows and insertId member variables.

// The class also provides transaction methods.

// An Error() object is thrown when an error occurs.  It is up to the calling code
// to trap the error with try/catch.

// Examples:
/*
// atomic operation storing to two tables
try {
	SQL.beginTransaction();
	SQL.update('REPLACE INTO some_table VALUES (...)');
	SQL.update('REPLACE INTO some_other_table VALUES (...)');
	SQL.commit();
}
catch (e) {
	SQL.rollback();
	errorHandler(); // see errorHandler.js
}

// Ignore drop table that fails.  Yes, MySQL has DROP TABLE IF EXISTS, but this is
// just to illustrate the concept of ignoring errors.
try {
	SQL.update('DROP TABLE some_table');
}
catch (e) {
	// ignore the error
}

// The getScalar() method is quite handy for certain types of queries:
var count = SQL.getScalar('SELECT COUNT(*) FROM some_table');

*/


// NOTE: This class is a singleton.  It does not provide for capability to read
// from two databases at the same time.  It could easily be changed from a singleton
// to a class that would require instantiation:
/*

var db = new MySQL(connectionInfo);
db.getScalar('SELECT COUNT(*) FROM some_table');
// etc.
*/

var MySQL = require('mysql').MySQL;

var SQL = function() {
	// private member variables
	var dbRead =  null;
	var dbWrite = null;

	// private member function
	function execute(db, query) {
		try {
			return db.query(query);
		}
		catch (e) {
			throw new Error('MySQL Error<br/>' + e.message + '<br/>' + query);
		}
	}

	// private member function
	function readHandle() {
		if (!dbRead) {
			var config = AppConfig.dbRead || AppConfig.dbConfig;
			dbRead = new MySQL().connect(config.host, config.user, config.password, config.database);
		}
		return dbRead;
	}
	
	// private member function
	function writeHandle() {
		if (!dbWrite) {
			var config = AppConfig.dbWrite || AppConfig.dbConfig;
			dbWrite = new MySQL().connect(config.host, config.user, config.password, config.database);
		}
		return dbWrite;
	}

	// these are the public members:	
	return {
		insertId: 0,
		numRows: 0,
		getDataRow: function(query) {
			var r = execute(readHandle(), query);
			r = r.fetchObjects();
			return r[0];
		},
		getDataRows: function(query) {
			var r = execute(readHandle(), query);
			r = r.fetchObjects();
			return r;
		},
		getScalar: function(query) {
			var r = execute(readHandle(), query);
			r = r.fetchArrays();
			return r[0][0];
		},
		update: function(query) {
			var db = writeHandle();
			execute(db, query);
			this.insertId = db.insertId();
			this.numRows = db.affectedRows();
		},
		startTransaction: function() {
			execute(writeHandle(), 'START TRANSACTION');
		},
		commit: function() {
			execute(writeHandle(), 'COMMIT');
		},
		rollback: function() {
			execute(writeHandle(), 'ROLLBACK');
		},
		quote: function(s) {
			return "'" + Util.addslashes(s) + "'";
		}
	}
}();

exports.SQL = SQL;
