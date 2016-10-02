//
// Player Class
// Implements the basic set of strategies for any player like traversing the board and determining path choices, validating and processing moves, 
// changing dice orientation based on the rolls, capturing and eliminating opponent dices.
//

/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#pragma once
#include "Board.h"
#include "Dice.h"
#include "Notifications.h"

class Player {
public:

	// Default Constructor
	Player();

protected:
	// Gets path choice
	int GetPathChoice() {
		return pathChoice;
	}

	/*
	// NEW SECTION: THESE FUNCTIONS CAN BE USED TO CHANGE STATES EITHER IN A TEMPORARY OR A PERMANENT GAME BOARD
	*/
	
	// Does one up roll of the dice
	void RollUp(Dice &dice, Board &board);

	// Does one down roll of the dice
	void RollDown(Dice &dice, Board &board);

	// Does one left roll of the dice
	void RollLeft(Dice &dice, Board &board);

	// Does one right roll of the dice
	void RollRight(Dice &dice, Board &board);

	/*
	// NEW SECTION: THE FOLLOWING FUNCTIONS WILL FORM TEMPORARY PASSED-BY-VALUE GAME OBJECTS AND CHECK THE VALIDITY OF ROUTE/DESTINATION
	*/

	// Checks if the destination is a valid one
	bool IsValidDestination(Dice dice, Square destination);

	// Checks the validity of a path to get from origin to destination square
	bool IsPathValid(Dice dice, Square destination, Board board);

	// Returns true if traversal is successful without blockade until the destination row (The passed by reference dice is actually a temporary dice itself)
	bool TraversedRowsWithoutBlockade(Dice &dice, Square destination, Board board);

	// Returns true if traversal is successful without blockade until the destination column (The passed by reference dice is actually a temporary dice itself)
	bool TraversedColumnsWithoutBlockade(Dice &dice, Square destination, Board board);

	/*
	// NEW SECTION: THE FOLLOWING FUNCTIONS WILL ACTUALLY MODIFY THE REAL GAMEBOARD.
	*/

	// Checks the validity of a given move, and performs it on the gameboard if valid
	bool MakeAMove(int startRow, int startCol, int endRow, int endCol, Board &board, int path = 0);

	//These two following functions will modify the actual gameboard. So pass the real game objects
	// Make sure you check the validity of the path beforehand. Cause they won't do the checking

	// Rolls the dice vertically until it is in the destination row
	void KeepRollingVertically(Dice &dice, Square &destination, Board &board);

	// Rolls the die laterally until it is in the destination column
	void KeepRollingLaterally(Dice &dice, Square &destination, Board &board);

protected:
	// static variable to toggle notifications print on and off
	static bool printNotifications;

private:
	// VARIABLES & OBJECTS DECLARATIONS
	int pathChoice;	// Choice of what type of path to take out of available four types
	bool multiplePathPossible;

	// Variables for Player Strategies
	int tempStorage1;
	int tempStorage2;

	// Counting variables for traversals to reset back the die position
	int counterRowsTraversed;
	int counterColumnsTraversed;

	Notifications notifications;
};