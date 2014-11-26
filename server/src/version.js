var config = require('../config.json'),
	ret = require('./ret.js');

// Returns version on request
module.exports = function(res){
  ret(res, {'status':'okay','version':config.version});
};
