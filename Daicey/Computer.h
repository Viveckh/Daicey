#pragma once
#include "Player.h"

class Computer : public Player {
public:
	Computer() {}

	bool Play(Board &board) {
		/*
		Board calculationBoard(board);	// Using implicitly defined copy constructor
		for (int loopThroughDice = 0; loopThroughDice < TEAMSIZE; loopThroughDice) {
			//if (IsValidDestination(calculationBoard.bots[loopThroughDice], )) {}
		}
		*/
		return true;
		// Calculate all the possibilities and make a move
	}

private:
	const int TEAMSIZE = 9;
};