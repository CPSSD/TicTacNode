var config = require('../config.json'),
	ret = require('./ret.js');

/**
* REturn the current version of the server
* @exports version
**/
module.exports = function(res){
  ret(res, {'status':'okay', 'major': config.version.major, 'minor': config.version.minor });
};
