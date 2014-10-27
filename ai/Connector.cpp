// Connector.cpp
// The connector class will manage all HTTP GET requests to the server.

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <curl/curl.h>
#include "Connector.hpp"

/* Callback function that will store the received data in a string. */
size_t Connector::writeCallback(char* ptr, size_t size, size_t nmemb, void* data)
{
	((std::string*)data)->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

Connector::Connector(std::string newAddress)
{
	curl = curl_easy_init();
	address = newAddress;
}

std::string Connector::newGame(std::string name)
{
	std::string replyJSON;
	std::string requestAddress = address+"/newGame?name="+name;
	
	curl_easy_setopt(curl, CURLOPT_URL, requestAddress.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &replyJSON);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_perform(curl);
    curl_easy_reset(curl);
    
    return replyJSON;
}

std::string Connector::next(std::string gameID)
{
	std::string replyJSON;
	std::string requestAddress = address+"/next?id="+gameID;
	
	curl_easy_setopt(curl, CURLOPT_URL, requestAddress.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &replyJSON);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_perform(curl);
    curl_easy_reset(curl);
    
    return replyJSON;
}
