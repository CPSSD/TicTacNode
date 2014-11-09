// TicTacNode
// main.cpp

#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>
#include <cstdlib>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/thread/thread.hpp>
#include <curl/curl.h>
#include "Connector.hpp"
#include "Response.hpp"
#include "AI.hpp"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	std::string host;
	std::string name;
	if(argc > 1) {
		host = argv[1];
	} else {
		host = "vm1.razoft.net:1337";
	}
	if(argc > 2) {
		name = argv[2];
		if(name.size() == 0) {
			name = "ColinAI";
		}
	} else {
		name = "ColinAI";
	}
	
	Connector connector(host);
	AI colin;
	try {
		colin.newGame(connector, name);
	} catch(std::runtime_error re) {
		std::cerr << "Error connecting to server: " << re.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	while(colin.winner(connector) == -1) {
		int currentPlayer = colin.next(connector);
		if(currentPlayer != colin.getLetter() && currentPlayer != 0) {
			boost::this_thread::sleep(boost::posix_time::seconds(1));
		} else if(currentPlayer == colin.getLetter()) {
			int move = colin.chooseMove();
			colin.move(connector, move);
		}
	}
	if(colin.winner(connector) == 0) std::cout << "The game is a draw!" << std::endl;
	else if(colin.winner(connector) == colin.getLetter()) std::cout << "Colin won!" << std::endl;
	else if(colin.winner(connector) != colin.getLetter()) std::cout << "Colin lost!" << std::endl;
	
	return 0;
}
