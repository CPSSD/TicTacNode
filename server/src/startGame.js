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
    var loc_id = (new Date().getTime()).toString()+s_t;
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
      last_move: s_t,
      description: desc,
      private: q.private,
      pin: checkParam("pin",q) ? q.pin : null,
      id: loc_id
    };

    db.games.insert(gameObj, function(){
      db.games.find({}, function(err, game){
        for(var g in game){
          if(game[g].id === loc_id){
            ret(res, {
              status: "okay",
              id: "game-"+g,
              secret: secret,
              letter: lett
            });
          }
        }
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
