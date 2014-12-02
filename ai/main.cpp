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

const int SLEEP_TIME_SECONDS = 2;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	std::string host;
	std::string name;
	int numGames;
	if(argc > 1) {
		numGames = std::atoi(argv[1]);
		if(numGames < 1) {
			numGames = 1;
		}
	} else {
		numGames = 1;
	}
	if(argc > 2) {
		host = argv[2];
	} else {
		host = "cpssd4-web.computing.dcu.ie:80";
	}
	if(argc > 3) {
		name = argv[3];
		if(name.size() == 0) {
			name = "ColinAI";
		}
	} else {
		name = "ColinAI";
	}
	
	Connector connector(host);
	std::vector<AI> games;
	
	for(int i = 0; i < numGames; i++) {
		AI ai;
		
		try {
			ai.newGame(connector, name + std::to_string(i));
		} catch(std::runtime_error re) {
			std::cerr << "Error connecting to server: " << re.what() << std::endl;
			std::exit(EXIT_FAILURE);
		}
		games.push_back(ai);
	}
	
	while(true) {
		for(unsigned int i = 0; i < games.size(); i++) {
			std::cout << "Looking at game: " << i << std::endl;
			AI* ai = &games[i];
			int next = ai->next(connector);
			if(next == ai->getLetter()) {
				int move = ai->chooseMove();
				ai->move(connector, move);
			} else if(next == 0) {
				int winner = ai->winner(connector);
				if(winner == ai->getLetter()) std::cout << "Game " << i << " won!" << std::endl;
				else if(winner == 0) std::cout << "Game " << i << " drawn." << std::endl;
				else std::cout << "Game " << i << " lost." << std::endl;
				
				// Create new game to replace the finished one.
				try {
					ai->newGame(connector, name + std::to_string(i));
				} catch(std::runtime_error re) {
					std::cerr << "Error connecting to server: " << re.what() << std::endl;
					std::exit(EXIT_FAILURE);
				}
			}
			boost::this_thread::sleep(boost::posix_time::seconds(SLEEP_TIME_SECONDS));
			std::cout << std::endl;
		}
	}
	
	return 0;
}
