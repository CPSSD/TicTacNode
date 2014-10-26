#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

char boardChar(int x)
{
    if (x == 2) {
        return 'O';
    } else if (x == 1) {
        return 'X';
    }
    return ' ';
}

void printBoard(int b[9])
{
    cout << "Current board : " << endl;
    for (int i = 0; i < 3; i++) {
        cout << "-------" << endl;
        cout << "|" << boardChar(b[i*3]) << "|" << boardChar(b[i*3 + 1]) << "|" << boardChar(b[i*3 + 2]) << "|" << endl;
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

string exec(char* cmd)
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

string getData(string host, string action, string params)
{
    string command = "curl ";
    command = command + host + '/' + action + '?' + params + " -s";
    char arr[command.length()];
    for (int i = 0; i < command.length(); i++) {
        arr[i] = command[i];
    }
    return exec(arr);
}

int main()
{
    int board[] = {1, 0, 0, 1, 0, 0, 1, 0, 0};
    cout << getData("vm1.razoft.net:1337", "next", "id=game-0") << endl;
    cout << getWinner(board) << endl;
    printBoard(board);
    jsonObject x = processJson("{\"status\":\"okay\",\"board\":[0,0,0,1,0,0,0,1,0],\"turn\":1}");
    cout << "Json Example : " << endl;
    cout << x.status << endl;
    cout << x.turn << endl;
    cout << "board : " << endl;
    for (int i = 0; i < 9; i++) {
        cout << x.board[i] << endl;
    }
    return 0;
}
