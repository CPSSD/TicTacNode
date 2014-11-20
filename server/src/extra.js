var db = require('./db.js').db;

exports.extra = {
  // Removes old games,
  removeOldGames: function(s_t){
    db.games.update(
      { "last_move": { $lt: s_t - 3 } },
      { $set: { winner: -1 } },
      function(){}
    );
  }
};
