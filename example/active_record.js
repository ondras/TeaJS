#!/usr/bin/env v8cgi

/**
 * More info on http://www.activerecordjs.org/record.html
 */
var ActiveRecord = require('active_record').ActiveRecord;

ActiveRecord.connect(ActiveRecord.Adapters.v8cgiMySQL, {
	user: 'root', 
	pass: 'root', 
	name: 'testdb'
});


var User = ActiveRecord.create('users',{
    username: '',
    password: '',
    post_count: 0,
    profile: {
        type: 'TEXT',
        value: ''
    }
},{
    getProfileWordCount: function(){
        return this.get('profile').split(/\s+/).length;
    }
});

var jessica = User.create({
    username: 'Jessica',
    password: 'rabbit'
});

/*jessica.username // 'Jessica'  
jessica.get('username'); // 'Jessica'  
jessica.username = 'new username';  
jessica.get('username'); // 'Jessica'  
jessica.set('username','new username');  
jessica.get('username'); // 'new username'
*/

User.findByUsername('Jessica');  
User.findAllByPassword(''); //finds all with blank passwords
