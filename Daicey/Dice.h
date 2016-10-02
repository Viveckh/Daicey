//
// Dice Class
// Implements the properties of a dice object used in the game. 
// The class consists of variables and functions to store and modify a dice’s face values, its coordinates within a game board, 
// its controller (human or computer), its capture status, and whether it is a king. 
//

/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#pragma once
#include "stdafx.h"

class Dice {

public:
	
	// Default Constructor
	Dice();

	// Constructor
	Dice(int row, int column, bool king);

	// ACCESSORS

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

	// Returns true if the dice is Bot Operated
	bool IsBotOperated() {
		return botOperated;
	}

	// Returns true if the dice is a king
	bool IsKing() {
		return king;
	}

	// Returns true if a dice is captured
	bool IsCaptured() {
		return captured;
	}

	// MUTATORS

	// Calculates & Sets the beginning orientation with face values of a dice in the home row
	void SetBeginningOrientation(int top, bool isBot);

	// Calculates & Sets the remaining sides of a dice given the Top-left or Top-Right sides
	void SetRemainingSides(int arg1, int arg2);

	// Sets the values of faces if the given dice is a king
	void SetKing(bool value);

	// Sets the controller of a dice, pass params as true if botOperated, false if humanOperated
	void SetBotControl(bool value);

	// Sets the dice as captured or uncaptured
	void SetCaptured(bool value);

	// Sets the dice coordinates
	void SetCoordinates(int row, int column);

	// Increments or decrements a dice row based on given value and the boolean flag
	void SetRow(int value, bool increment);

	// Increments or decrements a dice column based on given value and the boolean flag
	void SetColumn(int value, bool increment);

	// Sets the top Value of a dice
	void SetTop(int value);

	// Sets the bottom Value of a dice
	void SetBottom(int value);

	// Sets the front Value of a dice
	void SetFront(int value);

	// Sets the rear Value of a dice
	void SetRear(int value);

	// Sets the left Value of a dice
	void SetLeft(int value);

	// Sets the right Value of a dice
	void SetRight(int value);

private:
	//CONSTANTS & VARIABLES DECLARATIONS
	const int SUM_OF_OPPOSITE_SIDES = 7;

	// Variables to dice location & properties
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

	// Arrays with the counter clockwise order of the face values when viewed from different angles
	int counterClockwiseDiceOrder1[8] = { 1, 2, 6, 5, 1, 2, 6, 5 };
	int counterClockwiseDiceOrder2[8] = { 3, 1, 4, 6, 3, 1, 4, 6 };
	int counterClockwiseDiceOrder3[8] = { 2, 3, 5, 4, 2, 3, 5, 4 };
};