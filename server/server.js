// Include neccessary packages
var http = require('http'),
    url = require('url');

// Declare the return object. Global as functions use it
var ret = {};

// The game "database". Stores all games, users, boards and moves.
// DATA LOST ON RESTART
var game = {
  // The total amount of players playing the game
  players: 0,

  // Current games
  games: []
};

// Create the server
http.createServer( function(req , res){
  // Respond with HTTP status 200 OK, and set the content-type to json
  res.writeHead(200, {'Content-Type': 'application/json'});

  // Parse the URL to get the GET requests
  var get = url.parse(req.url, true);

  // Declare the query and pathname
  var q = get.query,
      p = get.pathname;

  // Check is the action given
  if(p === "/"){
    err(103);

  // Check are any parameters specified
  } else if(Object.getOwnPropertyNames(q).length === 0){
    err(101);

  // If everything is correct, proceed.
  } else {
    switch(p){
      // Do this on new Game
      case '/newGame':
        newGame(q);
        break;

      // Do this on next
      case '/next':
        next(q);
        break;

      // Do this on move
      case '/move':
        move(q);
        break;

      // If the request is not found, return Error 103
      default:
        err(103);
        break;
    }
  }


  // Return the finished JSON result and clear the result
  res.end( JSON.stringify(ret) );
  ret = {};

// Set the server port
}).listen(1337);










////////////////////////////////////
//    ALL NECCESSARY FUNCTIONS    //
////////////////////////////////////




// MAIN FUNCTIONS //


// newGame function
function newGame(q){

  // Check is the passed request "name"
  if(!checkParam("name", q)){
    err(102);

  // If the passed parameter is name, but its empty, return error 101
  } else if(q.name.length === 0){
    err(101);

  // If everything is fine, continue
  } else {

    // Join the game, or make a new one if nowhere to join
    var gm = joinGame(q);

    // Return data
    ret.status = "okay";
    ret.id = gm.id;
    ret.letter = gm.letter;
  }
}

// next function
function next(q){

  // Check is the passed request "id"
  if(!checkParam("id", q)){
    err(102);

  // If the passed parameter is id, but its empty, return error 101
  } else if(q.id.length === 0){
    err(101);

  // If everything is right, continue
  } else {

    // Get the game status
    var gs = gameStatus(q);

    // If game id is was not found, output error 100
    if(gs == -1){
      err(100);

    // If everything is fine, continue
    } else {
      ret.status = "okay";
      ret.board = gs.board;

      // If there is a winner, output that
      if(gs.winner != -1){
        ret.winner = gs.winner;
      } else {
        ret.turn = gs.turn;
      }
    }


  }
}


// Move function
function move(q){

  // Check are there 2 parameters
  if(Object.getOwnPropertyNames(q).length !== 2){
    err(101);

  // If 2 parameters are given, continue
  } else {

    // Check are the 2 parameters id and position
    if(!checkParam("id", q) || !checkParam("position", q)){
      err(102);

    // Check are is any parameter empty
    } else if(q.id.length === 0 || q.position.length === 0){
      err(101);

    // If everything is right, continue
    } else {


        // Do the move
        var dm = doMove(q);

        // If not found, send other error
        if(dm == -1){
          err(100);

        // Send invalid move
        } else if(dm == 0){
          err(106)

        // Send not player's turn
        } else if(dm == 1){
          err(105);
        } else {
          ret.status = "okay";
        }

    }
  }
}










// SECONDARY "WORKER" FUNCTIONS //

// Function make for joining games
function joinGame(q){

  // Counter
  var i = 0;

  //Make a game object
  var gameObj = {

    // Store each player
    player: [
      {
        name: "",
        id: null,
      },
      {
        name: "",
        id: null,
      }
    ],

    // The game board
    board: [0,0,0,0,0,0,0,0,0],

    // Who is the next player do to the movement
    next: 1,

    // Do a check is the game finished
    finished: false
  };

  // If games exists, check does user exist
  if(game.games.length > 0){

    // Cycle through all current games
    for(i = 0; i < game.games.length; i++){

      // Make the g the current game
      var g = game.games[i];

      // Check is the player already in the game (for x)
      if(g.player[0].name === q.name){
        return { id: "game-"+g.player[0].id, letter: 1 };

      // Check is the player already in the game (for x)
      } else if(g.player[1].name === q.name){
        return { id: "game-"+g.player[1].id, letter: 2 };

      // Check is the second player empty. If it is, play as it
      } else if(g.player[1].name === ""){
        g.player[1].name = q.name;
        g.player[1].id = game.players++;

        return { id: "game-"+g.player[1].id, letter: 2 };
      }

    }
  }


  // If no places are available to fill, make a new game
  gameObj.player[0].name = q.name;
  gameObj.player[0].id = game.players++;


  // Add the new player to the game
  game.games.push(gameObj);

  // Return the new data
  return {id: "game-"+gameObj.player[0].id, letter: 1};

}



// Get the game of the player
function getPlayerGame(q){

  //Cycle through the games to find the player
  for(var i = 0; i < game.games.length; i++){
    var g = game.games[i];
    var id = q.id.split('-')[1];

    // If player was found, return the game number
    if(g.player[0].id == id || g.player[1].id == id){
      return i;
    }
  }

  // If the player is not found, return -1
  return -1;

}


//Check the status of the game
function gameStatus(q){

  // Get the game of the player
  var g = getPlayerGame(q);

  // If player was not found, return -1
  if(g == -1){
    return -1;
  } else {
    var result = {};
    var cg = game.games[g];

    result.board = cg.board;
    result.turn = cg.next;

    var w = checkWinner(g);

    if(w != -1){
      result.winner = w;
    } else {
      result.winner = -1;
    }

    return result;

  }
}



// Check who is the winner
function checkWinner(g){

  // assign the board to b
  var b = game.games[g].board;

  // Check did 1 win
  if(

    // Horizontally
    (b[0] == b[1] && b[2] == 1)
    ||
    (b[3] == b[4] && b[5] == 1)
    ||
    (b[6] == b[7] && b[8] == 1)
    ||
    // Vertically
    (b[0] == b[3] && b[6] == 1)
    ||
    (b[1] == b[4] && b[7] == 1)
    ||
    (b[2] == b[5] && b[8] == 1)
    ||
    //Diagonally
    (b[0] == b[4] && b[8] == 1)
    ||
    (b[2] == b[4] && b[6] == 1)
  ){
    game.games[g].finished = true;
    return 1;

  // Check did 2 win
  } else if(
    // Horizontally
    (b[0] == b[1] && b[2] == 2)
    ||
    (b[3] == b[4] && b[5] == 2)
    ||
    (b[6] == b[7] && b[8] == 2)
    ||
    // Vertically
    (b[0] == b[3] && b[6] == 2)
    ||
    (b[1] == b[4] && b[7] == 2)
    ||
    (b[2] == b[5] && b[8] == 2)
    ||
    //Diagonally
    (b[0] == b[4] && b[8] == 2)
    ||
    (b[2] == b[4] && b[6] == 2)
  ){
    game.games[g].finished = true;
    return 2;

  // If no win
  } else {

    // Check are there any 0s. If there are it means game is not finished
    for(var i = 0; i < b.length; i++){
      if(b[i] == 0){
        return -1;
      }
    }

    // Otherwise return 0 - draw
    game.games[g].finished = true;
    return 0;
  }
}


// Function to check are the request parameters ok
function checkParam(param, q){
  if(Object.getOwnPropertyNames(q).indexOf(param) == -1){
    return false;
  } else {
    return true;
  }
}


// doMove function
function doMove(q){
  // Get the player's game
  var g = getPlayerGame(q);

  // Get user's id
  var id = q.id.split('-')[1];

  // If the game-id doesn't have a game, give error
  if(g == -1){
    return -1;

  } else {
    // Perform a check is there a winner already
    checkWinner(g);
    if(game.games[g].finished){
      return 0;

    // If there isn't allow user to make a move
    } else {
      // Get player's letter
      if(game.games[g].player[0].id == id){
        var l = 1;
      } else {
        var l = 2;
      }

      // If its not player's turn, send 1
      if(l != game.games[g].next){
        return 1;
      }

      // Try to make a move
      if(game.games[g].board[q.position] === 0){

        //If successful, enter the position
        game.games[g].board[q.position] = l;

        // Change the next player to do a move
        if(l == 1){
          game.games[g].next = 2;
        } else {
          game.games[g].next = 1;
        }

        // Return 2 if everything succeedes
        return 2;

      // If space is occupied send 0
      } else {
        return 0;
      }
    }
  }
}









// ERROR HANDLING //

// Error handling
function err(c){
  ret.status = "error";
  ret.code = c;
  switch(c){
    case 100:
      ret.message = "Other Error";
      break;

    case 101:
      ret.message = "Missing parameter in request";
      break;

    case 102:
      ret.message = "Unknown parameter in request";
      break;

    case 103:
      ret.message = "Unknown request";
      break;

    case 104:
      ret.message = "Server not ready or busy";
      break;

    case 105:
      ret.message = "Not players turn";
      break;

    case 106:
      ret.message = "Invalid move";
      break;
  }
}
