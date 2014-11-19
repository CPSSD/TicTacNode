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
		int letter;	/**< 1=X, 2=O */
		int oppLetter;	/**< Tracks opponent's letter */
		std::string gameID;	/**< ID of the current game */
		std::vector<int> board;	/**< The current game board */
		
		/**
		 * @fn score
		 * @brief Calculates a score for the move.
		 * 
		 * The function returns a score based on the depth of the move 
		 * and whether the move loses, wins, or draws the game.
		 * 
		 * @param board  the board after the proposed move is made.
		 * @param depth  the current move's depth.
		 */
		int score(std::vector<int> board, int depth);
		
		/**
		 * @fn gameOver
		 * @brief Checks whether the game is over.
		 * 
		 * @param board  the game board.
		 * @return the current game state. -1 if the game is not over, 0 
		 * if the game is a draw, 1 if X wins, and 2 if O wins.
		 */
		int gameOver(std::vector<int> board);
		
		/**
		 * @fn minimax
		 * @brief Calculates the best move to make.
		 * 
		 * Uses a simple minimax algorithm to calculate the move which 
		 * maximises the AI's gains and minimises those of the opponent.
		 * 
		 * @param board  the game board.
		 * @param depth  the depth of the current move.
		 * @param currentPlayer  the player whose move it currently is in the calculation. 1=X and 2=O.
		 * @param choice  the move the AI should make, set when the search is exhausted.
		 * @return the end score of the calculation.
		 */
		int minimax(std::vector<int> board, int depth, int currentPlayer, int& choice);
	
	public:
		int getLetter();
		
		/**
		 * @fn newGame
		 * @brief Requests a new game from the server.
		 * 
		 * The function sends a request for a new game to the server and 
		 * parses the response.
		 * 
		 * @param connector  an object of the @c Connector class.
		 * @param name  a string representing the AI's player name.
		 */
		void newGame(Connector& connector, std::string name);
		
		// Check if the game is over.
		int winner(Connector& connector);
		
		// Check whose move it is.
		int next(Connector& connector);
		
		/**
		 * @fn chooseMove
		 * @brief Chooses the best move to make.
		 * 
		 * The function uses the @c score and @c minimax functions to 
		 * calculate the best move.
		 */
		int chooseMove();
		
		// Send a move to the server.
		void move(Connector& connector, int move);
};

#endif
