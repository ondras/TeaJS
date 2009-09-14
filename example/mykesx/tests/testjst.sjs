// testjst.sjs

include('../lib/lib.js');
include('../lib/Jst.js');

function file_get_contents(fn) {
	var f = new File(fn);
	f.open('r');
	var contents = f.read();
	f.close();
	return contents;
}

println('hello');
var tpl = file_get_contents('test.tpl');
var parsed = Jst.parse(tpl);
println(Jst.executeParsed(parsed, { name: 'flintstone' }));
