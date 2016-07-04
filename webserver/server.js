/*(function() {
    var childProcess = require("child_process");
    var oldSpawn = childProcess.spawn;

    function mySpawn() {
        console.log('spawn called');
        console.log(arguments);
        var result = oldSpawn.apply(this, arguments);
        return result;
    }
    childProcess.spawn = mySpawn;
})();*/

var exec = require('child_process').exec;
var sudo = require('sudo');
var options = {
    cachePassword: true,
    prompt: 'Please Enter Sudo Password ? ',
    Password: 'admp',
    spawnOptions: { /* other options for spawn */ }
};

var express = require('express');

var server = express();
server.use(express.static(__dirname + '/../'));

var port = 8080;

server.listen(port, function() {
    console.log('server listening on port ' + port);
    /*  try {
          console.log('Old User ID: ' + process.getuid() + ', Old Group ID: ' + process.getgid());
          process.setgid('prajankya');
          process.setuid('prajankya');
          console.log('New User ID: ' + process.getuid() + ', New Group ID: ' + process.getgid());

          console.log(process.env.PATH);
      } catch (err) {
          console.log('Cowardly refusing to keep the process alive as root.');
          process.exit(1);
      }*/

    //    console.log('User ID:', process.getuid() + ', Group ID:', process.getgid());
    //drop_root();
    //    console.log('User ID:', process.getuid() + ', Group ID:', process.getgid());
    //
    //
    //sudo apt-get install libcap2-bin
    //sudo setcap cap_net_bind_service=+ep `readlink -f \`which node\``
    //
});

var ros = require('child_process').spawn('roslaunch', ['lidar_robot', 'lidar_robot.launch']).on('error', function(err) {
    console.log(err);
});
c_log(ros);
//sudo iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 80 -j REDIRECT --to-port 3000
var port_forwarder = sudo(['iptables', '-t', 'nat', '-A', 'PREROUTING', '-i', 'wlan0', '-p', 'tcp', '--dport', '80', '-j', 'REDIRECT', '--to-port', '8080'], options);
var create_ap = sudo(['bash', __dirname + '/create_ap/create_ap', '--redirect-to-localhost', '--config', __dirname + '/create_ap/create_ap.conf'], options);

c_log(port_forwarder);
c_log(create_ap);

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
