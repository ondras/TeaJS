var Buffer = require("binary").Buffer;
var alphabetString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
var alphabetBuffer = new Buffer(alphabetString, "utf-8");

exports.encode = function(input) {
	if (!(input instanceof Buffer)) { input = new Buffer(input, "utf-8"); }

	var output = new Buffer(4 * Math.ceil(input.length / 3));
	var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
	var i=0, j=0;
	system.stdout(input.length);
	do {
		chr1 = (i < input.length ? input[i++] : NaN);
		chr2 = (i < input.length ? input[i++] : NaN);
		chr3 = (i < input.length ? input[i++] : NaN);

		enc1 = chr1 >> 2;
		enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
		enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
		enc4 = chr3 & 63;

		if (isNaN(chr2)) { 
			enc3 = enc4 = 64;
		} else if (isNaN(chr3)) {
			enc4 = 64;
		}
		
		output[j++] = alphabetBuffer[enc1];
		output[j++] = alphabetBuffer[enc2];
		output[j++] = alphabetBuffer[enc3];
		output[j++] = alphabetBuffer[enc4];

	} while (i < input.length);

	return output;
};


exports.decode = function(input) {
	if (!(input instanceof Buffer)) { input = new Buffer(input, "utf-8"); }

	var output = new Buffer(Math.ceil(3 * input.length / 4));
	var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
	var i=0, j=0;
	
	try {

		do {
			enc1 = alphabetBuffer.indexOf(input[i++]);
			enc2 = alphabetBuffer.indexOf(input[i++]);
			enc3 = alphabetBuffer.indexOf(input[i++]);
			enc4 = alphabetBuffer.indexOf(input[i++]);

			chr1 = (enc1 << 2) | (enc2 >> 4);
			chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
			chr3 = ((enc3 & 3) << 6) | enc4;

			output[j++] = chr1;
			
			if (enc3 != 64) { output[j++] = chr2; }
			if (enc4 != 64) { output[j++] = chr3; }
		} while (i < input.length);

	} catch (e) {
		throw new Error("Malformed base64 sequence at char " + i);
	}

	output = output.range(0, j);
	return output;
};
