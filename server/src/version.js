var ret = require('./ret.js').ret,
    config = require('../config.json');

// Returns version on request
exports.version = function(res){
  ret(res, {'version':config.version});
};
