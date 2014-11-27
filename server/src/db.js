// Include mongojs and config file
var mongojs = require('mongojs'),
    config = require('../config.json');


var db = mongojs(config.db.name, config.db.collections);

// Set the index on secrets
db.games.ensureIndex( {secret: 1} );

// Export the database connection
module.exports = db;
