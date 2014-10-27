// TicTacNode
// main.cpp

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <curl/curl.h>
#include "Connector.hpp"

int main()
{
	Connector connector("vm1.razoft.net:1337");
	std::string gameResponse = connector.newGame("aitest2");
	std::string nextResponse = connector.next("game-4");
	
	std::cout << gameResponse << std::endl;
	std::cout << nextResponse << std::endl;
	return 0;
}
