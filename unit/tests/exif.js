/**
 * This file tests html HTML module.
 */

var assert = require("assert");
var EXIF = require("exif");
var FS = require("fs");

exports.testReader = function() {
	var parts = module.id.split(/[\/\\]/);
	parts.pop();
	parts.push("sample.jpg");
	var path = parts.join("/");
	
	var file = new FS.File(path);
	var data = file.open("r").read();
	var tags = new EXIF.Reader(data).getTags();
	
	assert.equal(tags["Model"].trim(), "E-420", "EXIF Camera Model");
	assert.equal(tags["ISOSpeedRatings"], 100, "EXIF ISO");
	assert.equal(tags["Flash"], 8, "EXIF Flash");
	assert.equal(tags["GPSLongitudeRef"], "E", "EXIF GPS Longitude reference");
	assert.equal(tags["GPSLongitude"].join("/"), "17/4/22.24", "EXIF GPS Longitude");
}
