/*

redis.js v0.2: Simple Redis client

Copyright (c) 2012-2020 Tamer Rizk, Inficron Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

exports.Redis = (function(){

	return function(params){

		params['host'] = 'undefined' != typeof params['host'] ? params['host'] : '127.0.0.1';
		params['port'] = 'undefined' != typeof params['port'] ? parseInt(params['port'], 10) : 6379;
		params['password'] = 'undefined' != typeof params['password'] ? params['password'] : '';
		params['bufsz'] = 'undefined' != typeof params['bufsz'] ?  parseInt(params['bufsz'], 10) : 67108864;
		params['db'] = 'undefined' != typeof params['db'] ? params['db'] : '0';
		params['debug'] = 'undefined' != typeof params['debug'] ? params['debug'] : false;

		this.status = '';
		this.rows = 0;
		this.debug = params['debug'];
		this.bufsz = params['bufsz'];		
		this.connection = null;

		var Sock = require('socket').Socket;
		this.connection = new Sock(2, 1, 6);
		this.connection.setOption(Sock.TCP_NODELAY, true);
		this.connection.setOption(Sock.SO_REUSEADDR, true);
		this.connection.setOption(Sock.SO_KEEPALIVE, true);

		if(!this.connection.connect(params['host'], params['port'])) {
			this.status = 'Could not connect to redis';
			return null;
		}

		if(params['password']){
			this.query('AUTH ' + params['password']);
			if(!this.status.match(/OK/i)){
				this.disconnect();
				return null;
			}
		}

		this.query('SELECT ' + params['db']);
		if(!this.status.match(/OK/i)){
			this.disconnect();
			return null;
		}
		this.rows = 0;
		this.status = '';  

	};
})();

exports.Redis.prototype = {

	quote : function(s, c){
		var q = 'undefined' == typeof(c) ? '"' : c;
		var se = new RegExp('(^[' + q + ']+)|(?:[\1]+$)', 'mg');
		s = s.toString();
		s = s.replace(se, '');
		return q + s + q;
	},

	query : function(q){
		if(!q || !this.connection) return null;

		var arg = [];
		var len = 1024;

		q = q.replace(/[\0\1]/g, ' ');
		q = q.replace(/^(?:[\r\n\t]+)|(?:[\r\n\t]+)$/mg, '');
		q = q.replace(/(?:\r\n)+/g, '\\r\\n');
		if(!q.match(/[a-z]/i)) return null;

		var quote = '';
		var delim = {quot:-1, apos:-1, quot_chr:'"', quot_replace:"\1", quot_esc:'(\\\\+)"', quot_match:'("[^"]*[ ][^"]*")', apos_chr:"'", apos_replace:"\1", apos_esc:"(\\\\+)'", apos_match:"('[^']*[ ][^']*')"};
		delim['quot'] = q.indexOf(' "');
		delim['apos'] = q.indexOf(" '");

		if(-1 < delim['quot'] || -1 < delim['apos']){
			quote = -1 == delim['apos'] || (-1 != delim['quot'] && delim['apos'] > delim['quot']) ? 'quot' : 'apos';

			var esc_re = new RegExp(delim[quote+'_esc'], 'g');
			var match_re = new RegExp(delim[quote+'_match']);
			var replace_re = new RegExp(delim[quote+'_replace']+'([0-9]+);', 'g');

			q = q.replace(esc_re, function(m, n){ return delim[quote+'_replace'] + n.length + ';' });

			while((arg = q.match(match_re)) && arg[1] && --len){
				q = q.replace(arg[1], arg[1].replace(/[ ]/g, "\0"));
			}
			if(1 > len) return null;
			q = q.replace(/[ ][ ][ ]*/g, ' ');

			q = q.replace(replace_re, function(m, n){ var c = parseInt(n, 10) || 0; return Array(c+1).join('\\') + delim[quote+'_chr'] });

		}

		arg = q.split(' ');
		len = arg.length;

		var msg = '*'+len+"\r\n";
		for(var i = -1; ++i < len;){
			arg[i] = arg[i].replace(/\0/g, ' ');
			if(arg[i].match(/^(["']).*\1$/)){
				arg[i] = arg[i].replace(/^(?:['"])|(?:['"])$/g, '');
			}
			msg += '$' + arg[i].length + "\r\n" + arg[i] + "\r\n";
		}

		if(this.debug) system.stderr.write(msg + "\n");

		var buf = '';
		var res = [];
		this.rows = 0;
		this.connection.send(msg);
		buf = this.connection.receive(this.bufsz);

		if(!buf){
			this.status = 'No response';
			return null;
		}

		buf = buf.toString('utf8').replace(/^(?:[ \r\n\t]+)|(?:[ \r\n\t]+)$/g, '');

		arg = buf.split("\r\n");
		buf = arg.shift();

		if(buf.match(/^\-/)){
			this.status = buf.replace(/^[\- ]+/g, '');
			return null;
		}

		if(buf.match(/^\+/)){
			this.status = buf.replace(/^[+ ]+/g, '');
			return [];
		}

		if(buf.match(/^\:/)){
			this.status = this.status || 'OK';
			this.rows = 1;
			return [ parseInt(buf.replace(/^[: ]+/g, ''), 10) ];
		}

		if(buf.match(/^\$/)){
			this.status =  this.status || 'OK';
			this.rows = buf.match(/^\$\-1/) ? 0 : 1;
			return 'undefined' == typeof arg[0] && 1 == this.rows ? [''] : arg;
		}

		if(!buf.match(/^\*/)){
			this.status = 'Unknown redis response';
			return null;
		}

		var d = true;
		var sane = 0;
		this.status = this.status || 'OK';
		this.rows = parseInt(buf.replace(/^[* ]+/g, ''), 10);

		len = arg.length;
		for(var i = -1; ++i < len;){
			d = d ? false : true;
			if(d) {
				res.push(arg[i].toString() || '');
				++sane;
				continue;
			}
			if(arg[i].match(/^\$\-1/)){
				d = true;
				++sane;
				res.push(null);
			}
		}
		if(sane != this.rows){
			this.status = 'Invalid redis response. Expected ' + this.rows + ' results, but got: ' + res.toString();
			this.rows = 0;
			return null;
		}
		return res;
	},

	disconnect : function(){
		if(this.connection){
			this.connection.close();
			this.connection = null;
			this.rows = 0;
			this.status = '';
		}
	},
};

/*
var test = function(){
   var redis = new exports.Redis({host:'127.0.0.1', port:6379});   
   if(!redis) system.stdout.write('no redis');
   system.stdout.write(redis.query('SET mykey1 myvalue'));
   system.stdout.write(redis.status);
   redis.disconnect();
};
*/

