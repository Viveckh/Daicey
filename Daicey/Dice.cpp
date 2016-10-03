/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#include "Dice.h"

// Default Constructor
Dice::Dice() {
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
Dice::Dice(int row, int column, bool king) {
	this->row = row;
	this->column = column;
	this->king = king;
}

/* *********************************************************************
Function Name: SetBeginningOrientation

Purpose: To set the remaining sides of a dice based on known sides at the beginning of game

Parameters:
top, the top integer value of the dice
isBot, boolean value stating if the dice is bot operated

Return Value: none

Local Variables: none besides loop counters

Assistance Received: none
********************************************************************* */
// Calculates & Sets the beginning orientation with face values of a dice in the home row
void Dice::SetBeginningOrientation(int top, bool isBot) {
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
}

/* *********************************************************************
Function Name: SetRemainingSides

Purpose: To set the remaining sides of a dice based on the known two (top-right for humans, top-left for bots)

Parameters:
arg1, the top value of dice
arg2, the right value if a human dice, the left value if a bot dice

Return Value: none

Local Variables: none

Assistance Received: had a discussion with Sujil Maharjan on how to approach this situation
********************************************************************* */
// Calculates & Sets the remaining sides of a dice given the Top-left or Top-Right sides
void Dice::SetRemainingSides(int arg1, int arg2) {
	// The first parameter is the top, the second one can either be left (for computer) or right (for human)
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

// Sets the values of faces if the given dice is a king
void Dice::SetKing(bool value) {
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

// Sets the controller of a dice, pass params as true if botOperated, false if humanOperated
void Dice::SetBotControl(bool value) {
	botOperated = value;
}

// Sets the dice as captured or uncaptured
void Dice::SetCaptured(bool value) {
	captured = value;
}

// Sets the dice coordinates
void Dice::SetCoordinates(int row, int column) {
	this->row = row;
	this->column = column;
}

// Increments or decrements a dice row based on given value and the boolean flag
void Dice::SetRow(int value, bool increment) {
	if (increment == true && (row + value) < 8) {
		row += value;
	}
	if (increment == false && (row - value) >= 0) {
		row -= value;
	}
}

// Increments or decrements a dice column based on given value and the boolean flag
void Dice::SetColumn(int value, bool increment) {
	if (increment == true && (column + value) < 9) {
		column += value;
	}
	if (increment == false && (column - value) >= 0) {
		column -= value;
	}
}

// Sets the top Value of a dice
void Dice::SetTop(int value) { 
	top = value; 
}

// Sets the bottom Value of a dice
void Dice::SetBottom(int value) { 
	bottom = value; 
}

// Sets the front Value of a dice
void Dice::SetFront(int value) { 
	front = value; 
}

// Sets the rear Value of a dice
void Dice::SetRear(int value) { 
	rear = value; 
}

// Sets the left Value of a dice
void Dice::SetLeft(int value) { 
	left = value; 
}

// Sets the right Value of a dice
void Dice::SetRight(int value) { 
	right = value; 
}