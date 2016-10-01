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
		captured = false;
	}

	// Constructor
	Dice (int row, int column, bool king) {
		this->row = row;
		this->column = column;
		this->king = king;
	}

	void SetBeginningOrientation(int top, bool isBot) {
		//Values given in program specs
		this->top = top;
		bottom = SUM_OF_OPPOSITE_SIDES - top;

		//Since the dies are arranged facing each other in two opposite directions
		if (isBot) {
			front = 3;
			rear = SUM_OF_OPPOSITE_SIDES - front;
		}
		else {
			rear = 3;	// for human
			front = SUM_OF_OPPOSITE_SIDES - rear;
		}

		/*	Since the given dice is oriented in a counterclockwise direction and 3 is always facing the rear,
			the top-left-bottom-right values are always in some 1-2-6-5 order pattern.
			This means, for a human, the left value is always next to the top value in the given 1-2-6-5 order.
			For a bot, the reverse is true, i.e. right value is always next to the top value in the 1-2-6-5 order.
		*/
		
		// Searching through the counter clockwise dice pattern to find the top value
		for (int index = 0; index < 4; index++) {
			if (counterClockwiseDiceOrder1[index] == top) {
				// If index has the top value, index+1 will have the left value for human, and right value for a bot
				if (index <= 2) {
					if (isBot) {
						right = counterClockwiseDiceOrder1[index + 1];
						left = SUM_OF_OPPOSITE_SIDES - right;
					}
					else {
						left = counterClockwiseDiceOrder1[index + 1];
						right = SUM_OF_OPPOSITE_SIDES - left;
					}
				}
				else {
					// If the last index has the matching top value, then the first index would have the left value for human, and right value for a bot
					if (isBot) {
						right = counterClockwiseDiceOrder1[0];
						left = SUM_OF_OPPOSITE_SIDES - right;
					}
					else {
						left = counterClockwiseDiceOrder1[0];
						right = SUM_OF_OPPOSITE_SIDES - left;
					}
				}
				break;
			}
		}
		//cout << top << left << bottom << right << endl;
	}

	// The first parameter is the top, the second one can either be left (for computer) or right (for human)
	void SetRemainingSides(int arg1, int arg2) {
		bottom = SUM_OF_OPPOSITE_SIDES - arg1;
		
		// for computer the given arg2 is left whereas for human the given arg2 is right value
		if (IsBotOperated()) {
			right = SUM_OF_OPPOSITE_SIDES - arg2;
		}
		else {
			left = SUM_OF_OPPOSITE_SIDES - arg2;
		}
		
		front = rear = 0;	//resetting before calculating new one

		// From this point, it doesn't matter whether it is human or computer die because both are saved in the model in the same way
		// above we had to be careful to meet our model's specs because the computer's right given in the serialization file is actually left in our overall board model
		for (int index = 0; index < 7; index++) {
			if (counterClockwiseDiceOrder1[index] == top && counterClockwiseDiceOrder1[index + 1] == right) {
				// take higher out of the remaining two not in the array as the rear value
				rear = 4;
				front = SUM_OF_OPPOSITE_SIDES - rear;
				break;
			}

			if (counterClockwiseDiceOrder1[index] == right && counterClockwiseDiceOrder1[index + 1] == top) {
				// take lower out of the remaining two not in the array as the rear value
				rear = 3;
				front = SUM_OF_OPPOSITE_SIDES - rear;
				break;
			}

			if (counterClockwiseDiceOrder2[index] == top && counterClockwiseDiceOrder2[index + 1] == right) {
				// take higher out of the remaining two not in the array as the rear value
				rear = 5;
				front = SUM_OF_OPPOSITE_SIDES - rear;
				break;
			}

			if (counterClockwiseDiceOrder2[index] == right && counterClockwiseDiceOrder2[index + 1] == top) {
				// take lower out of the remaining two not in the array as the rear value
				rear = 2;
				front = SUM_OF_OPPOSITE_SIDES - rear;
				break;
			}

			if (counterClockwiseDiceOrder3[index] == top && counterClockwiseDiceOrder3[index + 1] == right) {
				// take higher out of the remaining two not in the array as the rear value
				rear = 6;
				front = SUM_OF_OPPOSITE_SIDES - rear;
				break;
			}

			if (counterClockwiseDiceOrder3[index] == right && counterClockwiseDiceOrder3[index + 1] == top) {
				// take lower out of the remaining two not in the array as the rear value
				rear = 1;
				front = SUM_OF_OPPOSITE_SIDES - rear;
				break;
			}
		}
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

	void SetCaptured(bool value) {
		captured = value;
	}

	bool IsCaptured() {
		return captured;
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
	bool captured;

	//Variables to store the values of different faces
	int top;
	int bottom;
	int front;
	int rear;
	int left;
	int right;

	int counterClockwiseDiceOrder1[8] = { 1, 2, 6, 5, 1, 2, 6, 5 };
	int counterClockwiseDiceOrder2[8] = { 3, 1, 4, 6, 3, 1, 4, 6 };
	int counterClockwiseDiceOrder3[8] = { 2, 3, 5, 4, 2, 3, 5, 4 };
	const int SUM_OF_OPPOSITE_SIDES = 7;
};