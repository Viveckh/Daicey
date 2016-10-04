/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#include "Human.h"

/* *********************************************************************
Function Name: Play

Purpose: To validate the human player's move request, and process it if valid

Parameters:
startRow, integer value of start row coordinate
startCol, integer value of start column coordinate
endRow, integer value of end row coordinate
endCol, integer value of end Column coordinate
board, the board in context where the move is to be made (passed by ref)
path, the path selected by the human player in turn of a 90 degree turn, if any

Return Value: true if move successsful, false otherwise

Local Variables: none

Assistance Received: none
********************************************************************* */
// Validates user's Input, Validates user's move and performs the move as instructed by human player
bool Human::Play(int startRow, int startCol, int endRow, int endCol, Board &board, int path) {
	printNotifications = true;

	if (IndexOutOfBounds(startRow, startCol, endRow, endCol)) {
		// Log error here
		notifications.Msg_InputOutOfBounds();
		return false;
	}
	// Decrementing the input values to match the gameboard internal representation in array
	startRow--;
	startCol--;
	endRow--;
	endCol--;

	// Verify the dice is not bot operated so that the dice belongs to human player
	if (board.GetSquareResident(startRow, startCol) != NULL) {
		if (!board.GetSquareResident(startRow, startCol)->IsBotOperated()) {
			// Checking to see if there is a 90 degree turn			
			if (MakeAMove(startRow, startCol, endRow, endCol, board, false, path)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			notifications.Msg_WrongDice();
			return false;
		}
	}
	else {
		notifications.Msg_NoDiceToMove();
		return false;
	}
}

/* *********************************************************************
Function Name: IndexOutOfBounds

Purpose: To check if the user input of coordinates is out of bounds

Parameters:
startRow, integer value of start row coordinate
startCol, integer value of start column coordinate
endRow, integer value of end row coordinate
endCol, integer value of end Column coordinate

Return Value: true if out of bounds, false if within bounds

Local Variables: none

Assistance Received: none
********************************************************************* */
// Returns true if any input values are out of bounds, Call before decrementing the input values to match the gameboard array indexes
bool Human::IndexOutOfBounds(int startRow, int startCol, int endRow, int endCol) {
	if (startRow <= 0 || startRow > 8) {
		return true;
	}

	if (startCol <= 0 || startCol > 9) {
		return true;
	}

	if (endRow <= 0 || endRow > 8) {
		return true;
	}

	if (endCol <= 0 || endCol > 9) {
		return true;
	}
	return false;
}