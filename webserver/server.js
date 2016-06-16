var exec = require('child_process').exec;

var express = require('express');

var server = express();
server.use(express.static(__dirname + '/../'));

var port = 8080;
server.listen(port, function() {
    console.log('server listening on port ' + port);
});
/*
function puts(err, out, code) {
  if (err instanceof Error)
    throw err;
  process.stderr.write(err);
  process.stdout.write(out);
  process.exit(code);
}

exec('roslaunch lidar_robot server.launch', puts);
*/

var child = require('child_process').spawn('roslaunch', ['lidar_robot', 'server.launch']);

child.stdout.on('data', function (data) {
  console.log('stdout: ' + data);
});

child.stderr.on('data', function (data) {
  console.log('stderr: ' + data);
});

child.on('close', function (code) {
    console.log('child process exited with code ' + code);
});
