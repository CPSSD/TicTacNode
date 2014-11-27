var db = require('./db.js'),
    ret = require('./ret.js'),
    extra = require('./extra.js'),
    err = require('./err.js');

var checkParam = extra.checkParam,
    paramsLength = extra.paramsLength;
    secretGen = extra.secretGen;

// startGame function
module.exports = function(res, q, s_t){

  var paramsCheck = checkParameters(q);

  if(paramsCheck != 1){
    ret(res, err(paramsCheck));
  } else {

    var desc = unescape(q.description);
    var lett = (q.letter == 2 || q.letter == 'o') ? 2 : 1;
    var loc_id = (new Date().getTime()).toString()+Math.floor( Math.random()*100 );
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

      // Add an extra minute of waiting when starting the game
      last_move: s_t+3,
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
