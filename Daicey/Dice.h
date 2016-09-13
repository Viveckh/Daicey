//
// Dice Class- Properties of a dice in the gameboard
//

#pragma once
#include "stdafx.h"

class Dice {

public:
	
	// Default Constructor
	Dice() {
		row = 0;
		column = 0;
		top = 1;
		left = 2;
		rear = 3;
		bottom = SUM_OF_OPPOSITE_SIDES - top;
		right = SUM_OF_OPPOSITE_SIDES - left;
		front = SUM_OF_OPPOSITE_SIDES - rear;
		king = false;
		botOperated = false;
	}

	// Constructor
	Dice (int row, int column, bool king) {
		this->row = row;
		this->column = column;
		this->king = king;
	}

	void SetBeginningOrientation(int top) {
		//Values given in program specs
		this->top = top;
		rear = 3;	//By default, as supplied
		
		//Derived values since the sum of opposite sides is 7
		bottom = SUM_OF_OPPOSITE_SIDES - top;
		front = SUM_OF_OPPOSITE_SIDES - rear;

		/*	Since the given dice is oriented in a counterclockwise direction and 3 is always facing the rear,
			the top-left-bottom-right values are always in some 1-2-6-5 order pattern.
			This means, the left value is always next to the top value in the given 1-2-6-5 order.
		*/
		
		// Searching through the counter clockwise dice pattern to find the top value
		for (int index = 0; index < 4; index++) {
			if (counterClockwiseDiceOrder[index] == top) {
				// If index has the top value, index+1 will have the left value
				if (index <= 2) {
					left = counterClockwiseDiceOrder[index + 1];
				}
				else {
					// If the last index has the matching top value, then the first index would have the left value.
					left = counterClockwiseDiceOrder[0];
				}
				break;
			}
		}
		right = SUM_OF_OPPOSITE_SIDES - left;

		//cout << top << left << bottom << right << endl;
	}

	// Getters for the coordinates
	int GetRow() { return row; }
	int GetColumn() { return column; }
	
	// Getters for the values of different faces of the dice
	int GetTop() { return top; }
	int GetBottom() { return bottom; }
	int GetFront() { return front; }
	int GetRear() { return rear; }
	int GetLeft() { return left; }
	int GetRight() { return right; }

	// Setters for the coordinates
	void SetCoordinates(int row, int column) {
		this->row = row;
		this->column = column;
	}

	void SetRow(int value, bool increment) {
		if (increment == true && (row + value) < 8) {
			row += value;
		}
		if (increment == false && (row - value) >= 0) {
			row -= value;
		}
	}

	void SetColumn(int value, bool increment) {
		if (increment == true && (column + value) < 9) {
			column += value;
		}
		if (increment == false && (column - value) >= 0) {
			column -= value;
		}
	}

	void SetKing(bool value) { 
		king = value;
		if (value) {
			top = 1;
			bottom = 1;
			front = 1;
			rear = 1;
			left = 1;
			right = 1;
		}
	}

	void SetBotControl(bool value) {
		botOperated = value;
	}

	bool IsBotOperated() {
		return botOperated;
	}

	bool IsKing() {
		return king;
	}

	// Setters for the values of different faces of the dime
	// ATTENTION: Setting one face automatically sets the opposite since the sum is 7
	void SetTop(int value) { top = value; }

	void SetBottom(int value) { bottom = value; }

	void SetFront(int value) { front = value; }

	void SetRear(int value) { rear = value; }

	void SetLeft(int value) { left = value; }

	void SetRight(int value) { right = value; }

private:
	// Variables to store coordinates
	int row;
	int column;
	bool king;
	bool botOperated;

	//Variables to store the values of different faces
	int top;
	int bottom;
	int front;
	int rear;
	int left;
	int right;

	int counterClockwiseDiceOrder[4] = { 1, 2, 6, 5 };
	const int SUM_OF_OPPOSITE_SIDES = 7;
};