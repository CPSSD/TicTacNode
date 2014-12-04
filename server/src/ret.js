/**
 * Returns the finished status to the player
 * @exports ret
**/
module.exports = function(res, response){
    res.writeHead(200, {'Content-Type': 'application/json', 'Access-Control-Allow-Origin': '*'});
    res.end(JSON.stringify(response));
};
