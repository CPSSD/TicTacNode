var db = require('./db.js'),
	ret = require('./ret.js');

/**
* Returns a overview of the entire database for debugging and informational purposes
* @exports serverAdmin
**/
module.exports = function(res){
	var retObj = {};
	db.meta.findOne({}, function(err, meta){
		retObj.meta = meta;

		db.games.find({}, function(err, games){
			retObj.games = games;

			ret(res, retObj);
			retObj = {};
		});
	});
};
