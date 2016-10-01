//
// Listens & acts in accordance to the move request made by human player
//

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