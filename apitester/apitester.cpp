#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/thread/thread.hpp>
#include <boost/foreach.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE api_tests
#define BOOST_TEST_MAIN
#define BOOST_TEST_LOG_LEVEL all
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <sstream>
#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <vector>

using namespace std;

string host = "cpssd4-web.computing.dcu.ie:80";

struct jsonObject
{
    string status;
    int code;
    string message;
    string id;
    string secret;
    int versionMajor;
    int versionMinor;
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
    ret.secret = pt.get("secret", "");
    ret.letter = pt.get("letter", 0);
    ret.versionMajor = pt.get("major", 0);
    ret.versionMinor = pt.get("minor", 0);
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

BOOST_AUTO_TEST_CASE(version)
{
    if(boost::unit_test::framework::master_test_suite().argc > 1) {
        host = boost::unit_test::framework::master_test_suite().argv[1];
    }
    string serverResponse = getData("/version");
    jsonObject response = processJson(serverResponse);
    
    cout << "Testing: correct version" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.versionMajor == 2);
    BOOST_CHECK(response.versionMinor == 2);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(emptyRequest)
{
    string serverResponse = getData("");
    jsonObject response = processJson(serverResponse);
    
    cout << "Testing: empty request" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "error");
    BOOST_CHECK(response.code == 103);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(missingParameter)
{
    string serverResponse = getData("/startGame?");
    jsonObject response = processJson(serverResponse);
    
    cout << "Testing: request with missing parameter" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "error");
    BOOST_CHECK(response.code == 101);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(startGameRequest)
{
    string serverResponse = getData("/startGame?name=test1&description='Test'&letter=1&private=0");
    jsonObject response = processJson(serverResponse);
    
    cout << "Testing: valid startGame request" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "okay");
    BOOST_CHECK(response.letter == 1 || response.letter == 2);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(startGameInvalidPIN)
{
    string serverResponse = getData("/startGame?name=test1&description='Test'&letter=1&private=1&pin=12345");
    jsonObject response = processJson(serverResponse);
    
    cout << "Testing: startGame request with invalid PIN" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "error");
    BOOST_CHECK(response.code == 100);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(startGameValidPIN)
{
    string serverResponse = getData("/startGame?name=test1&description='Test'&letter=1&private=1&pin=1234");
    jsonObject response = processJson(serverResponse);
    
    cout << "Testing: startGame request with valid PIN" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "okay");
    BOOST_CHECK(response.letter == 1 || response.letter == 2);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(validJoinGameRequest)
{
    string serverResponse = getData("/startGame?name=test1&description='Test'&letter=1&private=0");
    jsonObject response = processJson(serverResponse);
    
    string id = response.id;
    serverResponse = getData("/joinGame?id="+id+"&name=test1");
    response = processJson(serverResponse);
    
    cout << "Testing: valid public joinGame request" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "okay");
    BOOST_CHECK(response.letter == 1 || response.letter == 2);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(joinGameRequestIncorrectPIN)
{
    string serverResponse = getData("/startGame?name=test1&description='Test'&letter=1&private=1&pin=1234");
    jsonObject response = processJson(serverResponse);
    
    string id = response.id;
    serverResponse = getData("/joinGame?id="+id+"&name=test1&pin=4723");
    response = processJson(serverResponse);
    
    cout << "Testing: private joinGame request with incorrect PIN" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "error");
    BOOST_CHECK(response.code == 100);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(joinGameRequestCorrectPIN)
{
    string serverResponse = getData("/startGame?name=test1&description='Test'&letter=1&private=1&pin=1234");
    jsonObject response = processJson(serverResponse);
    
    string id = response.id;
    serverResponse = getData("/joinGame?id="+id+"&name=test1&pin=1234");
    response = processJson(serverResponse);
    
    cout << "Testing: private joinGame request with correct PIN" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "okay");
    BOOST_CHECK(response.letter == 1 || response.letter == 2);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(nextRequestInvalidID)
{
    string serverResponse = getData("/next?secret=wrong");
    jsonObject response = processJson(serverResponse);
    
    cout << "Testing: next request with invalid secret" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "error");
    BOOST_CHECK(response.code == 107);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(moveRequestInvalidID)
{
    string serverResponse = getData("/move?secret=wrong&position=5");
    jsonObject response = processJson(serverResponse);
    
    cout << "Testing: move request with invalid secret" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "error");
    BOOST_CHECK(response.code == 107);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(outOfBoundsMove)
{
    string serverResponse = getData("/startGame?name=outOfBoundsTest&description='Test'&letter=1&private=0");
    jsonObject response = processJson(serverResponse);
    
    serverResponse = getData("/move?secret=" + response.secret + "&position=-1");
    response = processJson(serverResponse);
    
    cout << "Testing: move request out of bounds" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "error");
    BOOST_CHECK(response.code == 106);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(moveRequestNotTurn)
{
    string serverResponse = getData("/startGame?name=moveNotTurnTest&description='Test'&letter=2&private=0");
    jsonObject response = processJson(serverResponse);
    
    serverResponse = getData("/move?secret=" + response.secret + "&position=1");
    response = processJson(serverResponse);
    
    cout << "Testing: move request not player's turn" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "error");
    BOOST_CHECK(response.code == 105);
    cout << endl;
}

BOOST_AUTO_TEST_CASE(validMove)
{
    string serverResponse = getData("/startGame?name=outOfBoundsTest&description='Test'&letter=1&private=0");
    jsonObject response = processJson(serverResponse);
    
    serverResponse = getData("/move?secret=" + response.secret + "&position=0");
    response = processJson(serverResponse);
    
    cout << "Testing: valid move request" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "okay");
    cout << endl;
}

BOOST_AUTO_TEST_CASE(validNext)
{
    string serverResponse = getData("/startGame?name=outOfBoundsTest&description='Test'&letter=1&private=0");
    jsonObject response = processJson(serverResponse);
    
    serverResponse = getData("/next?secret=" + response.secret);
    response = processJson(serverResponse);
    
    cout << "Testing: valid next request" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "okay");
    cout << endl;
}

BOOST_AUTO_TEST_CASE(validEndGame)
{
    string serverResponse = getData("/startGame?name=outOfBoundsTest&description='Test'&letter=1&private=0");
    jsonObject response = processJson(serverResponse);
    
    serverResponse = getData("/endGame?secret=" + response.secret);
    response = processJson(serverResponse);
    
    cout << "Testing: valid endGame request" << endl;
    cout << "Returned: " << serverResponse << endl;
    BOOST_CHECK(response.status == "okay");
    cout << endl;
}
