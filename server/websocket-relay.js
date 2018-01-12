// Use the websocket-relay to serve a raw MPEG-TS over WebSockets. You can use
// ffmpeg to feed the relay. ffmpeg -> websocket-relay -> browser
// Example:
// node websocket-relay yoursecret 8081 8082
// ffmpeg -i <some input> -f mpegts http://localhost:8081/yoursecret

try {

var fs = require('fs'),
	http = require('http'),
	WebSocket = require('ws'); 

if (process.argv.length < 3) {
	console.log(
		'Usage: \n' +
		'node websocket-relay.js [<stream-port> <websocket-port>]'
	);
	process.exit();
}

var STREAM_PORT = process.argv[2] || 10001,
	WEBSOCKET_PORT = process.argv[3] || 10002,
	RECORD_STREAM = false;

var clients = new Map();

// Websocket Server
var socketServer = new WebSocket.Server({port: WEBSOCKET_PORT, perMessageDeflate: false});
socketServer.connectionCount = 0;
socketServer.on('connection', function(socket, upgradeReq) {
	socketServer.connectionCount++;
	var group = upgradeReq.url.substr(1);
	try{
		if(clients.has(group)){
			var socks = clients.get(group);
			if(!socks.has(socket)){
				socks.add(socket)
			}
		} else{
			var socks=new Set;
			socks.add(socket);
			clients.set(group,socks);
		}
	}
	catch(err){
		console.error("Unhandled exception when build connect"+ err);
	}

	console.log(
		'New WebSocket Connection: ', 
		(upgradeReq || socket.upgradeReq).socket.remoteAddress,
		(upgradeReq || socket.upgradeReq).headers['user-agent'],
		'('+socketServer.connectionCount+' total)',group
	);
	socket.on('close', function(code, message){
		try{
			if(clients.has(group)){
				var socks= clients.get(group);
				if (socks.has(socket)){
					socks.delete(socket);
				}
			}
		}catch(err){
			console.error("Unhandled exception when close connect:["+ err + "]");
		}

		socketServer.connectionCount--;
		console.log(
			'Disconnected WebSocket ('+socketServer.connectionCount+' total)'
		);
	});

	socket.on('error', function(e){	
		console.log(e)
	});
});

socketServer.broadcast = function(data, group) {
	try{
		if(clients.has(group)){
			var socks= clients.get(group);
			for (var sock of socks.values()) {
				if(sock.readyState===WebSocket.OPEN){
					sock.send(data);
				}
			}
		}
	} catch(err){
		console.error("Unhandled exception when broad cast mpeg-ts data err:" + err);
	}
};

// HTTP Server to accept incomming MPEG-TS Stream from ffmpeg
var streamServer = http.createServer( function(request, response) {
	var params = request.url.substr(1).split('/');

	response.connection.setTimeout(0);
	console.log(
		'Stream Connected: ' + 
		request.socket.remoteAddress + ':' +
		request.socket.remotePort
	);
	request.on('data', function(data){
		socketServer.broadcast(data, params[0]);
		if (request.socket.recording) {
			request.socket.recording.write(data);
		}
	});
	request.on('end',function(){
		console.log('close');
		if (request.socket.recording) {
			request.socket.recording.close();
		}
	});

	// Record the stream to a local file?
	if (RECORD_STREAM) {
		var path = 'recordings/' + Date.now() + '.ts';
		request.socket.recording = fs.createWriteStream(path);
	}
}).listen(STREAM_PORT);

console.log('Listening for incomming MPEG-TS Stream on http://0.0.0.0:/');
console.log('Awaiting WebSocket connections on ws://0.0.0.0:'+WEBSOCKET_PORT+'/');
}
catch(e){
	console.error("Unhandled exception all" + e);
}
