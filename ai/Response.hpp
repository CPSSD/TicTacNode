// Response.hpp
// The Response class will parse the JSON responses.

#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

class Response
{
	public:
		std::string status;		/**< Whether the request was good or bad. */
		std::string id;			/**< The game ID. */
		int letter;				/**< The player's letter. 1=X and 2=O. */
		std::vector<int> board;	/**< Vector representation of the game board. 1=X and 2=O. */
		int turn;				/**< The letter which has the move. 1=X and 2=O. */
		int winner;				/**< The letter which has won the game. -1=incomplete, 0=draw, 1=X, and 2=O. */
		int errorCode;			/**< The error code returned from a bad request. */
		std::string message;	/**< The error message returned from a bad request. */
	
		/** Takes a std::string representation of a JSON object and
		 * parses it to get the relevant information. */
		Response(std::string input);
		
		/** Parses a string representation of the board into a vector representation. */
		void parseBoard(boost::property_tree::ptree& pt);
};

#endif
