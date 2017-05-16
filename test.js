// contents of index.js
const addon = require("./build/Debug/node-uv");
var SegfaultHandler = require('segfault-handler');

SegfaultHandler.registerHandler("crash.log");

addon.start(function() {
	console.log("In Javascript callback");
});

setTimeout(function() {
	console.log("Called in setTimeout");
}, 5);