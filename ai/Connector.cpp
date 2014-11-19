// Connector.cpp
// The connector class will manage all HTTP GET requests to the server.

#include <string>
#include <stdexcept>
#include <curl/curl.h>
#include "Connector.hpp"

#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

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
	CURLcode error = curl_easy_perform(curl);
	if(error != 0) {	// error code 0 is CURL_OK
		std::string description = curl_easy_strerror(error);
		throw std::runtime_error(description);
	}
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
	CURLcode error = curl_easy_perform(curl);
	if(error != 0) {	// error code 0 is CURL_OK
		std::string description = curl_easy_strerror(error);
		throw std::runtime_error(description);
	}
	curl_easy_reset(curl);
    
    return replyJSON;
}

std::string Connector::move(std::string gameID, std::string position)
{
	std::string replyJSON;
	std::string requestAddress = address+"/move?id="+gameID+"&position="+position;

	curl_easy_setopt(curl, CURLOPT_URL, requestAddress.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &replyJSON);
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
	CURLcode error = curl_easy_perform(curl);
	if(error != 0) {	// error code 0 is CURL_OK
		std::string description = curl_easy_strerror(error);
		throw std::runtime_error(description);
	}
	curl_easy_reset(curl);
    
    return replyJSON;
}
