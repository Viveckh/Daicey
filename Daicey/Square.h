//
// Square - Properties and contents of a square in the game Board
//

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