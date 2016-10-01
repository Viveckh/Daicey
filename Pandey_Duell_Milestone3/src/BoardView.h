//
// Displays the Game Board to Console
//

#pragma once
#include "stdafx.h"
#include "Square.h"
#include "Dice.h"
#include "Board.h"

class BoardView {
public:

	// Default Constructor
	BoardView() {}

	// Draws the GameBoard to the console
	void DrawBoard(Board &board);
	
	// Prints out the indexes of player dice that are still active on the gameboard
	void ViewNonCapturedDice(Board &board);
};