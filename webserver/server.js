var exec = require('child_process').exec;

var express = require('express');

var server = express();
server.use(express.static(__dirname + '/../'));

var port = 8080;
server.listen(port, function() {
    console.log('server listening on port ' + port);
});
var child = require('child_process').spawn('roslaunch', ['lidar_robot', 'lidar_robot.launch']);

child.stdout.on('data', function (data) {
  console.log(data.toString());
});

child.stderr.on('data', function (data) {
  console.error(data.toString());
});

child.on('close', function (code) {
    console.log('child process exited with code ' + code);
});
