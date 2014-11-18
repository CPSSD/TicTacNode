// AI.hpp
// The AI class will decide what move to make each turn.

#ifndef AI_H
#define AI_H

#include <string>
#include <vector>
#include "Connector.hpp"
#include "Response.hpp"

/**
 * @class AI
 * @brief A class containing the actual logic of the AI.
 * 
 * The class will send requests through the connector to the server. It 
 * will also decide what moves to make.
 */
class AI
{
	private:
		int letter;	// 1=X, 2=O
		int oppLetter;	// Tracks opponent's letter
		std::string gameID;	// ID of the current game
		std::vector<int> board;	// The current game board
	
	public:
		int getLetter();
		
		/**
		 * @fn newGame
		 * @brief Requests a new game from the server.
		 * 
		 * The function sends a request for a new game to the server and 
		 * parses the response.
		 * 
		 * @param connector  An object of the @c Connector class.
		 * @param name  A string representing the AI's player name.
		 */
		void newGame(Connector& connector, std::string name);
		
		// Check if the game is over.
		int winner(Connector& connector);
		
		// Check whose move it is.
		int next(Connector& connector);
		
		// Decide on a move.
		int chooseMove();
		
		// Send a move to the server.
		void move(Connector& connector, int move);
};

#endif
