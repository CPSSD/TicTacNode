// Include required packages
var http = require('http'),
    url = require('url'),
    mongojs = require('mongojs'),

// Include custom files
    err       = require('./src/err.js'),
    config    = require('./config.json'),
    ret       = require('./src/ret.js'),
    extra     = require('./src/extra.js');

var action = {
  version   : require('./src/version.js'),
  startGame : require('./src/startGame.js'),
  listGames : require('./src/listGames.js'),
  joinGame  : require('./src/joinGame.js'),
  endGame   : require('./src/endGame.js'),
  next      : require('./src/next.js'),
  move      : require('./src/move.js'),
  serverAdmin: require('./src/serverAdmin.js')
};

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
    ret(res, err(103));
  } else {
    // Otherwise execute the proper command
    action[p](res, q ,server_time);
  }

}).listen(config.server.port);

// Timekeeping loop, updates server time and clears old games
setInterval(function(){

  extra.updateServerTime(function(new_time){
    server_time = new_time;
  });

  extra.removeOldGames(server_time);


// Set the check interval
},config.server.check_interval);
