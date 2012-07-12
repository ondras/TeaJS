var Socket = require("socket").Socket;

var eventCount = 0;
var lastId = 0;
var running = false; /* to prevent double-run */
var aborted = false; /* aborted flag (running for too long) */
var events = { /* all scheduled events */
	time: {},
	socket: {}
}; 

/* ---- private ---- */

var addTimeListener = function(callback, delay, repeat) {
	eventCount++;
	var id = lastId++;

	events.time[id] = {
		callback: callback,
		ts: Date.now() + delay,
		repeat: (repeat ? delay : -1)
	}

	return id;
}

var addSocketListener = function(callback, socket, read) {
	eventCount++;
	var id = lastId++;

	events.socket[id] = {
		callback: callback,
		socket: socket,
		read: read
	}

	return id;
}

var processSockets = function(read, write) {
	for (var id in events.socket) {
		var item = events.socket;
		if (
			(item.read && read.indexOf(item.socket) != -1) /* readable */
			||
			(!item.read && write.indexOf(item.socket) != -1) /* writeable */
			) {
			exports.clearSocket(id);
			item.callback();
		}
	}
}

var processTime = function() {
	var now = Date.now();
	for (var id in events.time) {
		var item = events.time[id];
		if (item.ts > now) { continue; }
		
		if (item.repeat > -1) {
			item.ts = now + item.repeat;
		} else {
			exports.clearTimeout(id);
		}
		
		item.callback();
	}
}

/* ---- public ---- */

exports.run = function(maxTime) {
	if (running) { throw new Error("Event loop is already running"); }
	if (!eventCount) { return false; }
	running = true;
	aborted = false;
	
	if (maxTime) { /* maximum milliseconds to run */
		exports.setTimeout(function() { aborted = true; }, maxTime);
	}
	
	
	while (eventCount && !aborted) {
		/* prepare data for Socket.select() */
		var now = Date.now();
		var read = [], write = [], timeout = 1/0;
	
		/* find closest time */
		for (var id in events.time) {
			var diff = Math.max(0, events.time[id] - now);
			timeout = Math.min(timeout, diff);
		}
		if (timeout == 1/0) { timeout = null; }
		
		/* prepare socket arrays */
		for (var id in events.socket) {
			var item = events.socket[id];
			(item.read ? read : write).push(item.socket);
		}
		
		try {
			var result = Socket.select(read, write, null, timeout);
		} catch (e) {
			break;
		}

		processTime();
		if (result) { processSockets(read, write); }
		
	}
	running = false;
	return true;
}

exports.setTimeout = function(callback, delay) {
	return addTimeListener(callback, delay, false);
}

exports.setInterval = function(callback, period) {
	return addTimeListener(callback, period, true);
}

exports.clearTimeout = exports.clearInterval = function(id) {
	if (id in events.time) {
		delete events.time[id];
		eventCount--;
	}
}

exports.readSocket = function(callback, socket) {
	return addSocketListener(callback, socket, true);
}

exports.writeSocket = function(callback, socket) {
	return addSocketListener(callback, socket, false);
}

exports.clearSocket = function(id) {
	if (id in events.socket) {
		delete events.socket[id];
		eventCount--;
	}
}
