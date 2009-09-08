// Json utility class.
// This class contains routines for encoding and decoding Json,
// as well as formulating ExtJS style Json responses.

var Json = {
	encode: function(obj) {
		return JSON.stringify(obj);	// native v8 version
	},
	decode: function(s) {
		return JSON.parse(s);		// native v8 version
	},
	success: function(obj) {
		obj = obj || {};
		obj.success = true;
		obj.elapsed = new Date().getTime() / 1000 - response.start_time ;
		ob_end_clean();
		print(Json.encode(obj));
		exit();
	},
	failure: function(msg) {
		ob_end_clean();
		print(Json.encode({ success: false, message: msg, elapsed: new Date().getTime() / 1000 - response.start_time  }));
		exit();
	},
	exception: function(msg) {
		ob_end_clean();
		print(Json.encode({ exception: msg, elapsed: new Date().getTime() / 1000 - response.start_time  }));
		exit();
	}
};

exports.Json = Json;
