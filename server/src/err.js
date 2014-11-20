// Error function
exports.err = function(c){
  var ret = {};
  ret.status = "error";
  ret.code = c;
  switch(c){
    case 100:
      ret.message = "Other error";
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

    case 107:
      ret.message = "No such game";
      break;

    case 108:
      ret.message = "Game already has two players";
      break;
  }

  return ret;
};
