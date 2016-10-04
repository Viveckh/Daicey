//
// Board Class
// Initializes and maintains a game board of squares and player dices. 
// It consists of functions to initialize a board, retrieve the contents at different squares within the board, check and set the occupancy of these squares that comprise the game board.
//

/*	************************************************************
     * Name:		Vivek Pandey								*
     * Project:		Duell C++									*
     * Class:		CMPS 366									*
     * Date:		10/4/2016									*
     ************************************************************ */

#pragma once
#include "Square.h"
#include "Dice.h"

class Board {

public:
	// VARIABLES
	// ATTENTION: These arrays should be private/protected but accessible from elsewhere at the same time
	Dice humans[9];
	Dice bots[9];

	// DEFAULT CONSTRUCTOR
	Board();

	// SELECTORS
	// Checks if a square in the gameboard is occupied with dice
	bool IsSquareOccupied(int row, int col) {
		return gameBoard[row][col].IsOccupied();
	}

	// Gets the pointer to the resident die in the square
	Dice * GetSquareResident(int row, int col) {
		return gameBoard[row][col].GetResident();
	}

	// Gets the square in the given co-ordinates of the gameboard
	Square GetSquareAtLocation(int row, int col) {
		return gameBoard[row][col];
	}

	// Gets the human King Die in the Gameboard
	Dice GetHumanKing() {
		return humans[4];
	}

	// Gets the bot king Die in the Gameboard
	Dice GetBotKing() {
		return bots[4];
	}

	// MUTATORS
	// Sets the given square in the gameboard as occupied with the given dice
	void SetSquareOccupied(int row, int col, Dice &dice);

	// Sets a square vacant from any dice occupancies
	void SetSquareVacant(int row, int col);

private:
	// The gameboard Array
	Square gameBoard[8][9];

	// Top values of dice at home row
	int startingTopValuesOfDices[9] = { 5, 1, 2, 6, 1, 6, 2, 1, 5 };
};