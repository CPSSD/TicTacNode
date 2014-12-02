// AI.cpp
// The AI class will decide what move to make each turn.

#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include "Connector.hpp"
#include "Response.hpp"
#include "AI.hpp"

int AI::getLetter()
{
	return letter;
}

int AI::gameOver(std::vector<int> board)
{
	for(unsigned int i = 0; i < board.size(); i++) {
		if(board[i*3] == board[i*3 + 1] && board[i*3] == board[i*3 + 2] && board[i] > 0) {
			return board[i*3];
		} else if(board[i] == board[i+3] && board[i] == board[i+6] && board[i] > 0) {
			return board[i];
		} else if(board[0] == board[4] && board[0] == board[8] && board[0] > 0) {
			return board[0];
		} else if(board[2] == board[4] && board[2] == board[6] && board[2] > 0) {
			return board[2];
		}
	}
	
	// Check for blank spaces. If one exists then the game is not 
	// over. If none exist the game is a draw.
	if(std::count(board.begin(), board.end(), 0) == 0) {
		return 0;
	}
	return -1;
}

int AI::score(std::vector<int> board, int depth)
{
	if(gameOver(board) == letter) {
		return 10 - depth;
	} else if(gameOver(board) == oppLetter) {
		return depth - 10;
	} else {
		return 0;
	}
}

int AI::minimax(std::vector<int> board, int depth, int currentPlayer, int& choice)
{
	if(gameOver(board) > 0) return score(board, depth);
	depth++;
	std::vector< std::pair<int, int> > moves;	// The moves and their corresponding scores.
	
	// Recurse for each possible move.
	for(unsigned int i = 0; i < board.size(); i++) {
		if(board[i] == 0) {
			std::vector<int> newBoard = board;
			newBoard[i] = currentPlayer;
			int newPlayer;
			if(currentPlayer == 1) {
				newPlayer = 2;
			} else {
				newPlayer = 1;
			}
			int score = minimax(newBoard, depth, newPlayer, choice);
			int move = i;
			moves.push_back(std::make_pair(score, move));
		}
	}
	
	// Return the min or the max.
	if(currentPlayer == letter) {	// max
		int max = -1000;
		int move;
		for(unsigned int i = 0; i < moves.size(); i++) {
			if(moves[i].first > max) {
				max = moves[i].first;
				move = moves[i].second;
			}
		}
		choice = move;	
		return max;
	} else if(currentPlayer == oppLetter) {	// min
		int min = 1000;;
		int move;
		for(unsigned int i = 0; i < moves.size(); i++) {
			if(moves[i].first < min) {
				min = moves[i].first;
				move = moves[i].second;
			}
		}
		choice = move;
		return min;
	}
	
	return -1000;
}

void AI::newGame(Connector& connector, std::string name)
{
	int newLetter = (rand() % 2) + 1;
    std::string responseString = connector.newGame(name, "AI_Game", newLetter);
	std::cout << responseString << std::endl;
	Response response(responseString);
	if(response.status == "error") {
		throw std::runtime_error(response.errorCode + ": " + response.message);
	}
	letter = response.letter;
	if(letter == 1) {
		oppLetter = 2;
	} else {
		oppLetter = 1;
	}
	gameID = response.id;
    secret = response.secret;
	board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
}

int AI::winner(Connector& connector)
{
	Response response(connector.next(gameID));
	if(response.status == "error") {
		throw std::runtime_error(response.errorCode + ": " + response.message);
	}
	return response.winner;
}

int AI::next(Connector& connector)
{
	std::string responseString = connector.next(secret);
	std::cout << responseString << std::endl;
	Response response(responseString);
	if(response.status == "error") {
		throw std::runtime_error(response.errorCode + ": " + response.message);
	}
	board = response.board;
	std::cout << "Colin's board is: ";
	for(unsigned int i = 0; i < board.size(); i++) {
		std::cout << board[i] << " ";
	}
	std::cout << std::endl;
	return response.turn;
}

int AI::chooseMove()
{
	int move;
	minimax(board, 0, letter, move);
	
	std::cout << "Colin's move: " << move << std::endl;
	return move;
}

void AI::move(Connector& connector, int move)
{
	std::cout << "Colin playing: " << move << std::endl;
	std::string responseString = connector.move(secret, std::to_string(move));
	std::cout << responseString << std::endl;
	Response response(responseString);
	if(response.status == "error") {
		throw std::runtime_error(response.errorCode + ": " + response.message);
	}
}
