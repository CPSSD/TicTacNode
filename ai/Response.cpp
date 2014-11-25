// Response.cpp
// The Response class will parse the JSON responses.

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "Response.hpp"

Response::Response(std::string input)
{
	std::stringstream responseStream(input);
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(responseStream, pt);
	
	status = pt.get("status", "");
	id = pt.get("id", "");
    secret = pt.get("secret", "");
	letter = pt.get("letter", 0);
	parseBoard(pt);
	turn = pt.get("turn", 0);
	winner = pt.get("winner", -1);
	errorCode = pt.get("code", 0);
	message = pt.get("message", "");
	
	/* Logs an error if encountered. More detailed error handling depends
	 * on the request made and will be covered in those functions. */
	if(status == "error") {
		std::cerr << "(EE) Response returned error code " << errorCode << ": " << message << std::endl;
	}
}

void Response::parseBoard(boost::property_tree::ptree& pt)
{
	if (pt.count("board") == 0) return;
	
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("board")) {
		board.push_back(v.second.get_value<int>());
	}
}
