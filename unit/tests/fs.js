/**
 * This file tests the "fs" module.
 * Several tests are performed with both files and directories.
 * It is necessary to have write access to current directory. If anything fails here,
 * please delete manually any intermediate files and/or directories created.
 */

var assert = require("assert");
var fs = require("fs");

exports.testFile = function() {
	var n1 = "n1_testfile_"+Math.random();
	var n2 = "n2_testfile_"+Math.random();
	var buffer = new (require("binary").Buffer)([10, 11, 12]);
	
	var f = new fs.File(n1);
	assert.equal(f.exists(), false, "non-existing file");

	f.open("wb").write("abc").write(buffer).close();
	assert.equal(f.exists(), true, "existing file");
	assert.equal(f.isFile(), true, "isFile");
	
	var stat = f.stat();
	assert.equal(stat.size, 6, "file size");
	
	f.open("rb");
	var data = f.read(3);
	assert.equal(data.toString("utf-8"), "abc", "utf-8 encoded");
	
	var data = f.read();
	assert.equal(data.toSource(), buffer.toSource(), "binary read");
	f.close();

	var old = new fs.File(n1);
	f.move(n2);
	assert.equal(f.exists(), true, "move exists target");
	assert.equal(old.exists(), false, "move removes source");

	var n = f.copy(n1);
	assert.equal(n.exists(), true, "copy exists target");
	assert.equal(f.exists(), true, "copy exists source");

	n.remove();
	f.remove();
	assert.equal(f.exists(), false, "deleted file #1");
	assert.equal(n.exists(), false, "deleted file #2");
}

exports.testDirectory = function() {
	var n = "testdir_"+Math.random();
	
	var d = new fs.Directory(n);
	assert.equal(d.exists(), false, "non-existing directory");

	d.create();
	assert.equal(d.exists(), true, "existing directory");
	assert.equal(d.isDirectory(), true, "isDirectory");
	
	var f1 = new fs.File(n+"/a").open("w").close();
	var d1 = new fs.Directory(n+"/b").create();
	
	var files = d.listFiles();
	var dirs = d.listDirectories();
	assert.equal(files.join(","), "a", "list of files");
	assert.equal(dirs.join(","), "b", "list of directories");
	
	f1.remove();
	d1.remove();

	d.remove();
	assert.equal(d.exists(), false, "deleted directory");
}

exports.testReadWriteLine = function() {
	var n = "testfile_"+Math.random();
	var f = new fs.File(n);
	var arr = ["abc", "def", "ghi"];
	
	f.open("w");
	for (var i=0;i<arr.length;i++) { f.writeLine(arr[i]); }
	f.close();
	
	f.open("r");
	while (1) {
		var line = f.readLine();
		if (!line) { break; }
		assert.equal(line.toString("ascii"), arr.shift() + "\n", "written and read lines are equal");
	}
	f.close();
	
	f.remove();
}
