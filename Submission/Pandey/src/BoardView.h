//
// BoardView Class
// Draws the updated game board to the console. Also can notify the user about the dices that haven’t been captured and are active on the game board.
//

/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

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