//
// Board - The properties and state of a game board
//

#pragma once
#include "Square.h"
#include "Dice.h"

class Board {

public:
	// Default Constructor
	Board();

	// Checks if a square in the gameboard is occupied with dice
	bool IsSquareOccupied(int row, int col) {
		return gameBoard[row][col].IsOccupied();
	}

	// Sets the given square in the gameboard as occupied with the given dice
	void SetSquareOccupied(int row, int col, Dice &dice) {
		return gameBoard[row][col].SetOccupied(dice);
	}

	// Sets a square vacant from any dice occupancies
	void SetSquareVacant(int row, int col) {
		return gameBoard[row][col].SetVacant();
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

	//ATTENTION: These arrays should be private/protected but accessible from elsewhere at the same time
	Dice humans[9];
	Dice bots[9];

private:
	Square gameBoard[8][9];		// The gameboard Array
	int startingTopValuesOfDices[9] = { 5, 1, 2, 6, 1, 6, 2, 1, 5 };	// Top values of dice at home row
};