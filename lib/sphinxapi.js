//
// $Id: sphinxapi.js 1094 2013-03-18 16:50:22Z $
//
// Copyright (c) 2013-2020, Tamer Rizk. All rights reserved
//
// This program is free software; you can redistribute it 
// and/or modify it under the terms of the GNU General 
// Public License. You should have received a copy of the 
// GPL license along with this program; if you
// did not, you can find it at http://www.gnu.org/
//

var Assert = require("assert");
var Socket = require("socket").Socket;
var Buffer = require("binary").Buffer;
var packlib = require("bufferpack").BufferPack;
var sprintlib = require("sprintf");

function assert(cond){
	return Assert.equal(cond, true);
}

function is_int(n) {
	return typeof n == "number" && n % 1 == 0;
}

function is_numeric(n) {
	return typeof n == "number";
}

function is_bool(b){
	return typeof b == "boolean";
}

function is_array(a){
	return Object.prototype.toString.call(a) == "[object Array]" ? true : false;
}

function is_hash(h){
	return typeof h == "object";
}

function is_string(s){
	return typeof s == "string";
}

function count(a){
	var c = 0;
	if(is_array(a)){
		c = a.length;	
	}else if(is_hash(a)){
		for(var i in a){
			c += 2;
		}			
	}
	return c;
}

function default_val(arg, val){
	return "undefined" == typeof arg ? val : arg;
}

function in_array(a, b, strict){
	strict = default_val(strict, true);
	if(!is_array(b)){
		if(!is_string(b) && !is_numeric(b)) 
			return false;
		b = [b];
	}
	var _a = {};
	if(is_array(a)){
		for(var i in a){
			_a[a[i]] = i;
		}				
	}else if(!is_hash(a)){
		return false;
	}else{
		_a = a;		
	}
	
	for(var i in b){
		if(strict){
			if(!(b[i] in _a))
				return false
		}else{
			if(!(b[i] in _a) && !(b[i] in a))
				return false			
		}
		/*
		if(strict){
			if("undefined" == typeof _a[b[i]])
				return false
		}else{
			if("undefined" == typeof _a[b[i]] && "undefined" == typeof a[b[i]])
				return false			
		}
		*/
	}

	return true;
}

function values(a){
	var _a = [];
	for(var i in a){
		_a.push(a[i]);
	}
	return _a;
}

function print_buf(buf){
	var str = buf.toSource().replace(/(?:^.*\[)|(?:\].*$)/g,'');
	var a = str.split(', ');
	for(var i in a){
		if("0" == a[i])
			continue;
		a[i] = String.fromCharCode(a[i]);
	}
	return a.join(',');
}

function buf_len(bufs){
	var l = 0;
	for (var i in bufs){
		l += bufs[i].length;
	}
	return l;
}

function buf_join(bufs){
	var pos = 0;	
	var buf = new Buffer(Array(buf_len(bufs)+1).join(String.fromCharCode(0)), "utf8");
	for (var i in bufs){
		buf.copyFrom(bufs[i], 0, pos, pos + bufs[i].length);
		pos += bufs[i].length;
	}
	return buf;
}

/// pack 64-bit signed
function sph_packi64(v){
	v = v+'';
	var r = parseFloat(v, 10);
	var s = parseInt(v, 10);
	if( 0 == r-s)
		return packlib.pack(">LL", [s < 0 ? -1 : 0, s]);//[v>>32, v&0xFFFFFFFF]);

	var q = strlen(v) - 13;
	var p = q > 0 ? q : 0;
	var lo = Math.abs(parseFloat(v.substr(p)));
	var hi = Math.abs(parseFloat(v.substr(0, p)));

	p = lo + hi*1316134912.0; // (10 ^ 13) % (1 << 32) = 1316134912
	q = Math.floor(p/4294967296.0);
	var l = p - (q*4294967296.0);
	var h = hi*2328.0 + q; // (10 ^ 13) / (1 << 32) = 2328

	if ( r<0 ){
		if (l==0){
			h = 4294967296.0 - h;
		}else{
			h = 4294967295.0 - h;
			l = 4294967296.0 - l;
		}
	}

	return packlib.pack(">LL", [h, l]);
}

/// pack 64-bit unsigned
function sph_packu64(v){
	
	v = v+'';
	var r = parseFloat(v, 10);
	var s = parseInt(v, 10);

	if (is_int(r))
		return packlib.pack(">LL", [0, s]);

	var q = strlen(v) - 13;
	var p = q > 0 ? q : 0;
	var lo = parseFloat(v.substr(p));
	var hi = parseFloat(v.substr(0, p));
       
	var m = lo + hi*1316134912.0;
	q = Math.floor(m / 4294967296.0);
	var l = m - (q * 4294967296.0);
	var h = hi*2328.0 + q;

	return packlib.pack(">LL", [h, l]);

}

// unpack 64-bit unsigned
function sph_unpacku64(v, p){
	p = "undefined" == typeof p ? 0 : p;
	var a = values(packlib.unpack(">L*L*", v, p));
	var hi = parseInt(a[0],10); 
	var lo = parseInt(a[1],10);
	
	if (0 == hi){
		if (0<lo)
			return lo;
		return parseFloat(sprintlib.sprintf("%u", lo), 10);
	}

	hi = parseFloat(sprintlib.sprintf("%u", hi), 10);
	lo = parseFloat(sprintlib.sprintf("%u", lo), 10);
       
	var q = Math.floor(hi/10000000.0);
	var r = hi - q*10000000.0;
	var m = lo + r*4967296.0;
	var mq = Math.floor(m/10000000.0);
	var l = m - mq*10000000.0;
	var h = q*4294967296.0 + r*429.0 + mq;

	h = sprintlib.sprintf("%.0f", h);
	l = sprintlib.sprintf("%07.0f", l);
	if ("0"==h)
		return parseFloat(sprintlib.sprintf("%.0f", l), 10);

	return parseFloat(h+""+l, 10);
}

// unpack 64-bit signed
function sph_unpacki64(v, p){
	var a = values(packlib.unpack(">L*L*", v, p));
	var hi = parseInt(a[0], 10);
	var lo = parseInt(a[1], 10);

	if (0==hi){
		if (0<lo)
			return $lo;
		return sprintlib.sprintf("%u", lo);
	}else if (-1==hi){
		if (0>lo)
			return lo;
		return sprintlib.sprintf("%.0f", lo - 4294967296.0);
	}
       
	var neg = "";
	var c = 0;
	if (0>hi){
		hi = ~hi;
		lo = ~lo;
		c = 1;
		neg = "-";
	}      

	hi = parseFloat(sprintlib.sprintf("%u", hi), 10);
	lo = parseFloat(sprintlib.sprintf("%u", lo), 10);

	var q = Math.floor(hi/10000000.0);
	var r = hi - q*10000000.0;
	var m = lo + r*4967296.0;
	var mq = Math.floor(m/10000000.0);
	var l = m - mq*10000000.0 + c;
	var h = q*4294967296.0 + r*429.0 + mq;

	h = sprintlib.sprintf("%.0f", h);
	l = sprintlib.sprintf("%07.0f", l);
    if ("0"==h)
		return parseFloat(neg + "" + sprintlib.sprintf("%.0f", parseFloat(l, 10)), 10);

	return parseFloat(neg+""+h+""+l, 10);

}

function sph_fixuint(value){
	if (0 > value) 
		value += (1<<32);
	return value;	
}


/// sphinx searchd client class
exports.SphinxClient = (function(){

	return function(){
		/// known searchd commands
		this.SEARCHD_COMMAND_SEARCH 		= 0;
		this.SEARCHD_COMMAND_EXCERPT 		= 1;
		this.SEARCHD_COMMAND_UPDATE 		= 2;
		this.SEARCHD_COMMAND_KEYWORDS		= 3;
		this.SEARCHD_COMMAND_PERSIST		= 4;
		this.SEARCHD_COMMAND_STATUS 		= 5;
		this.SEARCHD_COMMAND_FLUSHATTRS 	= 7;

		/// current client-side command implementation versions
		this.VER_COMMAND_SEARCH 		= 0x119;
		this.VER_COMMAND_EXCERPT 		= 0x104;
		this.VER_COMMAND_UPDATE 		= 0x102;
		this.VER_COMMAND_KEYWORDS 		= 0x100;
		this.VER_COMMAND_STATUS 		= 0x100;
		this.VER_COMMAND_QUERY 			= 0x100;
		this.VER_COMMAND_FLUSHATTRS	= 0x100;

		/// known searchd status codes
		this.SEARCHD_OK 					= 0;
		this.SEARCHD_ERROR 				= 1;
		this.SEARCHD_RETRY 				= 2;
		this.SEARCHD_WARNING 			= 3;

		/// known match modes
		this.SPH_MATCH_ALL 				= 0;
		this.SPH_MATCH_ANY 				= 1;
		this.SPH_MATCH_PHRASE 			= 2;
		this.SPH_MATCH_BOOLEAN 			= 3;
		this.SPH_MATCH_EXTENDED 		= 4;
		this.SPH_MATCH_FULLSCAN 		= 5;
		this.SPH_MATCH_EXTENDED2 		= 6;	// extended engine V2 (TEMPORARY, WILL BE REMOVED)

		/// known ranking modes (ext2 only)
		this.SPH_RANK_PROXIMITY_BM25 	= 0;	///< default mode, phrase proximity major factor and BM25 minor one
		this.SPH_RANK_BM25 				= 1;	///< statistical mode, BM25 ranking only (faster but worse quality)
		this.SPH_RANK_NONE 				= 2;	///< no ranking, all matches get a weight of 1
		this.SPH_RANK_WORDCOUNT 		= 3;	///< simple word-count weighting, rank is a weighted sum of per-field keyword occurence counts
		this.SPH_RANK_PROXIMITY 		= 4;
		this.SPH_RANK_MATCHANY 			= 5;
		this.SPH_RANK_FIELDMASK 		= 6;
		this.SPH_RANK_SPH04 				= 7;
		this.SPH_RANK_EXPR 				= 8;
		this.SPH_RANK_TOTAL 				= 9;

		/// known sort modes
		this.SPH_SORT_RELEVANCE 		= 0;
		this.SPH_SORT_ATTR_DESC 		= 1;
		this.SPH_SORT_ATTR_ASC 			= 2;
		this.SPH_SORT_TIME_SEGMENTS  	= 3;
		this.SPH_SORT_EXTENDED  		= 4;
		this.SPH_SORT_EXPR  				= 5;

		/// known filter types
		this.SPH_FILTER_VALUES 			= 0;
		this.SPH_FILTER_RANGE 			= 1;
		this.SPH_FILTER_FLOATRANGE 	= 2;

		/// known attribute types
		this.SPH_ATTR_INTEGER 			= 1;
		this.SPH_ATTR_TIMESTAMP 		= 2;
		this.SPH_ATTR_ORDINAL 			= 3;
		this.SPH_ATTR_BOOL 				= 4;
		this.SPH_ATTR_FLOAT 				= 5;
		this.SPH_ATTR_BIGINT 			= 6;
		this.SPH_ATTR_STRING 			= 7;
		this.SPH_ATTR_MULTI 				= 0x40000001;
		this.SPH_ATTR_MULTI64 			= 0x40000002;

		/// known grouping functions
		this.SPH_GROUPBY_DAY 			= 0;
		this.SPH_GROUPBY_WEEK 			= 1;
		this.SPH_GROUPBY_MONTH 			= 2;
		this.SPH_GROUPBY_YEAR 			= 3;
		this.SPH_GROUPBY_ATTR 			= 4;
		this.SPH_GROUPBY_ATTRPAIR 		= 5;
	
		// per-client-object settings
		this._host		= "localhost";		///< searchd host (default is "localhost")
		this._port		= 9312;				///< searchd port (default is 9312)
		this._path		= false;				
		this._socket	= false;

		// per-query settings
		this._offset	= 0;			///< how many records to seek from result-set start (default is 0)
		this._limit		= 20;			///< how many records to return from result-set starting at offset (default is 20)
		this._min_id	= 0;			///< min ID to match (default is 0, which means no limit)
		this._max_id	= 0;			///< max ID to match (default is 0, which means no limit)
		this._filters	= [];			///< search filters
		this._weights	= [];			///< per-field weights (default is 1 for all fields)
		this._mode		= this.SPH_MATCH_ALL;			///< query matching mode (default is SPH_MATCH_ALL)
		this._sort		= this.SPH_SORT_RELEVANCE;		///< match sorting mode (default is SPH_SORT_RELEVANCE)
		this._sortby	= "";			///< attribute to sort by (defualt is "")
		this._groupby	= "";			///< group-by attribute name
		this._groupdistinct	= "";	///< group-by count-distinct attribute
		this._groupsort	= "@group desc";		///< group-by sorting clause (to sort groups in result set with)
		this._groupfunc	= this.SPH_GROUPBY_DAY;				///< group-by function (to pre-process group-by attribute value with)
		this._ranker		= this.SPH_RANK_PROXIMITY_BM25;	///< ranking mode (default is SPH_RANK_PROXIMITY_BM25)
		this._rankexpr		= "";		///< ranking mode expression (for SPH_RANK_EXPR)
		this._maxmatches	= 100000;	///< max matches to retrieve
		this._cutoff		= 0;		///< cutoff to stop searching at (default is 0)
		this._retrycount	= 0;		///< distributed retries count
		this._retrydelay	= 0;		///< distributed retries delay
		this._anchor		= {};		///< geographical anchor point
		this._indexweights	= {};	///< per-index weights
		this._maxquerytime	= 0;	///< max query time, milliseconds (default is 0, do not limit)
		this._fieldweights	= {};	///< per-field-name weights
		this._overrides 	= {};		///< per-query attribute values overrides
		this._select		= "*";	///< select-list (attributes or expressions, with optional aliases)

		this._error			= ""; 	///< last error message; per-reply fields (for single-query case),
		this._warning		= "";		///< last warning message
		this._connerror	= false;	///< connection error vs remote error flag

		this._reqs			= [];		///< requests array for multi-query, requests storage (for multi-query case)
		this._arrayresult	= false;	///< whether result["matches"] should be a hash or an array
		this._timeout		= 0;		///< connect timeout
	};

})();

exports.SphinxClient.prototype = {
	// may be used within onexit handler
	__destroy : function(){
		if (this._socket)
			this._socket.close();
	},

	/// get last error message (string)
	GetLastError : function(){
		return this._error;
	},

	/// get last warning message (string)
	GetLastWarning : function(){
		return this._warning;
	},

	/// get last error flag (to tell network connection errors from searchd errors or broken responses)
	IsConnectError : function(){
		return this._connerror;
	},

	/// set searchd host name (string) and port (integer)
	SetServer : function(host, port){
		port = default_val(port, 0);
		assert(is_string(host));
		if ("/" == host[0]){
			this._path = "unix://" + host;
			return;
		}
		if ("unix://" == host.substr(0, 7)){
			this._path = host;
			return;
		}
				
		assert(is_int(port));
		this._host = host;
		this._port = port;
		this._path = "";
	},

	/// set server connection timeout (0 to remove)
	SetConnectTimeout : function(timeout){
		assert(is_numeric(timeout));
		this._timeout = timeout;
	},

	_Send : function(handle, data, length){
		if (!handle.send(data)){
			this._error = "connection unexpectedly closed (timed out?)";
			this._connerror = true;
			return false;
		}
		return true;
	},

	
	/// connect to searchd server
	_Connect : function(){

		if (this._socket){
			// we are in persistent connection mode, so we have a socket
			// however, need to check whether it's still alive
			var p = undefined;
			try {
				p = this._socket.getPeerName();
			}catch(e){
				// do nothing
			}
			if ( "undefined" !=typeof p && is_array(p) && 0 != count(p)  )		
				return this._socket;

			// force reopen
			this._socket = false;
		}

		errno = 0;
		errstr = "";
		this._connerror = false;

		if (this._path){
			host = this._path;
			port = 0;
		}else{
			host = this._host;
			port = this._port;
		}

		this._socket = new Socket(2, 1, 6);
		if (!this._socket.connect(host, port)){
			if (this._path)
				location = this._path;
			else
				location = this._host + ":" + this._port;
						
			this._error = "connection to " + location + " failed";
			this._connerror = true;
			return false;
		}

		// send my version
		// this is a subtle part. we must do it before (!) reading back from searchd.
		// because otherwise under some conditions (reported on FreeBSD for instance)
		// TCP stack could throttle write-write-read pattern because of Nagle.
		if (!this._Send(this._socket, packlib.pack(">L", [1]), 4) ){
			this._socket.close();
			this._error = "failed to send client protocol version";
			return false;
		}

		// check version
		var a = packlib.unpack(">L*", this._socket.receive(4));
		var v = parseInt(a[0], 10);
		
		if (1 > v){
			this._socket.close();
			this._error = "expected searchd protocol version 1+, got version '"+v+"'";
			return false;
		}

		return this._socket;
	},

	/// get and check response packet from searchd server
	_GetResponse : function(fp, client_ver){
		var response = new Buffer(0), len = 0, ver = "", status = "", a = [];
		var header = fp.receive(8);
		if (8 == header.length){
			a = packlib.unpack("HHL", header);

			status = a["0"];
			ver = a["1"];
			len = parseInt(a["2"], 10);
			var chunk = "";
			var left = len;
			var max = left;

			while ( left>0 && ( chunk = fp.receive(left < 8192 ? left : 8192) ) && 0 < max-- ){
				if (chunk){
					var tmp = response;
					response = new Buffer(tmp.length + chunk.length);
					tmp.copy(response);
					chunk.copy(response, tmp.length);
					left -= chunk.length;
				}
			}
		}

		// check response
		var read = response.length;
		if (!response || read != len){
			this._error = len
				? "failed to read searchd response (status=" + status + ", ver=" + ver + ", len=" + len + ", read=" + read + ")"
				: "received zero-sized searchd response";
			return false;
		}

		// check status
		if (status == this.SEARCHD_WARNING){
			a = packlib.unpack(">L", response.substr(0, 4));
			var wlen = parseInt(a[0], 10);
			
			this._warning = response.substr(4, wlen);
			return response.response.slice(4, 4 + wlen).toString("utf8");
		}

		if (status == this.SEARCHD_ERROR ){
			this._error = "searchd error: " + response.slice(0, 4).toString("utf8");
			return false;
		}

		if (status == this.SEARCHD_RETRY){
			this._error = "temporary searchd error: " + response.slice(0, 4).toString("utf8");;
			return false;
		}

		if(status != this.SEARCHD_OK){
			this._error = "unknown status code '" + status + "'";
			return false;
		}

		// check version
		if (ver < client_ver){
			this._warning = sprintlib.sprintf("searchd command v.%d.%d older than client's v.%d.%d, some options might not work", ver>>8, ver&0xff, client_ver>>8, client_ver&0xff );
		}

		return response;
	},

	/////////////////////////////////////////////////////////////////////////////
	// searching
	/////////////////////////////////////////////////////////////////////////////

	/// set offset and count into result set,
	/// and optionally set max-matches and cutoff limits
	SetLimits : function(offset, limit, max, cutoff){

		max = default_val(max, 0);
		cutoff = default_val(cutoff, 0);

		assert(is_int(offset) );
		assert(is_int(limit) );
		assert(offset >= 0 );
		assert(limit > 0);
		assert(max >= 0);
		this._offset = offset;
		this._limit = limit;

		if (0 < max)
			this._maxmatches = max;
		if (0 < cutoff)
			this._cutoff = cutoff;
	},

	/// set maximum query time, in milliseconds, per-index
	/// integer, 0 means "do not limit"
	SetMaxQueryTime : function(max){
		assert(is_int(max));
		assert(max >= 0);
		this._maxquerytime = max;
	},

	/// set matching mode
	SetMatchMode : function(mode)
	{
		assert( mode == this.SPH_MATCH_ALL
			|| mode == this.SPH_MATCH_ANY
			|| mode == this.SPH_MATCH_PHRASE
			|| mode == this.SPH_MATCH_BOOLEAN
			|| mode == this.SPH_MATCH_EXTENDED
			|| mode == this.SPH_MATCH_FULLSCAN
			|| mode == this.SPH_MATCH_EXTENDED2 );
		this._mode = mode;
	},

	/// set ranking mode
	SetRankingMode : function(ranker, rankexpr){
	
		rankexpr = default_val(rankexpr, "");

		assert( ranker >= 0 && ranker < this.SPH_RANK_TOTAL );
		assert(is_string(rankexpr));
		this._ranker = ranker;
		this._rankexpr = rankexpr;
	},

	/// set matches sorting mode
	SetSortMode : function(mode, sortby){

		sortby = default_val(sortby, "");

		assert(
			mode == this.SPH_SORT_RELEVANCE ||
			mode == this.SPH_SORT_ATTR_DESC ||
			mode == this.SPH_SORT_ATTR_ASC ||
			mode == this.SPH_SORT_TIME_SEGMENTS ||
			mode == this.SPH_SORT_EXTENDED ||
			mode == this.SPH_SORT_EXPR );
		assert(is_string(sortby));
		assert( mode == this.SPH_SORT_RELEVANCE || sortby.length > 0 );

		this._sort = mode;
		this._sortby = sortby;
	},

	/// bind per-field weights by order
	/// DEPRECATED; use SetFieldWeights() instead
	SetWeights : function(weights)
	{
		assert(is_array(weights));
		for (var name in weights)
			assert(is_int(weights[name]));

		this._weights = weights;
	},

	/// bind per-field weights by name
	SetFieldWeights : function(weights){
		assert (is_hash(weights));
		for (var name in weights){
			assert(is_string(name));
			assert(is_int(weights[name]));
		}
		this._fieldweights = weights;
	},

	/// bind per-index weights by name
	SetIndexWeights : function(weights){
		assert(is_hash(weights));
		
		for (var idx in weights){
			assert(is_string(idx));
			assert(is_int(weights[idx]));
		}
		this._indexweights = weights;
	},

	/// set IDs range to match
	/// only match records if document ID is between min and max (inclusive)
	SetIDRange : function(min, max){
		assert(is_numeric(min));
		assert(is_numeric(max));
		assert(min <= max);
		this._min_id = min;
		this._max_id = max;
	},

	/// set values set filter
	/// only match records where attribute value is in given set
	SetFilter : function(attribute, values, exclude){

		exclude = default_val(exclude, false);

		assert(is_string(attribute));
		assert(is_array(values));
		assert(values.length);

		if (is_array(values) && values.length){
			for (var i in values)
				assert(is_numeric(values[i]));

			this._filters.push( {"type":this.SPH_FILTER_VALUES, "attr":attribute, "exclude":exclude, "values":values} );
		}
	},

	/// set range filter
	/// only match records if attribute value is beetwen min and max (inclusive)
	SetFilterRange : function(attribute, min, max, exclude){

		exclude = default_val(exclude, false);

		assert(is_string(attribute));
		assert(is_numeric(min));
		assert(is_numeric(max));
		assert(min <= max);

		this._filters.push( {"type":this.SPH_FILTER_RANGE, "attr":attribute, "exclude":exclude, "min":min, "max":max} );
	},

	/// set float range filter
	/// only match records if attribute value is beetwen min and max (inclusive)
	SetFilterFloatRange : function(attribute, min, max, exclude){

		exclude = default_val(exclude, false);

		assert(is_string(attribute));
		assert(is_float(min));
		assert(is_float(max));
		assert(min <= max);

		this._filters.push( {"type":this.SPH_FILTER_FLOATRANGE, "attr":attribute, "exclude":exclude, "min":min, "max":max} );
	},

	/// setup anchor point for geosphere distance calculations
	/// required to use @geodist in filters and sorting
	/// latitude and longitude must be in radians
	SetGeoAnchor : function(attrlat, attrlong, lat, long){
		assert(is_string(attrlat));
		assert(is_string(attrlong));
		assert(is_numeric(lat));
		assert(is_numeric(long));

		this._anchor = {"attrlat":attrlat, "attrlong":attrlong, "lat":lat, "long":long};
	},

	/// set grouping attribute and function
	SetGroupBy : function(attribute, func, groupsort){

		groupsort = default_val(groupsort, "@group desc");

		assert (is_string(attribute));
		assert (is_string(groupsort));
		assert (func == this.SPH_GROUPBY_DAY
			|| func == this.SPH_GROUPBY_WEEK
			|| func == this.SPH_GROUPBY_MONTH
			|| func == this.SPH_GROUPBY_YEAR
			|| func == this.SPH_GROUPBY_ATTR
			|| func == this.SPH_GROUPBY_ATTRPAIR);

		this._groupby = attribute;
		this._groupfunc = func;
		this._groupsort = groupsort;
	},

	/// set count-distinct attribute for group-by queries
	SetGroupDistinct : function(attribute){
		assert(is_string(attribute));
		this._groupdistinct = attribute;
	},

	/// set distributed retries count and delay
	SetRetries : function(count, delay){
		delay = default_val(delay, 0);

		assert(is_int(count) && count >= 0);
		assert(is_int(delay) && delay >= 0);
		this._retrycount = count;
		this._retrydelay = delay;
	},

	/// set result set format (hash or array; hash by default)
	/// needed for group-by-MVA result sets that may contain duplicate IDs
	SetArrayResult : function (arrayresult){
		assert(is_bool(arrayresult));
		this._arrayresult = arrayresult;
	},

	/// set attribute values override
	/// there can be only one override per attribute
	/// values must be a hash that maps document IDs to attribute values
	SetOverride : function (attrname, attrtype, values){
		assert(is_string(attrname));
		assert( in_array(attrtype, [this.SPH_ATTR_INTEGER, this.SPH_ATTR_TIMESTAMP, this.SPH_ATTR_BOOL, this.SPH_ATTR_FLOAT, this.SPH_ATTR_BIGINT]) );
		assert(is_array(values));

		this._overrides[attrname] = {"attr":attrname, "type":attrtype, "values":values};
	},

	/// set select-list (attributes or expressions), SQL-like syntax
	SetSelect : function(select){
		assert(is_string(select));
		this._select = select;
	},

	//////////////////////////////////////////////////////////////////////////////

	/// clear all filters (for multi-queries)
	ResetFilters : function(){
		this._filters = [];
		this._anchor = [];
	},

	/// clear groupby settings (for multi-queries)
	ResetGroupBy : function(){
		this._groupby		= "";
		this._groupfunc	= this.SPH_GROUPBY_DAY;
		this._groupsort	= "@group desc";
		this._groupdistinct = "";
	},

	/// clear all attribute value overrides (for multi-queries)
	ResetOverrides : function(){
		this._overrides = {};
	},

	//////////////////////////////////////////////////////////////////////////////

	/// connect to searchd server, run given search query through given indexes,
	/// and return the search results
	Query : function(query, index, comment){

		index = default_val(index, "*");
		comment = default_val(comment, "");

		assert (0 == count(this._reqs));

		this.AddQuery(query, index, comment);
		var results = this.RunQueries();
		this._reqs = []; // just in case it failed too early

		if (!is_array(results))
			return false; // probably network error; error message should be already filled

		this._error = results[0]["error"];
		this._warning = results[0]["warning"];
		if (results[0]["status"] == this.SEARCHD_ERROR)
			return false;
		else
			return results[0];
	},

	/// helper to pack floats in network byte order
	_PackFloat : function(f){
		var t1 = packlib.pack(">f", [f]); // machine order
		var a = packlib.unpack(">L*", t1); // int in machine order
		var t2 = a[0];
		return packlib.pack(">L", [t2]);
	},

	/// add query to multi-query batch
	/// returns index into results array from RunQueries() call
	AddQuery : function (query, index, comment){
		index = default_val(index, "*");
		comment = default_val(comment, "");
				
		var req = [];
		// build request
		req.push(packlib.pack(">LLLL", [this._offset, this._limit, this._mode, this._ranker]));

		if (this._ranker == this.SPH_RANK_EXPR)
			req.push(packlib.pack(">L", [this._rankexpr.length]), new Buffer(this._rankexpr, "utf8"));
		
		req.push(packlib.pack(">L", [this._sort])); // (deprecated) sort mode

		req.push(packlib.pack(">L", [this._sortby.length]), new Buffer(this._sortby, "utf8"));

		req.push(packlib.pack(">L", [query.length]), new Buffer(query, "utf8")); // query itself

		req.push(packlib.pack(">L", [count(this._weights)])); // weights

		for(var i in this._weights)
			req.push(packlib.pack(">L", [parseInt(this._weights[i],10)]));

		req.push(packlib.pack(">L", [index.length]), new Buffer(index, "utf8")); // indexes

		req.push(packlib.pack(">L", [1])); // id64 range marker
		req.push(sph_packu64(this._min_id), sph_packu64(this._max_id)); // id64 range


		// filters
		req.push(packlib.pack(">L", [count(this._filters)] ));
		for (var i in this._filters){

			req.push(packlib.pack(">L", [this._filters[i]["attr"].length]), new Buffer(this._filters[i]["attr"], "utf8"));
			req.push(packlib.pack(">L", [this._filters[i]["type"]]));
			switch (this._filters[i]["type"]){
				case this.SPH_FILTER_VALUES:
					req.push(packlib.pack(">L", [count(this._filters[i]["values"])] ));
					for (var v in this._filters[i]["values"]){
						req.push(sph_packi64(this._filters[i]["values"][v]));
					}
					break;
				case this.SPH_FILTER_RANGE:
					req.push( sph_packi64(this._filters[i]["min"]), sph_packi64(this._filters[i]["max"]) );
					break;
				case this.SPH_FILTER_FLOATRANGE:
					req.push( this._PackFloat(this._filters[i]["min"]), this._PackFloat(this._filters[i]["max"]) );
					break;
				default:
					assert ( 0 && "internal error: unhandled filter type" );
			}
			req.push(packlib.pack(">L", [this._filters[i]["exclude"]]));
		}


		// group-by clause, max-matches count, group-sort clause, cutoff count
		req.push(packlib.pack(">LL", [this._groupfunc, this._groupby.length]), new Buffer(this._groupby, "utf8"));

		req.push(packlib.pack(">L", [this._maxmatches]));
		req.push(packlib.pack(">L", [this._groupsort.length]), new Buffer(this._groupsort, "utf8"));
		req.push(packlib.pack(">LLL", [this._cutoff, this._retrycount, this._retrydelay]));
		req.push(packlib.pack(">L", [this._groupdistinct.length]), new Buffer(this._groupdistinct, "utf8"));

		// anchor point
		if (0 == count(this._anchor)){
			req.push(packlib.pack(">L", [0]));
		} else {
			req.push(packlib.pack(">L", [1]));
			req.push(packlib.pack(">L", [this._anchor["attrlat"].length] ), new Buffer(this._anchor["attrlat"], "utf8"));
			req.push(packlib.pack(">L", [this._anchor["attrlong"].length] ), new Buffer(this._anchor["attrlong"], "utf8"));
			req.push(this._PackFloat(this._anchor["lat"]), this._PackFloat(this._anchor["long"]));
		}

		// per-index weights
		req.push(packlib.pack(">L", [count(this._indexweights)]));
		for (var idx in this._indexweights)
			req.push(packlib.pack(">L", [idx.length]), new Buffer(idx, "utf8"), packlib.pack(">L", this._indexweights[idx]));

		// max query time
		req.push(packlib.pack(">L", [this._maxquerytime]));

		// per-field weights
		req.push(packlib.pack(">L", [count(this._fieldweights)] ));
		for (var field in this._fieldweights)
			req.push(packlib.pack(">L", [field.length] ), new Buffer(field, "utf8"), packlib.pack(">L", this._fieldweights[field]));

		// comment
		req.push(packlib.pack(">L", [comment.length]), new Buffer(comment, "utf8"));

		// attribute overrides
		req.push(packlib.pack(">L", [count(this._overrides)] ));
		for (var key in this._overrides){
			req.push(packlib.pack(">L", [this._overrides[key]["attr"].length]), new Buffer(this._overrides[key]["attr"], "utf8"));
			req.push(packlib.pack(">LL", [this._overrides[key]["type"], count(this._overrides[key]["values"])] ));
			for(var id in this._overrides[key]["values"]){
				assert(is_numeric(id));
				assert(is_numeric(this._overrides[key]["values"][id]));

				req.push(sph_packu64(id));
				switch (this._overrides[key]["type"]){
					case this.SPH_ATTR_FLOAT:
						req.push(this._PackFloat(this._overrides[key]["values"][id]));
						break;
					case this.SPH_ATTR_BIGINT:
						req.push(sph_packi64(this._overrides[key]["values"][id]));
						break;
					default:
						req.push(packlib.pack(">L", [ this._overrides[key]["values"][id] ]));
						break;
				}
			}
		}

		// select-list
		req.push(packlib.pack(">L", [this._select.length]), new Buffer(this._select, "utf8"));

		// store request to requests array
		this._reqs.push(buf_join(req));
		return count(this._reqs)-1;
	},

	/// connect to searchd, run queries batch, and return an array of result sets
	RunQueries : function(){
		if (0 == count(this._reqs)){
			this._error = "no queries defined, issue AddQuery() first";
			return false;
		}

		var fp = this._Connect();
		if (!fp){
			return false;
		}

		// send query, get response
		var nreqs = count(this._reqs);		
		var len = 8+buf_len(this._reqs);
		this._reqs.unshift(packlib.pack(">HHLLL", [this.SEARCHD_COMMAND_SEARCH, this.VER_COMMAND_SEARCH, len, 0, nreqs])); // add header
				
		if (!this._Send(fp, buf_join(this._reqs), len + 8)){
			return false;
		}

		var response = this._GetResponse(fp, this.VER_COMMAND_SEARCH);
		if (!response){
			return false;
		}

		// query sent ok; we can reset reqs now
		this._reqs = [];

		// parse and return response
		return this._ParseSearchResponse(response, nreqs);
	},

	/// parse and return search query (or queries) response
	_ParseSearchResponse : function(response, nreqs){
		var a = [];
		var p = 0; // current position
		var max = response.length; // max position for checks, to protect against broken responses
		var results = [];
		for (var ires=0; ires<nreqs && p<max; ires++){
			results.push({});
			
			results[ires]["error"] = "";
			results[ires]["warning"] = "";
			var len = 0;

			// extract status
			a = packlib.unpack(">LLLL", response, p); 
			var status = a[0];
			p += 4;
			results[ires]["status"] = status;
			if (status != this.SEARCHD_OK){
				a = packlib.unpack(">LLLL", response, p); 
				len = parseInt(a[0], 10);
				p += 4;
				var message = response.slice(p, p + len).toString("utf8");
				p += len;

				if (status == this.SEARCHD_WARNING){
					results[ires]["warning"] = message;
				} else {
					results[ires]["error"] = message;
					continue;
				}
			}

			// read schema
			var fields = [];
			var attrs = {};
			var attrvals = {};
			var attr = "";

			a = packlib.unpack(">LLLL", response, p); 
			var nfields = parseInt(a[0], 10);
			p += 4;
			while (0 < nfields-- && p < max){
				a = packlib.unpack(">LLLL", response, p);
				len = parseInt(a[0],10);
				p += 4;
				fields.push(response.slice(p, p + len).toString("utf8")); 
				p += len;
			}
			results[ires]["fields"] = fields;

			a = packlib.unpack(">LLLL", response, p);
			var nattrs = parseInt(a[0], 10);
			p += 4;		
			while (0 < nattrs-- && p < max){
				a = packlib.unpack(">LLLL", response, p);
				len = parseInt(a[0], 10);
				p += 4;

				attr = response.slice(p, p + len).toString("utf8");
				p += len;
				a = packlib.unpack(">LLLL", response, p);
				p += 4;
				
				attrs[attr] = parseInt(a[0], 10);
			}
			results[ires]["attrs"] = attrs;

			// read match count
			a = packlib.unpack(">LLLL", response, p); 
			var cnt = parseInt(a[0], 10);
			p += 4;
			
			a = packlib.unpack(">LLLL", response, p);
			var id64 = a[0];
			p += 4;

			// read matches
			var weight = 0;
			var doc = 0;
			var idx = -1;
			while (0 < cnt-- && p < max){
				// index into result array
				idx++;
				// parse document id and weight
				if (id64){
					doc = sph_unpacku64(response.slice(p, p + 8), 0);
					p += 8;
					a = packlib.unpack(">LLLL", response.slice(p, p + 4), 0);
					weight = a[0];
					p += 4;
				}else{
					a = values(packlib.unpack(">LL", response.slice(p, p + 8), 0));
					doc = a[0];
					weight = a[1];
					p += 8;
					doc = sph_fixuint(doc);
				}
				weight = sprintlib.sprintf("%u", weight);
				if(!("matches" in results[ires]))
					results[ires]["matches"] = [];
				// create match entry
				if (this._arrayresult)
					results[ires]["matches"][idx] = {"id":doc, "weight":weight};
				else
					results[ires]["matches"][doc]["weight"] = weight;

				// parse and create attributes
				attrvals = {};
				for (attr in attrs){

					// handle 64bit ints
					if (attrs[attr] == this.SPH_ATTR_BIGINT){
						attrvals[attr] = sph_unpacki64(response.slice(p, p + 8), 0); 
						p += 8;
						continue;
					}

					// handle floats
					if (attrs[attr] == this.SPH_ATTR_FLOAT){
						a = packlib.unpack(">L", response.slice(p, p + 4), 0);
						var uval = a[0];
						p += 4;
						a = packlib.unpack(">f", packlib.pack(">L", [uval] ), 0); 
						var fval = a[0];
						attrvals[attr] = fval;
						continue;
					}

					// handle everything else as unsigned ints
					a = packlib.unpack(">L", response.slice(p, p + 4), 0); 
					p += 4;
					var val = a[0];
					if ( attrs[attr] == this.SPH_ATTR_MULTI){
						attrvals[attr] = [];
						nvalues = val;
						while (0 < nvalues-- && p < max){
							a = packlib.unpack(">L", response.slice(p, p + 4), 0); 
							val = a[0];
							p += 4;
							attrvals[attr].push(sph_fixuint(val));
						}
					} else if (attrs[attr] == this.SPH_ATTR_MULTI64){
						attrvals[attr] = [];
						var nvalues = val;
						while (0 < nvalues && p < max){
							attrvals[attr].push(sph_unpacku64(response.slice( p, p + 8), 0));
							p += 8;
							nvalues -= 2;
						}
					} else if (attrs[attr] == this.SPH_ATTR_STRING){
						attrvals[attr] = response.slice(p, p + val).toString("utf8");
						p += val;						
					} else{
						attrvals[attr] = sph_fixuint(val);
					}
				}

				if (this._arrayresult)
					results[ires]["matches"][idx]["attrs"] = attrvals;
				else
					results[ires]["matches"][doc]["attrs"] = attrvals;
			}

			var total, total_found, msecs, words;
			a = values(packlib.unpack(">LLLL", response.slice(p, p + 16)));
			total = a[0];
			total_found = a[1]; 
			msecs = parseInt(a[2], 10); 
			words = parseInt(a[3], 10);
			results[ires]["total"] = sprintlib.sprintf("%u", total);
			results[ires]["total_found"] = sprintlib.sprintf("%u", total_found);
			results[ires]["time"] = sprintlib.sprintf("%.3f", msecs/1000);
			p += 16;

			while (0 < words-- && p < max){
				a = packlib.unpack(">L", response.slice(p, p+4), 0);
				len = a[0];
				p += 4;
				word =  response.slice(p, p + len).toString("utf8");
				p += len;
				a = values(packlib.unpack(">LL", response.slice(p, p + 8, 0))); 
				var docs = a[0];
				var hits = a[1]; 
				p += 8;

				if(!("words" in results[ires]))
					results[ires]["words"] = {};

				results[ires]["words"][word] = {"docs":sprintlib.sprintf("%u", docs), "hits":sprintlib.sprintf("%u", hits)};
			}
		}

		return results;
	},

	/////////////////////////////////////////////////////////////////////////////
	// excerpts generation
	/////////////////////////////////////////////////////////////////////////////

	/// connect to searchd server, and generate exceprts (snippets)
	/// of given documents for given query. returns false on failure,
	/// an array of snippets on success
	BuildExcerpts : function(docs, index, words, opts){

		opts = default_val(opts, {});

		assert(is_array(docs));
		assert(is_string(index));
		assert(is_string(words));
		assert(is_array(opts));

		var fp = this._Connect();
		if (!fp){
			return false;
		}

		/////////////////
		// fixup options
		/////////////////

		if (!("before_match" in opts))
			opts["before_match"] = "<b>";
		if (!("after_match" in opts))
			opts["after_match"] = "</b>";
		if (!("chunk_separator" in opts))
			opts["chunk_separator"] = " ... ";
		if (!("limit" in opts))
			opts["limit"] = 256;
		if (!("limit_passages" in opts))
			opts["limit_passages"] = 0;
		if (!("limit_words" in opts))
			opts["limit_words"] = 0;
		if (!("around" in opts))
			opts["around"] = 5;
		if (!("exact_phrase" in opts))
			opts["exact_phrase"] = false;
		if (!("single_passage" in opts))
			opts["single_passage"] = false;
		if (!("use_boundaries" in opts))
			opts["use_boundaries"] = false;
		if (!("weight_order" in opts))
			opts["weight_order"] = false;
		if (!("query_mode" in opts))
			opts["query_mode"] = false;
		if (!("force_all_words" in opts))
			opts["force_all_words"] = false;
		if (!("start_passage_id" in opts))
			opts["start_passage_id"] = 1;
		if (!("load_files" in opts))
			opts["load_files"] = false;
		if (!("html_strip_mode" in opts))
			opts["html_strip_mode"] = "index";
		if (!("allow_empty" in opts))
			opts["allow_empty"] = false;
		if (!("passage_boundary" in opts))
			opts["passage_boundary"] = "none";
		if (!("emit_zones" in opts))
			opts["emit_zones"] = false;
		if (!("load_files_scattered" in opts))
			opts["load_files_scattered"] = false;
		
		/////////////////
		// build request
		/////////////////

		// v.1.2 req
		var flags = 1; // remove spaces
		if (opts["exact_phrase"])
			flags |= 2;
		if (opts["single_passage"])
			flags |= 4;
		if (opts["use_boundaries"])
			flags |= 8;
		if (opts["weight_order"])
			flags |= 16;
		if (opts["query_mode"])
			flags |= 32;
		if (opts["force_all_words"])
			flags |= 64;
		if (opts["load_files"])
			flags |= 128;
		if (opts["allow_empty"])
			flags |= 256;
		if (opts["emit_zones"])
			flags |= 512;
		if (opts["load_files_scattered"])
			flags |= 1024;
		
		var req = [];
		req.push(packlib.pack(">LL", [0, flags])); // mode=0, flags=flags
		req.push(packlib.pack(">L", index.length), new Buffer(index, "utf8")); // req index
		req.push(packlib.pack(">L", words.length), new Buffer(words, "utf8")); // req words

		// options
		req.push(packlib.pack(">L", [opts["before_match"].length]), new Buffer(opts["before_match"], "utf8"));
		req.push(packlib.pack(">L", [opts["after_match"].length]), new Buffer(opts["after_match"], "utf8"));
		req.push(packlib.pack(">L", [opts["chunk_separator"].length]), new Buffer(opts["chunk_separator"], "utf8"));
		req.push(packlib.pack(">LL", [parseInt(opts["limit"],10), parseInt(opts["around"],10)] ));
		req.push(packlib.pack(">LLL", [parseInt(opts["limit_passages"],10), parseInt(opts["limit_words"],10), parseInt(opts["start_passage_id"],10)] )); // v.1.2
		req.push(packlib.pack(">L", [opts["html_strip_mode"].length]), new Buffer(opts["html_strip_mode"], "utf8"));
		req.push(packlib.pack(">L", [opts["passage_boundary"].length]), new Buffer(opts["passage_boundary"], "utf8"));

		// documents
		req.push(packlib.pack(">L", count(docs)));
		for (var i in docs){
			assert(is_string(docs[i]));
			req.push(packlib.pack(">L", [docs[i].length]), new Buffer(docs[i], "utf8"));
		}

		////////////////////////////
		// send query, get response
		////////////////////////////

		var len = buf_len(req);
		req.unshift(packlib.pack(">HHL", [this.SEARCHD_COMMAND_EXCERPT, this.VER_COMMAND_EXCERPT, len])); // add header
		if (!(this._Send(fp, buf_join(req), len + 8))){
			return false;
		}

		var response = this._GetResponse(fp, this.VER_COMMAND_EXCERPT);
		if(!response){
			return false;
		}

		//////////////////
		// parse response
		//////////////////

		var a = [];
		var pos = 0;
		var res = [];
		var rlen = response.length;
		for (var i=0; i<count(docs); i++){
			a = packlib.unpack(">L", response.slice(pos, pos + 4));
			len = parseInt(a[0], 10);
			pos += 4;

			if (rlen < pos + len){
				this._error = "incomplete reply";
				return false;
			}
			res.push(len ? response.slice(pos, pos + len) : "");
			pos += len;
		}

		return res;
	},


	/////////////////////////////////////////////////////////////////////////////
	// keyword generation
	/////////////////////////////////////////////////////////////////////////////

	/// connect to searchd server, and generate keyword list for a given query
	/// returns false on failure,
	/// an array of words on success
	BuildKeywords : function(query, index, hits){
		assert(is_string(query));
		assert(is_string(index));
		assert(is_bool(hits));

		var fp = this._Connect();
		if (!fp){
			return false;
		}

		/////////////////
		// build request
		/////////////////

		// v.1.0 req
		var req = [];
		req.push(packlib.pack(">L", [query.length]), new Buffer(query, "utf8")); // req query
		req.push(packlib.pack(">L", [index.length]), new Buffer(index, "utf8")); // req index
		req.push(packlib.pack(">L", [parseInt(hits, 10)]));

		////////////////////////////
		// send query, get response
		////////////////////////////

		var len = buf_len(req);
		req.unshift(packlib.pack(">HLL", [this.SEARCHD_COMMAND_KEYWORDS, this.VER_COMMAND_KEYWORDS, len])); // add header
		if (!this._Send (fp, buf_join(req), len + 8)){
			return false;
		}

		var response = this._GetResponse(fp, this.VER_COMMAND_KEYWORDS);
		if(!response){
			return false;
		}

		//////////////////
		// parse response
		//////////////////

		var pos = 0;
		var res = [];
		var rlen = response.length;
		var a = packlib.unpack(">L", response.slice(pos, pos + 4), 0);
		var nwords = parseInt(a[0], 10);
		pos += 4;
		for (var i=0; i<nwords; i++){
			a = packlib.unpack(">L", response.slice(pos, pos + 4), 0);
			len = parseInt(a[0], 10);
			pos += 4;

			tokenized = len ? response.slice(pos, pos + len).toString("utf8") : "";
			pos += len;

			a = packlib.unpack(">L", response.slice(pos, pos + 4), 0);
			len = parseInt(a[0], 10);
			pos += 4;
			
			normalized = len ? response.slice(pos, pos + len).toString("utf8") : "";
			pos += len;

			res.push( {"tokenized":tokenized, "normalized":normalized} );

			if (hits){
				a = values(packlib.unpack(">LL", response.slice(pos, pos + 8)));
				pos += 8;
				res[i]["docs"] = a[0];
				res[i]["hits"] = a[1];
			}

			if (pos > rlen){
				this._error = "incomplete reply";
				return false;
			}
		}

		return res;
	},

	EscapeString : function(str){
		var from = [ '\\', '(',')','|','-','!','@','~','"','&', '/', '^', '$', '=' ];
		var to   = [ '\\\\', '\(','\)','\|','\-','\!','\@','\~','\"', '\&', '\/', '\^', '\$', '\=' ];
		for(var i in from){
			str = str.replace(from[i], to[i]);
		}
		return str;
	},

	/////////////////////////////////////////////////////////////////////////////
	// attribute updates
	/////////////////////////////////////////////////////////////////////////////

	/// batch update given attributes in given rows in given indexes
	/// returns amount of updated documents (0 or more) on success, or -1 on failure
	UpdateAttributes : function(index, attrs, values, mva){

		mva = default_val(mva, false);

		// verify everything
		assert(is_string(index));
		assert(is_bool(mva));
		assert(is_array(attrs));
		for (var i in attrs)
			assert(is_string(attrs[i]));

		assert(is_array(values));
		for (var id in values ){
			assert(is_numeric(id));
			assert(is_array(values[id]));
			assert(count(values[id]) == count(attrs));
			for (var i in values[id]){
				if (mva){
					assert(is_array(values[id][i]));
					for (var ii in values[id][i])
						assert(is_int(values[id][i][ii]));
				} else{
					assert(is_int(values[id][i]));
				}
			}
		}

		// build request
		var req = [];
		req.push(packlib.pack(">L", [index.length]), new Buffer(index, "utf8"));

		req.push(packlib.pack(">L", [count(attrs)] ));
		for (var i in attrs){
			req.push(packlib.pack(">L", [attrs[i].length]), new Buffer(attr[i], "utf8"));
			req.push(packlib.pack(">L", [mva ? 1 : 0]));
		}

		req.push(packlib.pack(">L", [count(values)] ));
		for (var id in values){
			req.push(sph_packu64(id));
			for (var v in values[id]){
				req.push(packlib.pack(">L", [ mva ? count(values[id][v]) : values[id][v] ] ));
				if (mva){
					for (var vv in values[id][v])
						req.push(packlib.pack(">L", [ values[id][v][vv] ] ));
				}
			}
		}

		var fp = this._Connect();
		// connect, send query, get response
		if (!fp){
			return -1;
		}

		var len = buf_len(req);
		req.unshift(packlib.pack(">HLL", [this.SEARCHD_COMMAND_UPDATE, this.VER_COMMAND_UPDATE, len])); // add header
		if (!this._Send(fp, buf_join(req), len + 8)){
			return -1;
		}

		var response = this._GetResponse(fp, this.VER_COMMAND_UPDATE);
		if (!response){
			return -1;
		}

		// parse response
		a = packlib.unpack(">L", response.slice(0, 4), 0);
		return a[0];
	},

	/////////////////////////////////////////////////////////////////////////////
	// persistent connections
	/////////////////////////////////////////////////////////////////////////////

	Open : function(){
		if (false !== this._socket){
			this._error = "already connected";
			return false;
		}

		var fp = this._Connect();
		if (!fp){
			return false;
		}

		// command, command version = 0, body length = 4, body = 1
		var req = packlib.pack(">HHLL", [this.SEARCHD_COMMAND_PERSIST, 0, 4, 1]);
		if (!this._Send(fp, req, 12)){
			return false;
		}

		this._socket = fp;
		return true;
	},

	Close : function(){
		if (false === this._socket){
			this._error = "not connected";
			return false;
		}

		this._socket.close();
		this._socket = false;

		return true;
	},

	//////////////////////////////////////////////////////////////////////////
	// status
	//////////////////////////////////////////////////////////////////////////

	Status : function(){
		var fp = this._Connect();
		if (!fp){
			return false;
		}

		var req = packlib.pack(">HHLL", [this.SEARCHD_COMMAND_STATUS, this.VER_COMMAND_STATUS, 4, 1]); // len=4, body=1
		if (!(this._Send(fp, req, 12))){
			return false;
		}

		var response = this._GetResponse(fp, this.VER_COMMAND_STATUS);
		if(!response){
			return false;
		}		

		var len = 0;
		//var res = response.substr( 4 ); // just ignore length, error handling, etc
		var p = 0;
		var a = values(packlib.unpack(">LL", response.slice(p, p + 8)), 0);
		p += 8;
		
		var rows = parseInt(a[0], 10);
		var cols = parseInt(a[1], 10);
		var val = "";
		var tr = [];
		var res = {};
		for (var i=0; i<rows; i++){
			for ( var j=0; j<cols; j++ ){
				a = packlib.unpack(">L", response.slice(p, p+4), 0); 
				len = parseInt(a[0], 10);
				p += 4;
				val = response.slice(p, p + len).toString('utf8');//values(packlib.unpack("S>", response.slice(p, p + len), 0))[0];
				if("undefined" == typeof tr[i])
					tr[i] = val;
				else	
					res[tr[i]] = val;
			
				p += len;
			}
		}

		return res;
	},

	//////////////////////////////////////////////////////////////////////////
	// flush
	//////////////////////////////////////////////////////////////////////////

	FlushAttributes : function(){
		var fp = this._Connect();
		if (!fp){
			return -1;
		}

		var req = packlib.pack(">hhI", [this.SEARCHD_COMMAND_FLUSHATTRS, this.VER_COMMAND_FLUSHATTRS, 0]); // len=0
		if (!(this._Send(fp, req, 8))){
			return -1;
		}

		var response = this._GetResponse(fp, this.VER_COMMAND_FLUSHATTRS);
		if(!response){
			return -1;
		}		
		
		var a = [-1, -1];
		if (4 == response.length){
			a = packlib.unpack(">L*", response);
		}else{
			this._error = "unexpected response length";
		}
		return a[1];
	},
};

