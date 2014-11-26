var db = require('./db.js'),
	ret = require('./ret.js');

module.exports = function(res){
	var retObj = {};
	db.meta.find({}, function(err, meta){
		retObj.meta = meta;

		db.games.find({}, function(err, games){
			retObj.games = games;

			ret(res, retObj);
		});
	});
};
