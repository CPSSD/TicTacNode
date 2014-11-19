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

char boardChar(int x, char def)
{
    if (x == 2) {
        return 'O';
    } else if (x == 1) {
        return 'X';
    }
    return def;
}

char toChar(int x)
{
    return '0' + x;
}

void printBoard(int b[9], bool forSelection)
{
    cout << "Current board : " << endl;
    for (int i = 0; i < 3; i++) {
        cout << "-------" << endl;
        if (forSelection == false) {
            cout << "|" << boardChar(b[i*3], ' ') << "|" << boardChar(b[i*3 + 1], ' ') << "|" << boardChar(b[i*3 + 2], ' ') << "|" << endl;
        } else {
            cout << "|" << boardChar(b[i*3], toChar(i*3 + 1)) << "|" << boardChar(b[i*3 + 1], toChar(i*3 + 2)) << "|" << boardChar(b[i*3 + 2], toChar(i*3 + 3)) << "|" << endl;
        }
    }
    cout << "-------" << endl;
}

int getWinner(int b[9])
{
    //rows and coloums
    for (int i = 0; i < 3; i++) {
        if (b[i*3] == b[i*3 + 1] && b[i*3] == b[i*3 + 2] && b[i*3] > 0) {
            return b[i*3];
        }
        if (b[i] == b[i + 3] && b[i] == b[i + 6] && b[i] > 0) {
            return b[i];
        }
    }
    //diagnals
    if (b[0] == b[4] && b[0] == b[8] && b[0] > 0) {
        return b[0];
    }
    if (b[2] == b[4] && b[2] == b[6] && b[2] > 0) {
        return b[2];
    }
    //is the game over?
    for (int i = 0; i < 9; i++) {
        if (b[i] == 0) {
            return -1;
        }
    }
    //game is a draw
    return 0;
}

bool validMove(int board[9], int pos)
{
    if (pos >= 0) {
        if (pos < 9) {
            if (board[pos] == 0) {
                return true;
            }
        }
    }
    return false;
}

struct generalRequest
{
    string status;
    int code;
    string message;
    string id;
    string secret;
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

generalRequest processJson(string x)
{
    stringstream ss;
    ss << x;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);
    generalRequest ret;
    ret.status = pt.get("status", "");
    ret.code = pt.get("code", 0);
    ret.message = pt.get("message", "");
    ret.id = pt.get("id", "");
    ret.secret = pt.get("secret", "");
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

void handleError(generalRequest x)
{
    cout << "status : " << x.status << endl;
    if (x.code > 0) {
        cout << "code : " << x.code << endl;
    }
    if (x.message != "") {
        cout << "message : " << x.message << endl;
    }
}

char getXOFromInt(int x)
{
    if (x == 1) {
        return 'X';
    } else {
        return 'O';
    }
}

void handleWinner(int player, int winner)
{
    if (winner == 0) {
        cout << "The game has ended in a draw" << endl;
    } else if (winner == player) {
        cout << "You have won the game, congratulations!" << endl;
    } else {
        cout << "You have lost the game, better luck next time" << endl;
    }
}

int getOppsite(int x)
{
    if (x == 1) {
        return 2;
    }
    return 1;
}

bool makeMove(int player, int board[9], string secret)
{
    string serverResponse;
    generalRequest response;
    cout << "It is your turn, select a move to make or enter 10 to end the game : " << endl;
    printBoard(board, true);
    int m;
    while (true) {
        cin >> m;
        if (validMove(board, m - 1)) {
            board[m - 1] = player;
            serverResponse = getData("/move?secret=" + secret + "&position=" + toChar(m - 1));
            response = processJson(serverResponse);
                if (response.status != "okay") {
                    handleError(response);
                }
            printBoard(board, false);
            cout << "Waiting for other player to move" << endl;
            return true;
        } else if (m == 10) {
            serverResponse = getData("/endGame?secret=" + secret);
            response = processJson(serverResponse);
            if (response.status != "okay") {
                handleError(response);
            }
            return false;
        } else {
            cout << "Invalid Move" << endl;
        }
    }
}

int tryNext(int player, int board[9], string secret)
{
    string serverResponse = getData("/next?secret=" + secret);
    generalRequest response = processJson(serverResponse);
    if (response.status == "okay") {
        if (response.winner >= 0) {
            handleWinner(player, response.winner);
            return 3;
        } else {
            if (response.turn == player) {
                for (int i = 0; i < 9; i++) {
                    board[i] = response.board[i];
                }
                return 2;
            } else {
                boost::this_thread::sleep(boost::posix_time::seconds(1));
                return 1;
            }
        }
    } else {
        handleError(response);
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        return 1;
    }
}

void runGame(int player, int board[9], int wMove, string secret)
{
    while (true) {
        if (getWinner(board) >= 0) {
            handleWinner(player, getWinner(board));
            break;
        } else {
            if (wMove == player) {
                bool moveMade = makeMove(player, board, secret);
                if (moveMade == false) {
                    return;
                }
                wMove = getOppsite(wMove);
            } else {
                int meNext = tryNext(player, board, secret);
                if (meNext == 2) {
                    wMove = getOppsite(wMove);
                } else if (meNext == 3) {
                    return;
                }
            }
        }
    }
}

bool validPin(string pin)
{
    if (pin.length() != 4) {
        return false;
    }
    for (int i = 0; i < pin.length(); i++) {
        if (isdigit(pin[i]) == false) {
            return false;
        }
    }
    return true;
}

string convertSpaces(string x)
{
    for (int i = 0; i < x.length(); i++) {
        if (x[i] == ' ') {
            x[i] = '+';
        }
    }
    return x;
}

string getGameRequest(string name)
{
    cout << "Please enter a game description : " << endl;
    string desc;
    cin >> noskipws() >> desc;
    char anwser;
    cout << "Would you like to play as X or O? : " << endl;
    cin >> skipws() >> anwser;
    string letter;
    if (anwser == 'X') {
        letter = "1";
    } else {
        letter = "2";
    }
    cout << "Would you like this game to be private? y/n" << endl;
    cin >> anwser;
    if (tolower(anwser) == 'y') {
        cout << "Please enter a 4 digit pin : " << endl;
        string pin;
        while (true) {
            cin >> pin;
            if (validPin(pin)) {
                return "/startGame?name=" + name + "&description=" + convertSpaces(desc) + "&letter=" + letter + "&private=1" + "&pin=" + pin;
            } else {
                cout << "Invalid pin" << endl;
            }
        }
    }
    return "/startGame?name=" + name + "&description=" + convertSpaces(desc) + "&letter=" + letter + "&private=0";
}

void startGame(string name)
{
    string serverResponse = getData(getGameRequest(name));
    generalRequest response = processJson(serverResponse);
    if (response.status == "okay") {
        string secret = response.secret;
        int player = response.letter;
        cout << "Started game with id " << response.id << ". You are playing as " << getXOFromInt(response.letter) << endl;
        int wMove = 1;
        int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        runGame(player, board, wMove, secret);
    } else {
        handleError(response);
    }
}

struct gameObject
{
    string id;
    string name;
    string description;
    int letter;
    int isPrivate;
};


vector<gameObject> getGames(boost::property_tree::ptree pt)
{
    vector<gameObject> ret;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("games")) {
        gameObject x;
        x.id = v.second.get<string>("id");
        x.name = v.second.get<string>("name");
        x.description = v.second.get<string>("description");
        x.letter = v.second.get<int>("letter");
        x.isPrivate = v.second.get<int>("private");
        ret.push_back(x);
    }
    return ret;
}

void printList(vector<gameObject> games)
{
    cout << "(0) = Go Back" << endl;
    for (int i = 0; i < games.size(); i++) {
        cout << "(" << i + 1 << ") = " << games[i].id << ". Started by " << games[i].name << ". Description : " << games[i].description << ". Can join as " << getXOFromInt(games[i].letter);
        if (games[i].isPrivate == 1) {
            cout << ". This is a private game";
        }
        cout << endl;
    }
}

void tryJoinGame(vector<gameObject> games, int n, string name)
{
    string pin;
    if (games[n].isPrivate == 1) {
        cout << "Attempting to join a private game, please enter the 4 digit pin" << endl;
        cin >> pin;
        if (validPin(pin) == false) {
            cout << "Invalid pin" << endl;
            return;
        }
        string serverResponse = getData("/joinGame?id=" + games[n].id + "&name=" + name + "&pin=" + pin);
        generalRequest response = processJson(serverResponse);
        int player = response.letter;
        string secret = response.secret;
        if (response.status == "okay") {
            string serverResponse = getData("/next?secret=" + secret);
            runGame(player, response.board, response.turn, secret);
        } else {
            handleError(response);
        }
    } else {
        string serverResponse = getData("/joinGame?id=" + games[n].id + "&name=" + name);
        generalRequest response = processJson(serverResponse);
        int player = response.letter;
        string secret = response.secret;
        if (response.status == "okay") {
            string serverResponse = getData("/next?secret=" + secret);
            runGame(player, response.board, response.turn, secret);
        } else {
            handleError(response);
        }
    }
}

void listGames(string name)
{
    string serverResponse = getData("/listGames");
    stringstream ss;
    ss << serverResponse;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);
    string status = pt.get("status", "");
    string message = pt.get("message", "");
    int code = pt.get("code", 0);
    if (status == "okay") {
        vector<gameObject> games = getGames(pt);
        if (games.size() == 0) {
            cout << "No games available to join" << endl;
            return;
        }
        printList(games);
        int g;
        while (true) {
            cout << "Enter a game you want to join or enter 0 to go back" << endl;
            cin >> g;
            if (g == 0) {
                return;
            } else if (g > 0 and g <= games.size()) {
                tryJoinGame(games, g - 1, name);
                return;
            } else {
                cout << "Invalid response" << endl;
            }
        }
    } else {
        cout << "Got error : " << code << " , " << message << endl;
    }
}

void playGames()
{
    string name;
    cout << "Please enter your name : " << endl;
    cin >> name;
    char anwser;
    while (true) {
        cout << "Would you like to start a new game or list all available games? Enter 1 or 2. Enter 3 to exit." << endl;
        while (true) {
            cin >> anwser;
            if (anwser == '1') {
                startGame(name);
                break;
            } else if (anwser == '2') {
                listGames(name);
                break;
            } else if (anwser == '3') {
                return;
            }
            cout << "invalid response" << endl;
        }
    }
}

int main()
{
    cout << "Would you like to use the defualt host (" << host << ") or enter an alternitive? y/n" << endl;
    char a;
    cin >> a;
    if (a == 'n') {
    	cout << "Enter host name :" << endl;
    	cin >> host;
    }
    playGames();
    return 0;
}
