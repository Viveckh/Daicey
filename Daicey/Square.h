//
// Square - Properties and contents of a square in the game Board
//

#pragma once

class Square {

public:
	// Default Constructor
	Square() {
		row = 0;
		row = 0;
		occupied = false;
	}

	// Constructor
	Square(int row, int column, bool occupied) {
		this->row = row;
		this->column = column;
		this->occupied = occupied;
	}

	// Checks whether the square is occupied by a gameobject
	bool IsOccupied() {
		return occupied;
	}

	// Sets the occupancy status of the square
	void SetOccupied(bool value) {
		occupied = value;
	}

	void SetRow(int value) { row = value; }
	void SetColumn(int value) { column = value; }

	int GetRow() { return row; }
	int GetColumn() { return column; }

private:
	// Coordinates of the square within the game board
	int row;
	int column;

	// Occupancy status
	bool occupied;
};