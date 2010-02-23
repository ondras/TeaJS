exports.Buffer.prototype.Content = Number;

exports.Buffer.prototype.toSource = function() {
	var arr = [];
	for (var i=0;i<this.length;i++) { arr.push(this[i]); }
	return 'require("binary").Buffer([' + arr.join(", ") + '])';
}
