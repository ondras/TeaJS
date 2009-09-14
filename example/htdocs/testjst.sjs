// testjst.sjs

var tpl = file_get_contents('test.tpl');
var parsed = Jst.parse(tpl);
println(Jst.executeParsed(parsed, { name: 'flintstone' }));

println('<p><a href="/">Return to home page</a></p>');


println('<h1>Source to this page</h1>');
println('<pre style="background: #efefef; padding: 5px; border: 1px solid black;">');
println(file_get_contents('testjst.sjs').replace(/</g, '&lt;'));
println('</pre>');

println('<h1>Source to the template test.tpl</h1>');
println('<pre style="background: #efefef; padding: 5px; border: 1px solid black;">');
println(file_get_contents('test.tpl').replace(/</g, '&lt;'));
println('</pre>');

