// Include neccessary packages
var http = require('http'),
    url = require('url');

// Declare the return object. Global as functions use it
var ret = {};

// The game "database". Stores all games, users, boards and moves.
// DATA LOST ON RESTART
var game = [];

// Create the server
http.createServer( function(req , res){
  // Respond with HTTP status 200 OK, and set the content-type to json
  res.writeHead(200, {'Content-Type': 'application/json'});

  // Parse the URL to get the GET requests
  var get = url.parse(req.url, true);

  // Declare the query and pathname
  var q = get.query,
      p = get.pathname;

  // Check is the action given
  if(p === "/"){
    err(103);

  // Check are any parameters specified
  } else if(Object.getOwnPropertyNames(q).length === 0){
    err(101);

  // If everything is correct, proceed.
  } else {
    switch(p){
      // Do this on new Game
      case '/newGame':
        newGame(q);
        break;

      // Do this on next
      case '/next':
        next(q);
        break;

      // Do this on move
      case '/move':
        move(q);
        break;

      // If the request is not found, return Error 103
      default:
        err(103);
        break;
    }
  }


  // Return the finished JSON result and clear the result
  res.end( JSON.stringify(ret) );
  ret = {};

// Set the server port
}).listen(1337);








////////////////////////////////////
//    ALL NECCESSARY FUNCTIONS    //
////////////////////////////////////


// newGame function
function newGame(q){

}

// next function
function next(q){

}

// move function
function move(q){

}


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
