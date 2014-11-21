var db = require('./db.js');

module.exports = {
  // Removes old games,
  removeOldGames: function(s_t){
    db.games.update(
      { "last_move": { $lt: s_t - 3 } },
      { $set: { winner: -1 } },
      function(){}
    );
  },

  updateServerTime: function(){
  	db.meta.findAndModify({
  		query: {},
  		update: { $inc: { server_time: 1 } },
  		new: true,
  		upsert: true
  	});
  }
};
