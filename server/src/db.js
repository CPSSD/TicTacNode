// Include mongojs and config file
var mongojs = require('mongojs'),
    config = require('../config.json');

// Create the database connection and export it
var db = mongojs(config.db.name, config.db.collections);

db.games.ensureIndex("players");
db.games.ensureIndex("finished");
db.games.ensureIndex("id");
db.games.ensureIndex("last_move");

module.exports = db;
