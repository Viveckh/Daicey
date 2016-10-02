//
// Class Human
// Handles the move requests from a human player by performing input validations and processing them to reflect changes in the game board.
//

/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#pragma once
#include "Player.h"
#include "Notifications.h"

class Human: public Player {
public:

	// Default Constructor
	Human() {}

	// Validates user's Input, Validates user's move and performs the move as instructed by human player
	bool Play(int startRow, int startCol, int endRow, int endCol, Board &board, int path = 0);

	// Returns true if any input values are out of bounds, Call before decrementing the input values to match the gameboard array indexes
	bool IndexOutOfBounds(int startRow, int startCol, int endRow, int endCol);

private:
	Notifications notifications;
};