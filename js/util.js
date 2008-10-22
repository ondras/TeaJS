var Util = {
    md5:function(str) {
    },
    sha1:function(str) {
    },
    base64encode:function(str) {
		var keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
		var output = "";
		var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
		var i = 0;

		do {
			chr1 = input.charCodeAt(i++);
			chr2 = input.charCodeAt(i++);
			chr3 = input.charCodeAt(i++);

			enc1 = chr1 >> 2;
			enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
			enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
			enc4 = chr3 & 63;

			if (isNaN(chr2)) { 
				enc3 = enc4 = 64;
			} else if (isNaN(chr3)) {
				enc4 = 64;
			}

			output = output + keyStr.charAt(enc1) + keyStr.charAt(enc2) + keyStr.charAt(enc3) + keyStr.charAt(enc4);
		} while (i < input.length);
		return output;
	},
    base64decode:function(str) {
		var keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
		var output = "";
		var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
		var i = 0;

		do {
			enc1 = keyStr.indexOf(input.charAt(i++));
			enc2 = keyStr.indexOf(input.charAt(i++));
			enc3 = keyStr.indexOf(input.charAt(i++));
			enc4 = keyStr.indexOf(input.charAt(i++));

			chr1 = (enc1 << 2) | (enc2 >> 4);
			chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
			chr3 = ((enc3 & 3) << 6) | enc4;

			output = output + String.fromCharCode(chr1);

			if (enc3 != 64) { output = output + String.fromCharCode(chr2); }
			if (enc4 != 64) { output = output + String.fromCharCode(chr3); }
		} while (i < input.length);

		return output;    
	},
    serialize:function(obj) {
		function sanitize(str) {
		    return str.replace(/"/g, '\\"').replace(/\n/g,"\\n").replace(/\r/g,"\\r"); //'
		}
		switch (typeof(obj)) {
		    case "string": return '"'+sanitize(obj)+'"';
		    case "number":
		    case "boolean": return obj.toString();
		    case "object":
			if (obj === null) {
			    return "null";
			} else if (obj instanceof Number || obj instanceof Boolean || obj instanceof RegExp)  { 
			    return obj.toString(); 
			} else if (obj instanceof String) { 
			    return '"'+sanitize(obj)+'"'; 
			} else if (obj instanceof Date) { 
			    return "new Date("+obj.getTime()+")"; 
			} else if (obj instanceof Array) {
			    var arr = [];
			    for (var i=0;i<obj.length;i++) {
				arr.push(arguments.callee(obj[i]));
			    }
			    return "["+arr.join(", ")+"]";
			} else if (obj instanceof Object) {
			    var arr = [];
			    for (var p in obj) {
				var str = sanitize(p) + ":" + arguments.callee(obj[p]);
				arr.push(str);
			    }
			    return "{"+arr.join(", ")+"}";
			}
		    break;
		}
		return null;
    },
    unserialize:function(str) {
		return eval("("+str+")");
    }
}
