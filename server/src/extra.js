var db = require('./db.js'),
    config = require('../config.json'),
    btoa = require('btoa'),
    _ = require('underscore');

/**
 * Create the extra object and return
 * @module
**/
module.exports = {
  /**
   * Remove old games
   * @function
   * @param {integer} s_t - Current server time
  **/
  removeOldGames: function(s_t){
    db.games.update(
      { "last_move": { $lt: s_t - config.server.timeout } },
      { $set: { winner: 0, finished: true }  },
      { multi: true },
      function(){}
    );
  },

  /**
   * Updates the server time in the database and returns the time
   * @function
   * @param {function} callback - Return updated server time once complete
   * @returns {integer} callback - Return current server time as callback parameter
  **/
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

  /**
   * Increment the game ID and return asynchronously
   * @function
   * @param {function} callback - Return the updated ID once the action is completed
   * @returns {integer} Integer value of current game as callback parameter
  **/
  updateGameID: function(callback){
    db.meta.findAndModify({
      query: {},
      update: { $inc: { current_id: 1 } },
      new: true,
      upsert: true
    }, function(er, data){
      callback(data.current_id);
    });
  },

  /**
   * Check does the list of requests contain a specific request
   * @function
   * @param {string} param - The property to be checked
   * @param {object} q - The object containing all current requests
   * @returns {boolean} Whether the query did contain the specific param
  **/
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

  /**
   * Check do the parameters match between request and authorised parameters
   * @function
   * @param {array} params - The array of properties to be checked
   * @param {object} q - The object containing all current requests
   * @returns {boolean}
  **/
  checkParams: function(params, q){
    params = (typeof params === null) ? [] : params;
    q = Object.keys(q);
    return _.isEqual(params, q) ? true : (params.splice(params.indexOf("pin"),1), _.isEqual(params, q));
  },

  /**
   * Check how many parameters there are
   * @function
   * @param {object} q - The object containing all current requests
   * @returns {integer} The amount of current requests
  **/
  paramsLength: function(q){
    return Object.getOwnPropertyNames(q).length;
  },

  // Generate the secret
  /**
   * Check do the parameters match between request and authorised parameters
   * @function
   * @returns {string} base64 encoded random string
  **/
  secretGen: function(){
    var r1 = Math.floor( Math.random()*Math.pow(10,17) ).toString(),
        r2 = Math.floor( Math.random()*Math.pow(10,17) ).toString(),
        r = r1+r2;

        r = r.length%2 === 0 ? r+"ab" : r;

    return btoa( r );
  },

  /**
   * Function to update the time of last move on the server
   * @function
   * @param {string} game_id - The ID of the game to be updated
  **/
  updateLastMove: function(game_id){
    db.meta.findOne({}, function(er, data){
      db.games.update({id: game_id}, { $set: { last_move: data.server_time } });
    });
  },

  /**
   * Function to set a winner of the current game
   * @private
   * @function
   * @param {string} game_id - The ID of the game to be updated
   * @param {integer} letter - The letter of the winning player
  **/
  setWinner: function(game_id, letter){
    db.games.update({id: game_id},{ $set: { winner: letter, finished:true } }, function(){});
  },

  /**
   * Function check the winner of the game
   * @function
   * @param {string} game_id - The ID of the game
  **/
  checkWinner: function(game_id){
    db.games.findOne({id: game_id}, function(er, game){
      var b = game.board;

      // Check horizontally and vertically
      for( var i = 0; i < 3; i++){
        if(b[i*3] == b[i*3 + 1] && b[i*3] == b[i*3 + 2] && b[i*3] > 0){
          module.exports.setWinner(game_id, b[i*3]);
        }
        if (b[i] == b[i + 3] && b[i] == b[i + 6] && b[i] > 0) {
          module.exports.setWinner(game_id, b[i]);
        }
      }

      // Check diagonally
      if (b[0] == b[4] && b[0] == b[8] && b[0] > 0) {
        module.exports.setWinner(game_id,b[0]);
      }
      if (b[2] == b[4] && b[2] == b[6] && b[2] > 0) {
        module.exports.setWinner(game_id, b[2]);
      }

      // Check are there any 0s. If there are it means game is not finished
      for(var x = 0; x < b.length; x++){
        if(b[x] === 0){
          return;
        }
      }

      // Else set as draw
      module.exports.setWinner(game_id, 0);

    });
  }
};
