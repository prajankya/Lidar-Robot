var express = require('express');

var server = express();
server.use(express.static(__dirname));

var port = 8080;
server.listen(port, function() {
    console.log('server listening on port ' + port);
});
var child2 = require('child_process').spawn('roslaunch', ['rosbridge_server', 'rosbridge_websocket.launch']);

child2.stdout.on('data', function (data) {
  console.log(data.toString());
});

child2.stderr.on('data', function (data) {
  console.error(data.toString());
});

child2.on('close', function (code) {
    console.log('child process exited with code ' + code);
});

var child = require('child_process').spawn('rosrun', ['map_server', 'map_server', '/home/prajankya/map.pgm', '0.05']);

child.stdout.on('data', function (data) {
  console.log(data.toString());
});

child.stderr.on('data', function (data) {
  console.error(data.toString());
});

child.on('close', function (code) {
    console.log('child process exited with code ' + code);
    process.exit(code);
});
