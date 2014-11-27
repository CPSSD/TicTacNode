var db = require('./db.js'),
    ret = require('./ret.js'),
    extra = require('./extra.js'),
    err = require('./err.js');

// listGames function
module.exports = function(res, q, s_t){
  db.games.find({}, function(err, dataa){
    var games = [];

    for(var c in dataa){
      var data = dataa[c];
      var game = {};
      if(!data.finished && data.player.length == 1){
        game.id = "game-"+c;
        game.name = data.player[0].name;
        game.letter = data.player[0].letter == 1 ? 2 : 1;
        game.private = data.private;
        game.description = data.description;

        games.push(game);
        game = {};
      }

    }

    ret(res, games);
  });
};
