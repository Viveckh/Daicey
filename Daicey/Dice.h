//
// Dice Class- Properties of a dice in the gameboard
//

#pragma once

class Dice {

public:

	// Getters for the coordinates
	int getRow() { return row; }
	int getColumn() { return column; }
	
	// Getters for the values of different faces of the dice
	int getTop() { return top; }
	int getBottom() { return bottom; }
	int getFront() { return front; }
	int getRear() { return rear; }
	int getLeft() { return left; }
	int getRight() { return right; }

	// Setters for the coordinates
	void SetRow(int value) { row = value; }
	void SetColumn(int value) { column = value; }

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

	//Variables to store the values of different faces
	int top;
	int bottom;
	int front;
	int rear;
	int left;
	int right;
};

