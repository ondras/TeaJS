var Json = {
	encode: function(obj) {
		return JSON.stringify(obj);
	},
	decode: function(s) {
		return JSON.parse(s);
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
