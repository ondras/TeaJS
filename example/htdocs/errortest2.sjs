// errortest.sjs

// cause a runtime error

function foo() {
	bar();
}

function bar() {
	baz(); // undefined
}

foo();
