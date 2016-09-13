//
// Square - Properties and contents of a square in the game Board
//

#pragma once
#include "Dice.h"

class Square {

public:
	// Default Constructor
	Square() {
		row = NULL;
		column = NULL;
		resident = NULL;
	}

	// Constructor
	Square(int row, int column) {
		this->row = row;
		this->column = column;
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

	// Sets the occupancy status of the square
	void SetOccupied(Dice &dice) {
		resident = &dice;
	}

	Dice * GetResident() {
		return resident;
	}

	// Clears the occupancy
	void SetVacant() {
		resident = NULL;
	}

	void SetCoordinates(int row, int column) {
		this->row = row;
		this->column = column;
	}

	int GetRow() { return row; }
	int GetColumn() { return column; }

private:
	// Coordinates of the square within the game board
	int row;
	int column;

	// Occupancy status, not occupied if the pointer is null
	Dice* resident;
};