#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/thread/thread.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <sstream>
#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <vector>

using namespace std;

string host = "cpssd4-web.computing.dcu.ie:80/";

struct jsonObject
{
    string status;
    int code;
    string message;
    string id;
    int letter;
    int board[9];
    int turn;
    int winner;
};

void getBoard(int b[9], boost::property_tree::ptree pt)
{
    if (pt.count("board") == 0) {
        for (int i = 0; i < 9; i++) {
            b[i] = 0;
        }
        return;
    }
    vector<int> r;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("board")) {
        r.push_back(v.second.get_value<int>());
    }
    for (int i = 0; i < 9; i++) {
        if (i < r.size()) {
            b[i] = r[i];
        } else {
            b[i] = 0;
        }
    }
}

jsonObject processJson(string x)
{
    stringstream ss;
    ss << x;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);
    jsonObject ret;
    ret.status = pt.get("status", "");
    ret.code = pt.get("code", 0);
    ret.message = pt.get("message", "");
    ret.id = pt.get("id", "");
    ret.letter = pt.get("letter", 0);
    getBoard(ret.board, pt);
    ret.turn = pt.get("turn", 0);
    ret.winner = pt.get("winner", -1);
    return ret;
}

CURL* curl = curl_easy_init();

size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* data)
{
	((std::string*)data)->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

string getData(string request)
{
    string requestAddress = host + request;
    string replyJSON;
	curl_easy_setopt(curl, CURLOPT_URL, requestAddress.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &replyJSON);
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
	curl_easy_perform(curl);
	curl_easy_reset(curl);
    return replyJSON;
}

void testServer()
{
    string serverResponse = getData("");
    jsonObject response = processJson(serverResponse);
    if (response.status == "error" and response.code == 103 and response.message == "Unknown request") {
        cout << "Empty Request : Passed" << endl;
    } else {
        cout << "Empty Request : Failed" << endl;
    }
    serverResponse = getData("newGame?");
    response = processJson(serverResponse);
    if (response.status == "error" and response.code == 101 and response.message == "Missing parameter in request") {
        cout << "Missing Parameter : Passed" << endl;
    } else {
        cout << "Missing Parameter : Failed" << endl;
    }
    serverResponse = getData("newGame?nae=test1");
    response = processJson(serverResponse);
    if (response.status == "error" and response.code == 102 and response.message == "Unknown parameter in request") {
        cout << "Unknown Parameter : Passed" << endl;
    } else {
        cout << "Unknown Parameter : Failed" << endl;
    }
}

int main()
{
    cout << "Would you like to use the defualt host (" << host << ") or enter and alternative? y/n" << endl;
    char a;
    cin >> a;
    if (a == 'n') {
    	cout << "Enter host name :" << endl;
    	cin >> host;
    }
    testServer();
    return 0;
}
