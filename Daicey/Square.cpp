#include "Square.h"

// Default Constructor
Square::Square() {
	row = NULL;
	column = NULL;
	resident = NULL;
}

// Constructor
Square::Square(int row, int column) {
	this->row = row;
	this->column = column;
}

// Sets coordinates of the square in a board
void Square::SetCoordinates(int row, int column) {
	this->row = row;
	this->column = column;
}

// Sets the given dice as a resident of the square
void Square::SetOccupied(Dice &dice) {
	resident = &dice;
}

// Clears the occupancy in the square
void Square::SetVacant() {
	resident = NULL;
}