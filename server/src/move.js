var db = require('./db.js'),
    ret = require('./ret.js'),
    extra = require('./extra.js'),
    err = require('./err.js');

    checkParam = extra.checkParam;
    checkWinner = extra.checkWinner;

/**
 * Perform a move
 * @exports move
**/
module.exports = function(res, q, s_t){
  if(!checkParam("secret",q) || !checkParam("position",q) ){
    ret(res, err(101));
  } else {
    if(q.position < 0 || q.position > 8){
      ret(res, err(106));
    } else {
      db.games.findOne({"player.secret": q.secret}, function(er, game){

        if(!game){
          ret(res, err(107));
        } else if(game.finished){
          ret(res, err(100, "Game has timed out or is finished"));
        } else {

          // Get the board and the letter of the current player
          var b = game.board;
          var l = (game.player[0].secret == q.secret) ? game.player[0].letter : game.player[1].letter;

          // Check is it players turn
          if(l != game.next){
            ret(res, err(105));
          } else {

            // Check is the position valid
            if(b[q.position] !== 0){
              ret(res, err(106));
            } else {
              b[q.position] = l;

              // Change the next to the opposite player
              var nxt = (l == 1) ? 2 : 1;

              // Update the games and check the winner when complete
              db.games.update({id: game.id},{ $set: { board: b, next: nxt}}, function(){
                checkWinner(game.id);
              });

              // Return the status
              ret(res, {"status": "okay"});
            }
          }


        }
      });
    }
  }
};
