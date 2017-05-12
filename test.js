// contents of index.js
const addon = require("./build/Debug/node-uv");
var SegfaultHandler = require('segfault-handler');

SegfaultHandler.registerHandler("crash.log");

console.log("calling addon");
addon.start();
console.log("called addon");

