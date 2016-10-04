//
// Square
// Stores and maintains the location and occupancy status of a square in the game board. A square can be occupied by a dice object only.
//

/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#pragma once
#include "Dice.h"

class Square {
public:
	// Default Constructor
	Square();

	// Constructor
	Square(int row, int column);

	//ACCESSORS

	// Gets the row of the square in a board
	int GetRow() { return row; }

	// Gets the column of the square in a board
	int GetColumn() { return column; }

	// Gets the pointer to resident die
	Dice * GetResident() {
		return resident;
	}

	// Checks whether the square is occupied by a gameobject
	bool IsOccupied() {
		if (resident != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	
	// MUTATORS
	// Sets coordinates of the square in a board
	void SetCoordinates(int row, int column);

	// Sets the given dice as a resident of the square
	void SetOccupied(Dice &dice);

	// Clears the occupancy in the square
	void SetVacant();

private:
	// VARIABLE DECLARATIONS

	// Coordinates of the square within the game board
	int row;
	int column;

	// Occupancy status, not occupied if the pointer is null
	Dice* resident;
};