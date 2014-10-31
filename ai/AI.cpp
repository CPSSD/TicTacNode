// AI.cpp
// The AI class will decide what move to make each turn.

#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include "Connector.hpp"
#include "Response.hpp"
#include "AI.hpp"

int AI::getLetter()
{
	return letter;
}

void AI::newGame(Connector& connector)
{
	std::string responseString = connector.newGame("Colin");
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
	std::string responseString = connector.next(gameID);
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
	/* 1: If AI is able to win, play the winning move. */
	// Horizontally
	for(unsigned int i = 0; i < 3; i++) {
		if(board[i*3] == letter && board[i*3 + 1] == letter && board[i*3 + 2] == 0) {
			return i*3 + 2;
		} else if(board[i*3] == letter && board[i*3 + 1] == 0 && board[i*3 + 2] == letter) {
			return i*3 + 1;
		} else if(board[i*3] == 0 && board[i*3 + 1] == letter && board[i*3 + 2] == letter) {
			return i*3;
		}
	}
	// Vertically
	for(unsigned int i = 0; i < 3; i++) {
		if(board[i] == letter && board[i + 3] == letter && board[i + 6] == 0) {
			return i + 6;
		} else if(board[i] == letter && board[i + 3] == 0 && board[i + 6] == letter) {
			return i + 3;
		} else if(board[i] == 0 && board[i + 3] == letter && board[i + 6] == letter) {
			return i;
		}
	}
	// Diagonally top-left to bottom-right
	if(board[0] == letter && board[4] == letter && board[8] == 0) {
		return 8;
	} else if(board[0] == letter && board[4] == 0 && board[8] == letter) {
		return 4;
	} else if(board[0] == 0 && board[4] == letter && board[8] == letter) {
		return 0;
	}
	// Diagonally top-right to bottom-left
	if(board[2] == letter && board[4] == letter && board[6] == 0) {
		return 6;
	} else if(board[2] == letter && board[4] == 0 && board[6] == letter) {
		return 4;
	} else if(board[2] == 0 && board[4] == letter && board[6] == letter) {
		return 2;
	}
	
	/* 2: If opponent is about to win, play a move to block it. */
	// Horizontally
	for(unsigned int i = 0; i < 3; i++) {
		if(board[i*3] == oppLetter && board[i*3 + 1] == oppLetter && board[i*3 + 2] == 0) {
			return i*3 + 2;
		} else if(board[i*3] == oppLetter && board[i*3 + 1] == 0 && board[i*3 + 2] == oppLetter) {
			return i*3 + 1;
		} else if(board[i*3] == 0 && board[i*3 + 1] == oppLetter && board[i*3 + 2] == oppLetter) {
			return i*3;
		}
	}
	// Vertically
	for(unsigned int i = 0; i < 3; i++) {
		if(board[i] == oppLetter && board[i + 3] == oppLetter && board[i + 6] == 0) {
			return i + 6;
		} else if(board[i] == oppLetter && board[i + 3] == 0 && board[i + 6] == oppLetter) {
			return i + 3;
		} else if(board[i] == 0 && board[i + 3] == oppLetter && board[i + 6] == oppLetter) {
			return i;
		}
	}
	// Diagonally top-left to bottom-right
	if(board[0] == oppLetter && board[4] == oppLetter && board[8] == 0) {
		return 8;
	} else if(board[0] == oppLetter && board[4] == 0 && board[8] == oppLetter) {
		return 4;
	} else if(board[0] == 0 && board[4] == oppLetter && board[8] == oppLetter) {
		return 0;
	}
	// Diagonally top-right to bottom-left
	if(board[2] == oppLetter && board[4] == oppLetter && board[6] == 0) {
		return 6;
	} else if(board[2] == oppLetter && board[4] == 0 && board[6] == oppLetter) {
		return 4;
	} else if(board[2] == 0 && board[4] == oppLetter && board[6] == oppLetter) {
		return 2;
	}
	
	/* 3: If the centre is unoccupied, occupy it. */
	if(board[4] == 0) {
		return 4;
	}
	
	/* 4: Otherwise, play a random move. */
	int move = rand() % 9;
	while(board[move] != 0) {
		move = rand() % 9;
	}
	return move;
}

void AI::move(Connector& connector, int move)
{
	std::cout << "Colin playing: " << move << std::endl;
	std::string responseString = connector.move(gameID, std::to_string(move));
	std::cout << responseString << std::endl;
	Response response(responseString);
	if(response.status == "error") {
		throw std::runtime_error(response.errorCode + ": " + response.message);
	}
}
