var HTML = {
	escape: function(str) {
		if (str === null || !str.toString) { return ""; }
		return str.toString()
			.replace(/&/g,"&amp;")
			.replace(/</g,"&lt;")
			.replace(/>/g,"&gt;")
			.replace(/"/g,"&quot;")
			.replace(/'/g,"&apos;");
	},
	unescape: function(str) {
		if (str === null || !str.toString) { return ""; }
		return str.toString()
			.replace(/&apos;/g,"'")
			.replace(/&quot;/g,"\"")
			.replace(/&gt;/g,">")
			.replace(/&lt;/g,"<")
			.replace(/&amp;/g,"&");
	},
	dump: function(o) {

	   if( o === null) { return "null"; }
	   if( o === undefined) { return "undefined"; }

	   var t = typeof o;

	   if( t == "function") {
	     var prototypeFunctions = [];
	     for(var fct in o.prototype) {
	        prototypeFunctions.push(fct);
	     }
	     return "("+prototypeFunctions.join(',')+")";
	   }
	   if( t == "string") { return "<span style='color: green;'>\""+o+"\"</span>"; }
	   if( t == "number" || t == "boolean") {
	      return "<span style='color: blue;'>"+o+"</span>";
	   }

	   var str = "<ul>";
	   for(var key in o) {
	      if(o.hasOwnProperty(key) && key != "global") {
	         str += "<li>"+key+": "+HTML.dump(o[key])+"</li>";
	      }
	   }
	   str += "</ul>";
	   return str;
	}
};

exports.HTML = HTML;
