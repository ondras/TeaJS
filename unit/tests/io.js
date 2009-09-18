/**
 * This file tests the built-in IO module.
 * Several tests are performed with both files and directories.
 * It is necessary to have write access to current directory. If anything fails here,
 * please delete manually any intermediate files and/or directories created.
 */

var assert = require("assert");

exports.testFile = function() {
	var n1 = "n1_testfile_"+Math.random();
	var n2 = "n2_testfile_"+Math.random();
	
	var f = new File(n1);
	assert.assertEquals("non-existing file", false, f.exists());

	f.open("wb").write("abc").write([10,11,12]).close();
	assert.assertEquals("existing file", true, f.exists());
	assert.assertEquals("isFile", true, f.isFile());
	
	var stat = f.stat();
	assert.assertEquals("file size", 6, stat.size);
	
	f.open("rb");
	var data = f.read(3);
	assert.assertEquals("text read", "abc", data);
	var data = f.read(false, true);
	assert.assertEquals("binary read", "10,11,12", data.join(","));
	f.close();
	
	var old = new File(n1);
	f.move(n2);
	assert.assertEquals("move exists target", true, f.exists());
	assert.assertEquals("move removes source", false, old.exists());

	var n = f.copy(n1);
	assert.assertEquals("copy exists target", true, n.exists());
	assert.assertEquals("copy exists source", true, f.exists());

	n.remove();
	f.remove();
	assert.assertEquals("deleted file #1", false, f.exists());
	assert.assertEquals("deleted file #2", false, n.exists());
}

exports.testDirectory = function() {
	var n = "testdir_"+Math.random();
	
	var d = new Directory(n);
	assert.assertEquals("non-existing directory", false, d.exists());

	d.create();
	assert.assertEquals("existing directory", true, d.exists());
	assert.assertEquals("isDirectory", true, d.isDirectory());
	
	var f1 = new File(n+"/a").open("w").close();
	var d1 = new Directory(n+"/b").create();
	
	var files = d.listFiles();
	var dirs = d.listDirectories();
	assert.assertEquals("list of files", "a", files.join(","));
	assert.assertEquals("list of directories", "b", dirs.join(","));
	
	f1.remove();
	d1.remove();

	d.remove();
	assert.assertEquals("deleted directory", false, d.exists());
}
