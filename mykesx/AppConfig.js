// This is an application configuration file.
// Ideally, there is one of these per virtual host in apache!
// This file would be outside the document root so it can't be
// served!  It contains MySQL username/passwords and that sort
// of thing.

AppConfig = {
	dbRead: {
		host: 'localhost',
		user: 'mysql_username',
		password: 'mysql_password',
		database: 'mysql_database'
	},
	dbWrite: {
		host: 'localhost',
		user: 'mysql_username',
		password: 'mysql_password',
		database: 'mysql_database'
	},
	consoleFile: '/tmp/v8.log'
};

exports.AppConfig = AppConfig;

