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

void finishgame(string p1, string p2)
{
    getData("move?id=" + p2 + "&position=5");
    getData("move?id=" + p1 + "&position=1");
    getData("move?id=" + p2 + "&position=0");
    getData("move?id=" + p1 + "&position=7");
}

void drawgame(string p1, string p2)
{
     getData("move?id=" + p1 + "&position=0");
     getData("move?id=" + p2 + "&position=1");
     getData("move?id=" + p1 + "&position=2");
     getData("move?id=" + p2 + "&position=4");
     getData("move?id=" + p1 + "&position=7");
     getData("move?id=" + p2 + "&position=6");
     getData("move?id=" + p1 + "&position=8");
     getData("move?id=" + p2 + "&position=5");
     getData("move?id=" + p1 + "&position=3");
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
    serverResponse = getData("newGame?name=test1");
    response = processJson(serverResponse);
    string gameid = response.id;
    string gameid2;
    int turn = response.letter;
    if (response.status == "okay" and (response.letter == 1 or response.letter == 2)) {
        cout << "newGame request : Passed" << endl;
    } else {
        cout << "newGame request : Failed" << endl;
    }
    serverResponse = getData("next?id=wrong");
    response = processJson(serverResponse);
    if (response.status == "error" and response.code == 100 and response.message == "Other error") {
        cout << "next request with invalid game id : Passed" << endl;
    } else {
        cout << "next request with invalid game id : Failed" << endl;
    }
    serverResponse = getData("move?id=wrong&position=5");
    response = processJson(serverResponse);
    if (response.status == "error" and response.code == 100 and response.message == "Other error") {
        cout << "move request with invalid game id : Passed" << endl;
    } else {
        cout << "move request with invalid game id : Failed" << endl;
    }
    //Create a new player to play if our current gameid isn't a player 1
    if (turn != 1) {
        serverResponse = getData("newGame?name=test2");
        response = processJson(serverResponse);
        gameid = response.id;
        serverResponse = getData("newGame?name=test3");
        response = processJson(serverResponse);
        gameid2 = response.id;
    } else {
        serverResponse = getData("newGame?name=test2");
        response = processJson(serverResponse);
        gameid2 = response.id;
    }
    serverResponse = getData("move?id=" + gameid + "&position=-1");
    response = processJson(serverResponse);
    if (response.status == "error" and response.code == 106 and response.message == "Invalid move") {
        cout << "move request with out of bounds move : Passed" << endl;
    } else {
        cout << "move request with out of bounds move : Failed" << endl;
    }
    serverResponse = getData("move?id=" + gameid2 + "&position=4");
    response = processJson(serverResponse);
    if (response.status == "error" and response.code == 105 and response.message == "Not players turn") {
        cout << "move request with not players turn : Passed" << endl;
    } else {
        cout << "move request with not players turn : Failed" << endl;
    }
    serverResponse = getData("move?id=" + gameid + "&position=4");
    response = processJson(serverResponse);
    if (response.status == "okay") {
        cout << "move request with valid move : Passed" << endl;
    } else {
        cout << "move request with valid move : Failed" << endl;
    }
    serverResponse = getData("next?id=" + gameid);
    response = processJson(serverResponse);
    if (response.status == "okay" and response.turn == 2) {
        cout << "next request valid : Passed" << endl;
    } else {
        cout << "next request valid : Failed" << endl;
    }
    finishgame(gameid, gameid2);
    serverResponse = getData("next?id=" + gameid);
    response = processJson(serverResponse);
    if (response.status == "okay" and response.winner == 1) {
        cout << "next request winning game : Passed" << endl;
    } else {
        cout << "next request winning game : Failed" << endl;
    }
    serverResponse = getData("newGame?name=test4");
    response = processJson(serverResponse);
    gameid = response.id;
    serverResponse = getData("newGame?name=test5");
    response = processJson(serverResponse);
    gameid2 = response.id;
    drawgame(gameid, gameid2);
    serverResponse = getData("next?id=" + gameid);
    response = processJson(serverResponse);
    if (response.status == "okay" and response.winner == 0) {
        cout << "next request drawing game : Passed" << endl;
    } else {
        cout << "next request drawing game : Failed" << endl;
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
