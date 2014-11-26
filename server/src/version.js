var config = require('../config.json'),
	ret = require('./ret.js');

// Returns version on request
module.exports = function(res){
  ret(res, {'status':'okay', 'major': config.version.major, 'minor': config.version.minor });
};
