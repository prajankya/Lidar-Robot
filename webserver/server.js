var exec = require('child_process').exec;
var sudo = require('sudo');
var options = {
    cachePassword: true,
    prompt: 'Please Enter Sudo Password ? ',
    spawnOptions: { /* other options for spawn */ }
};

var express = require('express');

var server = express();
server.use(express.static(__dirname + '/../'));

var port = 80;

server.listen(port, function() {
    console.log('server listening on port ' + port);

// console.log('User ID:',process.getuid()+', Group ID:',process.getgid());
//    drop_root();
//   console.log('User ID:',process.getuid()+', Group ID:',process.getgid());
//
//
//sudo apt-get install libcap2-bin
//sudo setcap cap_net_bind_service=+ep `readlink -f \`which node\``
//
});

var create_ap = sudo([ 'bash',__dirname + '/create_ap/create_ap', '--redirect-to-localhost','--config',__dirname +  '/create_ap/create_ap.conf'], options);

var ros = require('child_process').spawn('roslaunch', ['lidar_robot', 'lidar_robot.launch']);

c_log(create_ap);
c_log(ros);

function c_log(child){
	child.stdout.on('data', function (data) {
	  console.log(data.toString());
	});

	child.stderr.on('data', function (data) {
	  console.error(data.toString());
	});

	child.on('close', function (code) {
	    console.log('child process exited with code ' + code);
//	    process.exit(code);
	});
}
