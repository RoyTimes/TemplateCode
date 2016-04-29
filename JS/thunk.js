var x = function (b) {
	return b + 1;
}

console.log(x (8 + 10));

var y = function (a, b) {
	return b;
}

console.log(y (8*9+1, 10))
////////

int first (x) {
	return x * 2;
}
printf ("%d", first( y + 10 ));

--> 

int second (y) {
	return (y + 10);
}
printf ("%d", first (second (x)))

////
fs.readFile(filename, callback);
-->
let Thunk = function(filename) {
	return function(callback) {
		return fs.readFile(filename, callback);
	}
}
readFile = Thunk (filename);
readFile(callback);


function * fn(x) {
	var one = yield 1;
	var two = yield 2;
	console.log(one + " - " + two);
}

var Gen = fn();
fn.next(); -> 1
fn.next(); -> 2
fn.next(); -> 1 - 2








