// TicTacNode
// main.cpp

#include <iostream>
#include <string>
#include <ctime>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/thread/thread.hpp>
#include <curl/curl.h>
#include "Connector.hpp"
#include "Response.hpp"
#include "AI.hpp"

int main()
{
	srand(time(NULL));
	
	Connector connector("vm1.razoft.net:1337");
	AI colin;
	colin.newGame(connector);
	
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
