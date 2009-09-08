// Util.js

Util = {
	/**
	 * creates a random string (numbers and chars)
	 * @param len length of key
	 * @param mode determines which letters to use. null or 0 = all letters;
	 *      1 = skip 0, 1, l and o which can easily be mixed with numbers;
	 *      2 = use numbers only
	 * @returns random string
	 */
	randomString: function(len, mode) {
		if (mode == 2) {
			var x = Math.random() * Math.pow(10,len);
			return Math.floor(x);
		}
		var keystr = '';
		for (var i=0; i<len; i++) {
			var x = Math.floor((Math.random() * 36));
			if (mode == 1) {
				// skip 0,1
				x = (x<2) ? x + 2 : x;
				// don't use the letters l (charCode 21+87) and o (24+87)
				x = (x==21) ? 22 : x;
				x = (x==24) ? 25 : x;
			}
			if (x<10) {
				keystr += String(x);
			}    else    {
				keystr += String.fromCharCode(x+87);
			}
		}
		return keystr;
	},

	mergeObjects:  function(dst, src) {
		for (var key in src) {
			dst[key] = src[key];
		}
	},

	inet_ntoa:  function(ip) {
		ip = parseInt(ip);
		var quads = [];
		for (var i = 0; i < 4; i++) {
			quads.push(ip % 256);
			ip >>= 8;
		}
		return quads[3] + '.' + quads[2] + '.' + quads[1] + '.' + quads[0];
	},

	inet_aton:  function(ip) {
		console.log('inet_aton('+ip+')');
		var quads = ip.split('.');
		//console.log(ip);
		//console.dir(quads);
		return (parseInt(quads[0]) << 24) | (parseInt(quads[1]) << 16) | (parseInt(quads[2]) << 8) | parseInt(quads[3]);
	},

	currentTime:  function() {
		var date = new Date();
		return parseInt(date.getTime() / 1000);
	},

	currentTimeMillis:  function() {
		var date = new Date();
		return date.getTime();
	},

	dateOnlyString:  function(timestamp) {
		timestamp = parseInt(timestamp);
		var date = new Date(timestamp * 1000);
		var now = Util.currentTime();
		var today = now - (now % 86400);
		var tomorrow = today + 86400;
		var dayafter = tomorrow + 86400;
		var yesterday = today - 86400;
		if (timestamp >= tomorrow && timestamp <= dayafter) {
			return "Tomorrow";
		}
		if (timestamp >= today && timestamp <= tomorrow) {
			return "Today";
		}
		if (timestamp >= yesterday && timestamp <= today) {
			return "Yesterday";
		}
		return date.format('MM/dd/yyyy');
		//	var f = date.getMonth();
		//	f = date.getDate();
		//	f = date.getFullYear();
		//	return (date.getMonth() + 1).format('##') + '/' + date.getDate().format('##') + '/' + date.getFullYear();
	},

	timeOnlyString:  function(timestamp) {
		timestamp = parseInt(timestamp);
		var date = new Date(timestamp * 1000);
		return date.format('hh:mm:ss a');
		//	var hour = date.getHours();
		//	var ampm = 'AM';
		//	if (hour > 11) {
		//		ampm = 'PM';
		//		if (hour > 12) {
		//			hour -= 12;
		//		}
		//	}
		//	hour = hour.format('##');
		//	var minutes = date.getMinutes().format('##');
		//	var seconds = date.getSeconds().format('##');
		//	return hour +':' + minutes + ':' + seconds + ' ' + ampm;
	},

	dateString:  function(timestamp) {
		timestamp = parseInt(timestamp);
		var now = Util.currentTime();
		var today = now - (now % 86400);
		var yesterday = today - 86400;
		var date = new Date(timestamp * 1000);
		if (timestamp >= today) {
			return "Today " + date.format('hh:mm:ss a');
		}
		if (timestamp >= yesterday) {
			return "Yesterday " + date.format('hh:mm:ss a');
		}
		return date.format('MM/dd/yyyy hh:mm:ss a');
		//	var hour = date.getHours();
		//	var ampm = 'AM';
		//	if (hour > 11) {
		//		ampm = 'PM';
		//		if (hour > 12) {
		//			hour -= 12;
		//		}
		//	}
		//	hour = hour.format('##');
		//	var minutes = date.getMinutes().format('##');
		//	return (date.getMonth()+1).format('##') + '/' + date.getDate().format('##') + '/' + date.getFullYear() + ' ' + hour + ':' + minutes + ' ' + ampm;
	},

	dateStringLocale:  function(timestamp) {
		return new Date(timestamp * 1000).toLocaleString();
	},

	/*
	//returns utf8 encoded charachter of a unicode value.
	//code must be a number indicating the Unicode value.
	//returned value is a string between 1 and 4 charachters.
	ode2ut:fcode) {
		if (code < 128) return chr(code);
		if (code < 2048) return chr(192 + (code >> 6)) + chr(128 + (code & 63));
		if (code < 65536) return chr(224 + (code >> 12)) + chr(128 + ((code >> 6) & 63)) + chr(128 + (code & 63));
		if (code < 2097152) return chr(240 + (code >> 18)) + chr(128 + ((code >> 12) & 63)) + chr(128 + ((code >> 6) & 63)) + chr(128 + (code & 63));
	}

	//it is a private function for internal use in utf8Encode function 
	//Encodes a unicode string to UTF8 format.
	encodeUTF8:  function(str) {
		function _utf8Encode(str) {
			var utf8str = new Array();
			for (var i = 0; i < str.length; i++) {
				utf8str[i] = code2utf(str.charCodeAt(i));
			}
			return utf8str.join('');
		}

		var utf8str = new Array();
		var pos, j = 0;
		var tmpStr = '';

		while ((pos = str.search(/[^\x00-\x7F]/)) != -1) {
			tmpStr = str.match(/([^\x00-\x7F]+[\x00-\x7F]{0,10})+/)[0];
			utf8str[j++] = str.substr(0, pos);
			utf8str[j++] = _utf8Encode(tmpStr);
			str = str.substr(pos + tmpStr.length);
		}

		utf8str[j++] = str;
		return utf8str.join('');
	}
	*/

	//it is a private function for internal use in utf8Decode function 
	//Decodes a UTF8 formated string
	decodeUTF8:  function(utf8str) {
		//an alias of String.fromCharCode
		function chr(code) {
			return String.fromCharCode(code);
		}
		function _utf8Decode(utf8str) {
			var str = new Array();
			var code, code2, code3, code4, j = 0;
			for (var i = 0; i < utf8str.length;) {
				code = utf8str.charCodeAt(i++);
				if (code > 127) code2 = utf8str.charCodeAt(i++);
				if (code > 223) code3 = utf8str.charCodeAt(i++);
				if (code > 239) code4 = utf8str.charCodeAt(i++);

				if (code < 128) str[j++] = chr(code);
				else if (code < 224) str[j++] = chr(((code - 192) << 6) + (code2 - 128));
				else if (code < 240) str[j++] = chr(((code - 224) << 12) + ((code2 - 128) << 6) + (code3 - 128));
				else str[j++] = chr(((code - 240) << 18) + ((code2 - 128) << 12) + ((code3 - 128) << 6) + (code4 - 128));
			}
			return str.join('');
		}

		var str = new Array();
		var pos = 0;
		var tmpStr = '';
		var j = 0;
		while ((pos = utf8str.search(/[^\x00-\x7F]/)) != -1) {
			tmpStr = utf8str.match(/([^\x00-\x7F]+[\x00-\x7F]{0,10})+/)[0];
			str[j++] = utf8str.substr(0, pos) + _utf8Decode(tmpStr);
			utf8str = utf8str.substr(pos + tmpStr.length);
		}

		str[j++] = utf8str;
		return str.join('');
	},

	/*
	Util.encodeUTF8 = function(s) {
		for (var c, i = -1,
		l = (s = s.split("")).length, o = String.fromCharCode; ++i < l;
		s[i] = (c = s[i].charCodeAt(0)) >= 127 ? o(0xc0 | (c >>> 6)) + o(0x80 | (c & 0x3f)) : s[i]);
		return s.join("");
	}
	Util.decodeUTF8 = function(s) {
		for (var a, b, i = -1,
		l = (s = s.split("")).length, o = String.fromCharCode, c = "charCodeAt"; ++i < l; ((a = s[i][c](0)) & 0x80) && (s[i] = (a & 0xfc) == 0xc0 && ((b = s[i + 1][c](0)) & 0xc0) == 0x80 ? o(((a & 0x03) << 6) + (b & 0x3f)) : o(128), s[++i] = ""));
		return s.join("");
	}
	*/


	encodeUTF8:  function(string) {
		string = string.replace(/rn/g, "\n");
		var utftext = "";

		for (var n = 0; n < string.length; n++) {
			var c = string.charCodeAt(n);
			if (c < 128) {
				utftext += String.fromCharCode(c);
			}
			else if ((c > 127) && (c < 2048)) {
				utftext += String.fromCharCode((c >> 6) | 192);
				utftext += String.fromCharCode((c & 63) | 128);
			}
			else {
				utftext += String.fromCharCode((c >> 12) | 224);
				utftext += String.fromCharCode(((c >> 6) & 63) | 128);
				utftext += String.fromCharCode((c & 63) | 128);
			}
		}
		return utftext;
	},

	/*
	decodeUTF8:  function(utftext) {
		var string = "";
		if (utftext) {
		var i = 0;
		var c = c1 = c2 = 0;

		while (i < utftext.length) {
			c = utftext.charCodeAt(i);
			if (c < 128) {
				string += String.fromCharCode(c);
				i++;
			}
			else if ((c > 191) && (c < 224)) {
				c2 = utftext.charCodeAt(i + 1);
				string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
				i += 2;
			}
			else {
				c2 = utftext.charCodeAt(i + 1);
				c3 = utftext.charCodeAt(i + 2);
				string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
				i += 3;
			}
		}
		}
		return string;
	}
	*/

	/*
	decodeUTF8:  function(s) {
		var buffer = new java.lang.String((new java.lang.String(s)).getBytes("ISO-8859-1"), "UTF-8");
	//	var buffer = new java.lang.String((new java.lang.String(s)).getBytes("UTF-8"), "Latin1");
		return String(buffer);
		return s;
		var buffer = new java.lang.String(s);
		return s;
	//	return buffer;
		return new java.lang.String(buffer.getBytes("UTF-8"));
	}
	*/

	// http://sportstwo.com/forums/images/buttons/Generic/viewpost.gif 
	parseBBCode:  function(text) {
		text = text.replace(/\</igm, '&lt;');
		text = text.replace(/\r/gm, '');
		text = text.replace(/\n/gm, '<br/>');
		var search = new Array(
			/\[img\](.*?)\[\/img\]/igm, 
			/\[url="*([\w]+?:\/\/[^ \\"\n\r\t<]*?)"*\](.*?)\[\/url\]/igm, 
			/\[url\]((www|ftp|)\.[^ \\"\n\r\t<]*?)\[\/url\]/igm, 
			/\[url=((www|ftp|)\.[^ \\"\n\r\t<]*?)\](.*?)\[\/url\]/igm, 
			/\[email\](([a-z0-9&\-_.]+?)@([\w\-]+\.([\w\-\.]+\.)?[\w]+))\[\/email\]/igm, 
			/\[b\](.*?)\[\/b\]/igm, 
			/\[i\](.*?)\[\/i\]/igm, 
			/\[center\](.*?)\[\/center\]/igm, 
			/\[url\](http:\/\/[^ \\"\n\r\t<]*?)\[\/url\]/igm, 
			/\[quote\](.*?)\[\/quote\]/igm,
			/\[quote=(.*?);(.*?)\](.*?)\[\/quote\]/igm,
			/\[quote=(.*?)\](.*?)\[\/quote\]/igm
		);

		var replace = new Array(
			"<img src=\"$1\" alt=\"An image\">", 
			"<a href=\"$1\" target=\"blank\">$2</a>", 
			"<a href=\"http://$1\" target=\"blank\">$1</a>", 
			"<a href=\"$1\" target=\"blank\">$1</a>", 
			"<a href=\"mailto:$1\">$1</a>", 
			"<b>$1</b>", 
			"<i>$1</i>", 
			"<center>$1</center>", 
			"<a href=\"$1\" target=\"blank\">$1</a>", 
			'<div class="quote">$1</div>',
			'<div class="quote"><b>$1 <a href="/forums/Post/$2">wrote</a>:</b><br/>$3</div>',
			'<div class="quote"><b>$1 wrote:</b><br/>$2</div>'
		);

		for (var x = 0; x < 5; x++) {
			for (var i = 0; i < search.length; i++) {
				text = text.replace(search[i], replace[i]);
			}
		}
		return text;
	},

	stripslashes:  function(str) {
		return (str + '').replace(/\0/g, '0').replace(/\\([\\'"])/g, '$1');
	},

	addslashes:  function(str) {
		return (str + '').replace(/([\\"'])/g, "\\$1").replace(/\0/g, "\\0");
	},
	
	md5: function (string) {
	 
		function RotateLeft(lValue, iShiftBits) {
			return (lValue<<iShiftBits) | (lValue>>>(32-iShiftBits));
		}
	 
		function AddUnsigned(lX,lY) {
			var lX4,lY4,lX8,lY8,lResult;
			lX8 = (lX & 0x80000000);
			lY8 = (lY & 0x80000000);
			lX4 = (lX & 0x40000000);
			lY4 = (lY & 0x40000000);
			lResult = (lX & 0x3FFFFFFF)+(lY & 0x3FFFFFFF);
			if (lX4 & lY4) {
				return (lResult ^ 0x80000000 ^ lX8 ^ lY8);
			}
			if (lX4 | lY4) {
				if (lResult & 0x40000000) {
					return (lResult ^ 0xC0000000 ^ lX8 ^ lY8);
				} else {
					return (lResult ^ 0x40000000 ^ lX8 ^ lY8);
				}
			} else {
				return (lResult ^ lX8 ^ lY8);
			}
		}
	 
		function F(x,y,z) { return (x & y) | ((~x) & z); }
		function G(x,y,z) { return (x & z) | (y & (~z)); }
		function H(x,y,z) { return (x ^ y ^ z); }
		function I(x,y,z) { return (y ^ (x | (~z))); }
	 
		function FF(a,b,c,d,x,s,ac) {
			a = AddUnsigned(a, AddUnsigned(AddUnsigned(F(b, c, d), x), ac));
			return AddUnsigned(RotateLeft(a, s), b);
		};
	 
		function GG(a,b,c,d,x,s,ac) {
			a = AddUnsigned(a, AddUnsigned(AddUnsigned(G(b, c, d), x), ac));
			return AddUnsigned(RotateLeft(a, s), b);
		};
	 
		function HH(a,b,c,d,x,s,ac) {
			a = AddUnsigned(a, AddUnsigned(AddUnsigned(H(b, c, d), x), ac));
			return AddUnsigned(RotateLeft(a, s), b);
		};
	 
		function II(a,b,c,d,x,s,ac) {
			a = AddUnsigned(a, AddUnsigned(AddUnsigned(I(b, c, d), x), ac));
			return AddUnsigned(RotateLeft(a, s), b);
		};
	 
		function ConvertToWordArray(string) {
			var lWordCount;
			var lMessageLength = string.length;
			var lNumberOfWords_temp1=lMessageLength + 8;
			var lNumberOfWords_temp2=(lNumberOfWords_temp1-(lNumberOfWords_temp1 % 64))/64;
			var lNumberOfWords = (lNumberOfWords_temp2+1)*16;
			var lWordArray=Array(lNumberOfWords-1);
			var lBytePosition = 0;
			var lByteCount = 0;
			while ( lByteCount < lMessageLength ) {
				lWordCount = (lByteCount-(lByteCount % 4))/4;
				lBytePosition = (lByteCount % 4)*8;
				lWordArray[lWordCount] = (lWordArray[lWordCount] | (string.charCodeAt(lByteCount)<<lBytePosition));
				lByteCount++;
			}
			lWordCount = (lByteCount-(lByteCount % 4))/4;
			lBytePosition = (lByteCount % 4)*8;
			lWordArray[lWordCount] = lWordArray[lWordCount] | (0x80<<lBytePosition);
			lWordArray[lNumberOfWords-2] = lMessageLength<<3;
			lWordArray[lNumberOfWords-1] = lMessageLength>>>29;
			return lWordArray;
		};
	 
		function WordToHex(lValue) {
			var WordToHexValue="",WordToHexValue_temp="",lByte,lCount;
			for (lCount = 0;lCount<=3;lCount++) {
				lByte = (lValue>>>(lCount*8)) & 255;
				WordToHexValue_temp = "0" + lByte.toString(16);
				WordToHexValue = WordToHexValue + WordToHexValue_temp.substr(WordToHexValue_temp.length-2,2);
			}
			return WordToHexValue;
		};
	 
		function Utf8Encode(string) {
			string = string.replace(/\r\n/g,"\n");
			var utftext = "";
	 
			for (var n = 0; n < string.length; n++) {
	 
				var c = string.charCodeAt(n);
	 
				if (c < 128) {
					utftext += String.fromCharCode(c);
				}
				else if((c > 127) && (c < 2048)) {
					utftext += String.fromCharCode((c >> 6) | 192);
					utftext += String.fromCharCode((c & 63) | 128);
				}
				else {
					utftext += String.fromCharCode((c >> 12) | 224);
					utftext += String.fromCharCode(((c >> 6) & 63) | 128);
					utftext += String.fromCharCode((c & 63) | 128);
				}
	 
			}
	 
			return utftext;
		};
	 
		var x=Array();
		var k,AA,BB,CC,DD,a,b,c,d;
		var S11=7, S12=12, S13=17, S14=22;
		var S21=5, S22=9 , S23=14, S24=20;
		var S31=4, S32=11, S33=16, S34=23;
		var S41=6, S42=10, S43=15, S44=21;
	 
		string = Utf8Encode(string);
	 
		x = ConvertToWordArray(string);
	 
		a = 0x67452301; b = 0xEFCDAB89; c = 0x98BADCFE; d = 0x10325476;
	 
		for (k=0;k<x.length;k+=16) {
			AA=a; BB=b; CC=c; DD=d;
			a=FF(a,b,c,d,x[k+0], S11,0xD76AA478);
			d=FF(d,a,b,c,x[k+1], S12,0xE8C7B756);
			c=FF(c,d,a,b,x[k+2], S13,0x242070DB);
			b=FF(b,c,d,a,x[k+3], S14,0xC1BDCEEE);
			a=FF(a,b,c,d,x[k+4], S11,0xF57C0FAF);
			d=FF(d,a,b,c,x[k+5], S12,0x4787C62A);
			c=FF(c,d,a,b,x[k+6], S13,0xA8304613);
			b=FF(b,c,d,a,x[k+7], S14,0xFD469501);
			a=FF(a,b,c,d,x[k+8], S11,0x698098D8);
			d=FF(d,a,b,c,x[k+9], S12,0x8B44F7AF);
			c=FF(c,d,a,b,x[k+10],S13,0xFFFF5BB1);
			b=FF(b,c,d,a,x[k+11],S14,0x895CD7BE);
			a=FF(a,b,c,d,x[k+12],S11,0x6B901122);
			d=FF(d,a,b,c,x[k+13],S12,0xFD987193);
			c=FF(c,d,a,b,x[k+14],S13,0xA679438E);
			b=FF(b,c,d,a,x[k+15],S14,0x49B40821);
			a=GG(a,b,c,d,x[k+1], S21,0xF61E2562);
			d=GG(d,a,b,c,x[k+6], S22,0xC040B340);
			c=GG(c,d,a,b,x[k+11],S23,0x265E5A51);
			b=GG(b,c,d,a,x[k+0], S24,0xE9B6C7AA);
			a=GG(a,b,c,d,x[k+5], S21,0xD62F105D);
			d=GG(d,a,b,c,x[k+10],S22,0x2441453);
			c=GG(c,d,a,b,x[k+15],S23,0xD8A1E681);
			b=GG(b,c,d,a,x[k+4], S24,0xE7D3FBC8);
			a=GG(a,b,c,d,x[k+9], S21,0x21E1CDE6);
			d=GG(d,a,b,c,x[k+14],S22,0xC33707D6);
			c=GG(c,d,a,b,x[k+3], S23,0xF4D50D87);
			b=GG(b,c,d,a,x[k+8], S24,0x455A14ED);
			a=GG(a,b,c,d,x[k+13],S21,0xA9E3E905);
			d=GG(d,a,b,c,x[k+2], S22,0xFCEFA3F8);
			c=GG(c,d,a,b,x[k+7], S23,0x676F02D9);
			b=GG(b,c,d,a,x[k+12],S24,0x8D2A4C8A);
			a=HH(a,b,c,d,x[k+5], S31,0xFFFA3942);
			d=HH(d,a,b,c,x[k+8], S32,0x8771F681);
			c=HH(c,d,a,b,x[k+11],S33,0x6D9D6122);
			b=HH(b,c,d,a,x[k+14],S34,0xFDE5380C);
			a=HH(a,b,c,d,x[k+1], S31,0xA4BEEA44);
			d=HH(d,a,b,c,x[k+4], S32,0x4BDECFA9);
			c=HH(c,d,a,b,x[k+7], S33,0xF6BB4B60);
			b=HH(b,c,d,a,x[k+10],S34,0xBEBFBC70);
			a=HH(a,b,c,d,x[k+13],S31,0x289B7EC6);
			d=HH(d,a,b,c,x[k+0], S32,0xEAA127FA);
			c=HH(c,d,a,b,x[k+3], S33,0xD4EF3085);
			b=HH(b,c,d,a,x[k+6], S34,0x4881D05);
			a=HH(a,b,c,d,x[k+9], S31,0xD9D4D039);
			d=HH(d,a,b,c,x[k+12],S32,0xE6DB99E5);
			c=HH(c,d,a,b,x[k+15],S33,0x1FA27CF8);
			b=HH(b,c,d,a,x[k+2], S34,0xC4AC5665);
			a=II(a,b,c,d,x[k+0], S41,0xF4292244);
			d=II(d,a,b,c,x[k+7], S42,0x432AFF97);
			c=II(c,d,a,b,x[k+14],S43,0xAB9423A7);
			b=II(b,c,d,a,x[k+5], S44,0xFC93A039);
			a=II(a,b,c,d,x[k+12],S41,0x655B59C3);
			d=II(d,a,b,c,x[k+3], S42,0x8F0CCC92);
			c=II(c,d,a,b,x[k+10],S43,0xFFEFF47D);
			b=II(b,c,d,a,x[k+1], S44,0x85845DD1);
			a=II(a,b,c,d,x[k+8], S41,0x6FA87E4F);
			d=II(d,a,b,c,x[k+15],S42,0xFE2CE6E0);
			c=II(c,d,a,b,x[k+6], S43,0xA3014314);
			b=II(b,c,d,a,x[k+13],S44,0x4E0811A1);
			a=II(a,b,c,d,x[k+4], S41,0xF7537E82);
			d=II(d,a,b,c,x[k+11],S42,0xBD3AF235);
			c=II(c,d,a,b,x[k+2], S43,0x2AD7D2BB);
			b=II(b,c,d,a,x[k+9], S44,0xEB86D391);
			a=AddUnsigned(a,AA);
			b=AddUnsigned(b,BB);
			c=AddUnsigned(c,CC);
			d=AddUnsigned(d,DD);
		}
	 
		var temp = WordToHex(a)+WordToHex(b)+WordToHex(c)+WordToHex(d);
	 
		return temp.toLowerCase();
	},
	/**
	 * Concatenates the values of a variable into an easily readable string
	 * by Matt Hackett [scriptnode.com]
	 * @param {Object} x The variable to debug
	 * @param {Number} max The maximum number of recursions allowed (keep low, around 5 for HTML elements to prevent errors) [default: 10]
	 * @param {String} sep The separator to use between [default: a single space ' ']
	 * @param {Number} l The current level deep (amount of recursion). Do not use this parameter: it's for the function's own use
	 */
	print_r: function(x, max, sep, l) {
	
		l = l || 0;
		max = max || 4;
		sep = sep || ' ';
	
		if (l > max) {
			return "[WARNING: Too much recursion]\n";
		}
	
		var
			i,
			r = '',
			t = typeof x,
			tab = '';
	
	//	r += t + '\n';
		if (x === null) {
			r += "(null)\n";
		} else if (t === 'function') {
			r += '(function)\n';
			x = 'function';
		} else if (t === 'object') {
	
			l++;
	
			for (i = 0; i < l; i++) {
				tab += sep;
			}
	
			if (x && x.length) {
				t = 'array';
			}
	
			r += '(' + t + ") :\n";
	
			for (i in x) {
				if (i === 'class') continue;
				try {
					r += tab + '[' + i + '] : ' + Util.print_r(x[i], max, sep, (l + 1));
				} catch(e) {
					return "[ERROR: " + e + "]\n";
				}
			}
	
		} else {
	
			if (t == 'string') {
				if (x == '') {
					x = '(empty)';
				}
			}
	
			r += '(' + t + ') ' + x + "\n";
	
		}
	
		return r;
	
	}
};

exports.Util = Util;
exports.now = Util.currentTime();
