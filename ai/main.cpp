// TicTacNode
// main.cpp

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <curl/curl.h>
#include "Connector.hpp"
#include "Response.hpp"

int main()
{
	Connector connector("vm1.razoft.net:1337");
	std::string gameString = connector.newGame("aitest2");
	std::string nextString = connector.next("game-1827");
	
	Response gameResponse(gameString);
	std::cout << gameResponse.status << std::endl;
	std::cout << gameResponse.id << std::endl;
	std::cout << gameResponse.letter << std::endl;
	std::cout << std::endl;
	
	Response nextResponse(nextString);
	std::cout << nextResponse.status << std::endl;
	std::cout << nextResponse.errorCode << std::endl;
	for(unsigned int i = 0; i < nextResponse.board.size(); i++) {
		std::cout << nextResponse.board[i];
	}
	std::cout << std::endl;
	std::cout << nextResponse.turn << std::endl;
	
	return 0;
}
