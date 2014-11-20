// Include mongojs and config file
var mongojs = require('mongojs'),
    config = require('../config.json');

// Export the database connections
exports = mongojs(config.db.name, config.db.collections);
