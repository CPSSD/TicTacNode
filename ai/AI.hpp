// AI.hpp
// The AI class will decide what move to make each turn.

#ifndef AI_H
#define AI_H

#include <string>
#include <vector>
#include "Connector.hpp"
#include "Response.hpp"

class AI
{
	private:
		int letter;	// 1=X, 2=O
		std::string gameID;	// ID of the current game
		std::vector<int> board;	// The current game board
	
	public:
		int getLetter();
		
		// Start a new game on the server.
		void newGame(Connector& connector);
		
		// Check if the game is over.
		int winner(Connector& connector);
		
		// Check whose move it is.
		int next(Connector& connector);
		
		// Make a move. Returns move number.
		int move(Connector& connector);
};

#endif
