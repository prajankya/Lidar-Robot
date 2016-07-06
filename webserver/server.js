var sudo = require('sudo');
var express = require('express');

var sudoOptions = {
    cachePassword: true,
    prompt: 'Please Enter Sudo Password ? ',
    password: 'admp',
    spawnOptions: { /* other options for spawn */ }
};

function c_log(child) {
    child.stdout.on('data', function(data) {
        console.log(data.toString());
    });

    child.stderr.on('data', function(data) {
        console.error(data.toString());
    });

    child.on('close', function(code) {
        console.log('child process exited with code ' + code);
        //	    process.exit(code);
    });
}

var port = 8080;
var app = express();

app.get('/', function(request, response) {
    response.sendFile(__dirname + '/index.html');
});

app.use(express.static(__dirname + '/../'));

app.listen(port, function() {
    console.log('server listening on port ' + port);
});

var port_forwarder = sudo([
    'iptables', '-t', 'nat', '-A', 'PREROUTING', '-i', 'wlan0', '-p', 'tcp', '--dport', '80', '-j', 'REDIRECT', '--to-port', '8080'
], sudoOptions).on('error', function(err) {
    console.error(err);
});
c_log(port_forwarder);


var create_ap = sudo([
  'bash', __dirname + '/create_ap/create_ap', '--redirect-to-localhost', '--config', __dirname + '/create_ap/create_ap.conf'
], sudoOptions).on('error', function(err) {
    console.error(err);
});
c_log(create_ap);

var ros = require('child_process').spawn('roslaunch', ['lidar_robot', 'lidar_robot.launch']).on('error', function(err) {
    console.error(err);
});
c_log(ros);
