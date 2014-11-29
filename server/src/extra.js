var db = require('./db.js'),
    config = require('../config.json'),
    btoa = require('btoa');

module.exports = {
  // Removes old games,
  removeOldGames: function(s_t){
    db.games.update(
      { "last_move": { $lt: s_t - config.server.timeout } },
      { $set: { winner: 0, finished: true }  },
      { multi: true },
      function(){}
    );
  },

  // Updates the server time in the database and returns the time
  updateServerTime: function(callback){
  	db.meta.findAndModify({
  		query: {},
  		update: { $inc: { server_time: 1 } },
  		new: true,
  		upsert: true
  	}, function(er, data){
      callback(data.server_time);
    });
  },

  // Check does the list of requests contain a specific request
  checkParam: function(param, q){
    if(!q.hasOwnProperty(param)){
      return false;
    } else {
      if(q[param].length === 0){
        return false;
      } else {
        return true;
      }
    }
  },

  // Check how many parameters there is
  paramsLength: function(q){
    return Object.getOwnPropertyNames(q).length;
  },

  // Generate the secret
  secretGen: function(){
    var r1 = Math.floor( Math.random()*Math.pow(10,17) ).toString(),
        r2 = Math.floor( Math.random()*Math.pow(10,17) ).toString(),
        r = r1+r2;

        r = r.length%2 === 0 ? r+"ab" : r;

    return btoa( r );
  },

  // Function to update last move
  updateLastMove: function(game_id){
    db.meta.findOne({}, function(er, data){
      db.games.update({id: game_id}, { $set: { last_move: data.server_time } });
    });
  },

  // get the winner of the game
  checkWinner: function(game_id){
    db.games.findOne({id: game_id}, function(er, game){
      var b = game.board;

      // Check horizontally and vertically
      for( var i = 0; i < 3; i++){
        if(b[i*3] == b[i*3 + 1] && b[i*3] == b[i*3 + 2] && b[i*3] > 0){
          setWinner(game_id, b[i*3]);
        }
        if (b[i] == b[i + 3] && b[i] == b[i + 6] && b[i] > 0) {
          setWinner(game_id, b[i]);
        }
      }

      // Check diagonally
      if (b[0] == b[4] && b[0] == b[8] && b[0] > 0) {
        setWinner(game_id,b[0]);
      }
      if (b[2] == b[4] && b[2] == b[6] && b[2] > 0) {
        setWinner(game_id, b[2]);
      }

      // Check are there any 0s. If there are it means game is not finished
      for(var x = 0; x < b.length; x++){
        if(b[x] === 0){
          return;
        }
      }

      // Else set as draw
      setWinner(game_id, 0);

    });
  },

  setWinner: function(game_id, letter){
    db.games.update({id: game_id},{ $set: {winner: letter} }, function(){});
  }
};
