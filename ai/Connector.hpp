// Connector.hpp
// The connector class will manage all HTTP GET requests to the server.

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>
#include <curl/curl.h>

class Connector
{
	private:
		CURL* curl;
		std::string address;
	
		/** Callback function that will store the received data in a string. */
		static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* data);
	
	public:
		Connector(std::string newAddress);
	
		/** Function to request a new game from the server. */
		std::string newGame(std::string name);
		
		/** Function to check who currently has the move. */
		std::string next(std::string gameID);
		
		/** Function to make a move on the board. */
		std::string move(std::string gameID, std::string position);
};

#endif
