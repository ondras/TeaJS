// SQL

// this needs to be an object via new() so it can be used by multiple threads.

var MySQL = require('mysql').MySQL;

var SQL = function() {
	var dbRead =  null;
	var dbWrite = null;

	function execute(db, query) {
//		console.log(query);
//		println(query);
		try {
			return db.query(query);
		}
		catch (e) {
			throw new Error('MySQL Error<br/>' + e.message + '<br/>' + query);
		}
	}

	function readHandle() {
		if (!dbRead) {
			var config = AppConfig.dbRead || AppConfig.dbConfig;
			dbRead = new MySQL().connect(config.host, config.user, config.password, config.database);
		}
		return dbRead;
	}
	
	function writeHandle() {
		if (!dbWrite) {
			var config = AppConfig.dbWrite || AppConfig.dbConfig;
			dbWrite = new MySQL().connect(config.host, config.user, config.password, config.database);
		}
		return dbWrite;
	}
	
	return {
		insertId: 0,
		numRows: 0,
		getDataRow: function(query) {
	//		console.log(query);
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
	//		console.log(query);
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
		},
		where: function(example) {
			var parts = [];
			for (var key in example) {
				parts.push(key + '=' + SQL.quote(example[key]));
			}
			if (parts.length) {
				return ' WHERE ' + parts.join(' AND ');
			}
			else {
				return '';
			}
		}
	}
}();

exports.SQL = SQL;
