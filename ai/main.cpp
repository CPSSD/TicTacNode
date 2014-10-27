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
	std::string JSON = connector.newGame("aitest1");
	
	std::cout << JSON << std::endl;
	return 0;
}
