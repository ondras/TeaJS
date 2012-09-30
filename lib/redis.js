/* 

redis.js: Simple Redis client

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

exports.Redis = function(bufsz){
   
   this.maxsz = 67108864;
   this.status = '';
   this.rows = 0;
   this.connection = null;
   this.bufsz = parseInt(bufsz || this.maxsz, 10);
   
   this.connect = function(host, port, password, db){

      if(this.connection) return this.connection;

      host = host || '127.0.0.1';
      port = parseInt(port || 6379, 10);
      password = password || '';
      db = db || '0';
      
      var Sock = require('socket').Socket;
      this.connection = new Sock(2, 1, 6);
      this.connection.setOption(Sock.TCP_NODELAY, true);
      this.connection.setOption(Sock.SO_REUSEADDR, true);
      this.connection.setOption(Sock.SO_KEEPALIVE, true);

      if(!this.connection.connect(host, port)) {
         this.status = 'Could not connect to redis';
         this.connection = false;       
         return null;
      }

      if(password){
         this.query('AUTH '+password);
         if(!this.status.match(/OK/i)){
            this.disconnect();
            return null;
         }
      }

      this.query('SELECT '+db);
      if(!this.status.match(/OK/i)){
         this.disconnect();
         return null;
      }
      this.rows = 0;
      this.status = '';  

      return this;
   };

   this.query = function(q){
      if(!q || !this.connection) return null;

      var arg = [];
      var len = 1024;
      q = q.replace(/\0/g, ' ');
      q = q.replace(/(?:^[ \r\n\t]+)|(?:[ \r\n\t]+$)/g, '');
      q = q.replace(/(?:\r\n)+/g, '\\r\\n');
      q = q.replace(/\\"/g, '\\&quot;');

      while((arg = q.match(/("[^"]*[ ][^"]*")/)) && arg[1] && --len){
         q = q.replace(new RegExp(arg[1], 'g'), arg[1].replace(/[ ]/g, "\0"));
      }

      if(!q.match(/[a-z]/i) || 1 > len) return null;
      q = q.replace(/[ ][ ][ ]*/g, ' ');      
      q = q.replace(/\\&quot;/g, '\\"');      
      arg = q.split(' ');
      len = arg.length;
      
      var msg = '*'+len+"\r\n"; 
      for(var i = -1; ++i < len;){
         arg[i] = arg[i].replace(/\0/g, ' ');
         msg += '$'+arg[i].length+"\r\n"+arg[i]+"\r\n";
      }
  
      var buf = '';
      var res = [];
      this.rows = 0;
      this.connection.send(msg);     
      buf = this.connection.receive(this.bufsz);

      if(!buf){
         this.status = 'No response';
         return null;
      }
     
      buf = buf.toString('utf8').replace(/(?:^[ \r\n\t]+)|(?:[ \r\n\t]+$)/g, '');

      arg = buf.split("\r\n");
      buf = arg.shift();
      len = arg.length;

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
         return arg || [];
      }
      if(!buf.match(/^\*/)){
         this.status = 'Unknown redis response';
         return null;
      } 

      var d = true;
      var sanity = 0;
      this.status = this.status || 'OK';
      this.rows = parseInt(buf.replace(/^[* ]+/g, ''), 10);
      for(var i = -1; ++i < len;){
         d = d ? false : true;
         if(d) {
            res.push(arg[i]);
            ++sanity;
            continue;
         }
         if(arg[i].match(/^\$\-1/)){
            d = true;
            ++sanity;
            res.push(null);            
         }
      }
      if(sanity != this.rows){
         this.status = 'Invalid redis response. Expected '+this.rows+' results, but got: '+res.toString();
         this.rows = 0;
         return null;
      }
      return res;
   };

   this.disconnect = function(){
      if(this.connection){
         this.connection.close();
         this.connection = null;
         this.rows = 0;
         this.status = '';
      }
      return this;
   };


};

/*
var test = function(){
   var redis = new exports.Redis();
   redis.connect(undefined,undefined,'foobared');
   if(!redis.connection) system.stdout.write('no redis');
   system.stdout.write(redis.query('SET mykey1 myvalue'));
   system.stdout.write(redis.status);
   redis.disconnect();
};
*/
