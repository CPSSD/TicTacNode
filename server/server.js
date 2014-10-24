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








////////////////////////////////////
//    ALL NECCESSARY FUNCTIONS    //
////////////////////////////////////



// Error handling
function err(c){
  ret.status = "error";
  ret.code = c;
  switch(c){
    case 100:
      ret.message = "Other Error";
      break;

    case 101:
      ret.message = "Missing parameter in request";
      break;

    case 102:
      ret.message = "Unknown parameter in request";
      break;

    case 103:
      ret.message = "Unknown request";
      break;

    case 104:
      ret.message = "Server not ready or busy";
      break;

    case 105:
      ret.message = "Not players turn";
      break;

    case 106:
      ret.message = "Invalid move";
      break;
  }
}
