
var test = require('unit.js');
var main = require('./server.js');
var http = require('http');
var request = require('request');

var errors = ["Other error", "Missing parameter in request", "Unknown parameter in request", "Unknown request", "Server not ready or busy", "Not players turn", "Invalid move"];

describe('Test Suite', function(){
  describe('Error Handling', function(){
    // just for example of tested value
    for (var i = 0; i < errors.length; i++) {
        it(errors[i], function(){
            test.assert(main.err(100 + i) == errors[i]);
        });
    }
  });
  describe('Server Requests', function(){
      it('Empty request', function() {
          request.get('http://localhost:1337',  function (err, res, body){
              test.assert(body == "{\"status\":\"error\",\"code\":103,\"message\":\"Unknown request\"}");
          });
      });
      it('Missing parameter request', function() {
          request.get('http://localhost:1337/newGame',  function (err, res, body){
              test.assert(body == "{\"status\":\"error\",\"code\":101,\"message\":\"Missing parameter in request\"}");
          });
      });
      it('Unknown parameter request', function() {
          request.get('http://localhost:1337/newGame?nam=test',  function (err, res, body){
              test.assert(body == "{\"status\":\"error\",\"code\":102,\"message\":\"Unknown parameter in request\"}");
          });
      });
      it('newGame', function() {
          request.get('http://localhost:1337/newGame?name=test',  function (err, res, body){
              var myObject = JSON.parse(body);
              test.must(myObject.status).equal('okay');
              test.must(myObject.id).be.a.string();
              test.assert(myObject.letter == 1 || myObject.letter == 2);
              test.must(Object.getOwnPropertyNames(myObject).length == 3);
          });
          request.get('http://localhost:1337/newGame?name=test2');
      });
      it('next', function() {
          request.get('http://localhost:1337/next?id=game-1',  function (err, res, body){
              var myObject = JSON.parse(body);
              test.must(myObject.status).equal('okay');
              test.assert(myObject.turn == 1 || myObject.turn == 2);
              test.assert(myObject.board);
              test.must(Object.getOwnPropertyNames(myObject).length == 3);
          });
      });
      it('move', function() {
          request.get('http://localhost:1337/move?id=game-1&position=1',  function (err, res, body){
              var myObject = JSON.parse(body);
              test.must(myObject.status).equal('okay');
              test.must(Object.getOwnPropertyNames(myObject).length == 1);
          });
      });
  });
  describe('checkWinner function tests', function() {
      it('Game not complete', function() {
         main.game.games[0].board = [0, 0, 0, 0, 0, 0, 0, 0, 0];
         test.assert(main.checkWinner(0) == -1);
      });
      it('Draw', function() {
         main.game.games[0].board = [1, 2, 1, 1, 2, 2, 2, 1, 1];
         test.assert(main.checkWinner(0) == 0);
      });
      it('Row Win', function() {
         main.game.games[0].board = [1, 1, 1, 1, 2, 2, 2, 1, 1];
         test.assert(main.checkWinner(0) == 1);
      });
      it('Column Win', function() {
         main.game.games[0].board = [1, 2, 2, 1, 2, 2, 1, 2, 1];
         test.assert(main.checkWinner(0) == 1);
      });
      it('Diagnol Win', function() {
         main.game.games[0].board = [1, 2, 2, 2, 1, 2, 2, 1, 1];
         test.assert(main.checkWinner(0) == 1);
      });
  });
  describe('doMove fucntion tests', function() {
      it('Game does not exist', function() {
         test.assert(main.doMove({id : 'game-1000', position : 1}) == -1);
      });
      it('Game finished', function() {
         test.assert(main.doMove({id : 'game-1', position : 1}) == 0);
      });
      it('Not players move', function() {
         main.game.games[0].board = [0, 0, 0, 0, 1, 0, 0, 0, 0];
         main.game.games[0].finished = false;
         main.game.games[0].next = 2;
         test.assert(main.doMove({id : 'game-1', position : 1}) == 1);
      });
      it('Space occupied', function() {
         main.game.games[0].board = [0, 0, 0, 0, 1, 0, 0, 0, 0];
         main.game.games[0].finished = false;
         main.game.games[0].next = 2;
         test.assert(main.doMove({id : 'game-2', position : 4}) == 0);
      });
      it('Sucess', function() {
         main.game.games[0].board = [0, 0, 0, 0, 1, 0, 0, 0, 0];
         main.game.games[0].finished = false;
         main.game.games[0].next = 2;
         test.assert(main.doMove({id : 'game-2', position : 1}) == 2);
      });
  });
});
