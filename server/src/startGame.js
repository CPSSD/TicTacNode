var db = require('./db.js'),
    ret = require('./ret.js'),
    extra = require('./extra.js'),
    config = require('../config.json'),
    err = require('./err.js');

var checkParam = extra.checkParam,
    paramsLength = extra.paramsLength,
    secretGen = extra.secretGen,
    updateGameID = extra.updateGameID;

// startGame function
module.exports = function(res, q, s_t){

  var paramsCheck = checkParameters(q);

  if(paramsCheck != 1){
    ret(res, err(paramsCheck));
  } else {
    updateGameID(function(curr_id){

      var desc = decodeURI(q.description);
      var lett = (q.letter == 2 || q.letter == 'o') ? 2 : 1;
      var loc_id = "game-"+curr_id;
      var secret = secretGen();

      var gameObj = {
        player: [
          {
            name: q.name,
            secret: secret,
            letter: lett
          }
        ],
        board: [0,0,0,0,0,0,0,0,0],
        next: 1,
        finished: false,
        start_time: s_t,

        // Set the timeout time when the game starts
        last_move: s_t-config.server.timeout+config.server.start_timeout,
        description: desc,
        private: q.private,
        pin: checkParam("pin",q) ? q.pin : null,
        id: loc_id
      };

      db.games.insert(gameObj, function(){
        ret(res, {
          "status": "okay",
          "id": gameObj.id,
          "secret": gameObj.player[0].secret,
          "letter": gameObj.player[0].letter
        });
        gameObj = {};
      });
    });

  }

};

function checkParameters(q){
  var n = checkParam("name",q),
      d = checkParam("description",q),
      l = checkParam("letter",q),
      pri = checkParam("private", q);

    if(n && d && l && pri){
      if(q.private == 1){
        var pi = checkParam("pin", q);
        if(pi){
          if(q.pin.length == 4){
            return 1;
          } else {
            return 101;
          }
        } else {
          return 101;
        }
      } else {
        return 1;
      }
    } else {
      return 101;
    }
}
