var db = require('./db.js'),
    ret = require('./ret.js'),
    extra = require('./extra.js'),
    err = require('./err.js'),

    checkParam = extra.checkParam,
    updateLastMove = extra.updateLastMove;

// endGame function
module.exports = function(res, q, s_t){
  if(!checkParam("secret",q)){
    ret(res, err(101));
  } else {
    db.games.findAndModify({
      query: {"player.secret": q.secret},
      update: { $set: { winner: 0, finished: true} },
      new: true,
    }, function(er, data){
      if(data === null){
        ret(res, err(107));
      } else {
        updateLastMove(data.id);
        ret(res, {"status": "okay"});
      }
    });
  }
};
