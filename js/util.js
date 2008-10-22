var Util = {
    md5:function(str) {
    },
    sha1:function(str) {
    },
    base64encode:function(str) {
    },
    base64decode:function(str) {
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
