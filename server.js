var exec = require('child_process').exec;

var express = require('express');
 
var server = express();
server.use(express.static(__dirname + '/'));
 
var port = 8080;
server.listen(port, function() {
    console.log('server listening on port ' + port);
});

function puts(err, out, code) {
  if (err instanceof Error)
    throw err;
  process.stderr.write(err);
  process.stdout.write(out);
  process.exit(code);
}

exec('roslaunch lidar_robot server.launch', puts);
