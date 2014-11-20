// Include required packages
var http = require('http'),
    url = require('url'),

// Include custom files
    err       = require('./src/err.js').err,
    config    = require('./config.json'),
    db        = require('./src/db.js').db,
    extra     = require('./src/extra.js').extra,

    version   = require('./src/version.js').version,
    startGame = require('./src/startGame.js').startGame,
    listGames = require('./src/listGames.js').listGames,
    joinGame  = require('./src/joinGame.js').joinGame,
    endGame   = require('./src/endGame.js').endGame,
    next      = require('./src/next.js').next,
    ret       = require('./src/ret.js').ret,
    move      = require('./src/move.js').move;

// Create the HTTP server
http.createServer(function(req,res){

  // Parse the URL to get the GET request
  var get = url.parse(req.url, true);

  // Get the Request and parameters
  // q: GET Parameters
  // p: Server Request
  var q = get.query,
      p = get.pathname.substring(1);

  if(config.authReq.indexOf(p) === -1){
    // Return 103 if the request was not found
    err(103);
  } else {
    switch(p){
      case 'version':
        version(res);
        break;
      case 'startGame':
        startGame(res,q);
        break;
      case 'listGames':
        listGames(res,q);
        break;
      case 'joinGame':
        joinGame(res,q);
        break;
      case 'endGame':
        endGame(res,q);
        break;
      case 'next':
        next(res,q);
        break;
      case 'move':
        move(res,q);
        break;
      case 'serverAdmin':
        serverAdmin(res,q);
        break;
    }
  }

}).listen(config.port);

var server_time = 0;

// Timekeeping loop, removes old games
setInterval(function(){

  server_time++;

  extra.removeOldGames(server_time);


// Set the interval to 20 seconds
},1000*20);
