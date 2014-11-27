// Include mongojs and config file
var mongojs = require('mongojs'),
    config = require('../config.json');

// Create the database connection and export it
module.exports = mongojs(config.db.name, config.db.collections);
