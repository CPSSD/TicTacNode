#include <iostream>

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

int main()
{
    int board[] = {1, 0, 0, 1, 0, 0, 1, 0, 0};
    printBoard(board);
    cout << getWinner(board) << endl;
    return 0;
}
