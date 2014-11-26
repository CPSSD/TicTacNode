// Include required packages
var http = require('http'),
    url = require('url'),
    mongojs = require('mongojs'),

// Include custom files
    err       = require('./src/err.js'),
    config    = require('./config.json'),
    ret       = require('./src/ret.js'),
    db        = require('./src/db.js'),
    extra     = require('./src/extra.js'),
    serverAdmin = require('./src/serverAdmin.js'),

    version   = require('./src/version.js'),
    startGame = require('./src/startGame.js'),
    listGames = require('./src/listGames.js'),
    joinGame  = require('./src/joinGame.js'),
    endGame   = require('./src/endGame.js'),
    next      = require('./src/next.js'),
    move      = require('./src/move.js');

// Return object
var ret = {};

// Server Time
var server_time = 0;
extra.updateServerTime(function(new_time){
  server_time = new_time;
});

// Create the HTTP server
http.createServer(function(req,res){

  // Parse the URL to get the GET request
  var get = url.parse(req.url, true);

  // Get the Request and parameters
  // q: GET Parameters
  // p: Server Request
  var q = get.query,
      p = get.pathname.substring(1);

  if(config.authReq.indexOf(p) === -1 || p.length === 0){
    // Return 103 if the request was not found
    err(103);
  } else {
    switch(p){
      case 'version':
        version(res);
        break;
      case 'startGame':
        startGame(res, q, server_time);
        break;
      case 'listGames':
        listGames(res, q, server_time);
        break;
      case 'joinGame':
        joinGame(res, q, server_time);
        break;
      case 'endGame':
        endGame(res, q, server_time);
        break;
      case 'next':
        next(res, q);
        break;
      case 'move':
        move(res, q, server_time);
        break;
      case 'serverAdmin':
        serverAdmin(res);
        break;
    }
  }

}).listen(config.port);

// Timekeeping loop, updates server time and clears old games
setInterval(function(){

  extra.updateServerTime(function(new_time){
    server_time = new_time;
  });
  
  extra.removeOldGames(server_time);


// Set the interval to 20 seconds
},1000*20);
