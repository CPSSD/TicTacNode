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

int AI::move(Connector& connector)
{
	int move = rand() % 9;
	while(board[move] != 0) {
		move = rand() % 9;
	}
	std::cout << "Colin playing: " << move << std::endl;
	std::string responseString = connector.move(gameID, std::to_string(move));
	std::cout << responseString << std::endl;
	Response response(responseString);
	if(response.status == "error") {
		throw std::runtime_error(response.errorCode + ": " + response.message);
	}
	return move;
}
