// Include neccessary packages
var http = require('http'),
    url = require('url');

// Declare the return object. Global as functions use it
var ret = {};

// Create the server
http.createServer( function(req , res){
  // Respond with HTTP status 200 OK, and set the content-type to json
  res.writeHead(200, {'Content-Type': 'application/json'});

  // Return the finished JSON result and clear the result
  res.end( JSON.stringify(ret) );
  ret = {};

// Set the server port
}).listen(1337);
