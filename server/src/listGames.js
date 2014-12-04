var db = require('./db.js'),
    ret = require('./ret.js'),
    extra = require('./extra.js'),
    err = require('./err.js');

/**
 * Lists all current games
 * @exports listGames
**/
module.exports = function(res, q, s_t){
  db.games.find({ finished: false, player: { $size: 1 } }, function(er, dataa){
    var games = [];

    for(var c in dataa){
      var data = dataa[c];
      var game = {
        id: data.id,
        name: data.player[0].name,
        description: data.description,
        letter: data.player[0].letter == 1 ? 2 : 1,
        private: data.private
      };

      games.push(game);
      game = {};
    }

    ret(res, { "status":"okay", "games": games });
  });
};
