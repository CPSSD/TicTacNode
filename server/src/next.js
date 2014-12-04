var db = require('./db.js'),
    ret = require('./ret.js'),
    extra = require('./extra.js'),
    err = require('./err.js'),

    checkParam = extra.checkParam;

/**
 * Check the current board status and who is next to play
 * @exports next
**/
module.exports = function(res, q){

  if(!checkParam("secret",q)){
    ret(res, err(101));
  } else {

    // Get the game where the secret matches
    db.games.findOne({"player.secret": q.secret}, function(er, game){

      if(!game){
        ret(res, err(107));

      } else {
        var result = {};
        result.status = "okay";
        result.board = game.board;
        if(game.finished){
          result.winner = game.winner;
        } else {
          result.turn = game.next;
        }

        ret(res, result);
        result = {};
      }
    });
  }
};
