var db = require('./db.js'),
    ret = require('./ret.js'),
    extra = require('./extra.js'),
    err = require('./err.js'),

    checkParam = extra.checkParam,
    secretGen = extra.secretGen,
    updateLastMove = extra.updateLastMove;

// joinGame function
module.exports = function(res, q, s_t){

  if(!checkParam("id", q) || !checkParam("name", q) ){
    ret(res, err(101));
  } else {

    // get all games and cycle through
    db.games.find({id: q.id}, function(er, data){
      // If game of that ID was not found, return 107 - No such game
      if(data.length === 0){
        ret(res, err(107));
      } else {
        var game = data[0];

        // Check is there only one player
        if(game.player.length != 1){
           ret(res, err(108));
        } else {

          // Check is the game private
          if(game.private == 1){

            //Check the pin
            if(!checkParam("pin", q)){
              ret(res, err(100, "Private Game requires PIN"));
            } else {

              if(q.pin == game.pin){
                performInsertion(res, q, game);
              } else {
                ret(res, err(100, "Incorrect PIN"));
              }
            }

          } else {
            performInsertion(res, q, game);
          }
        }
      }

    });
  }

};

// Function to send to the player when we got successfully inserted into the database
var insertSuccess = function(res, newPlayer){
  ret(res, {"status": "okay", "secret": newPlayer.secret, "letter": newPlayer.letter});
};


// Function to perform insertion, takes in
//    res (object of current HTTP connection),
//    q (object containing the parameters) and
//    game (object containing current game)
var performInsertion = function(res, q, game){
  // Initialize new player data
  var newPlayer = {
    name: q.name,
    letter: (game.player[0] == 1) ? 2 : 1,
    secret: secretGen(),
  };

  // Change the time of last move
  updateLastMove(game.id);

  // Add the new player and send the data to the player on success
  db.games.update({ id: game.id }, {
    $push: { player: newPlayer }
  }, insertSuccess(res, newPlayer));
};


// Export the functions for testing
exports.insertSuccess = insertSuccess;
exports.performInsertion = performInsertion;
