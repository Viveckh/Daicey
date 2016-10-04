/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#include "BoardView.h"

/* *********************************************************************
Function Name: DrawBoard

Purpose: Draws the game board to the console

Parameters: board, board object to be drawn

Return Value: none

Local Variables: none besides loop counters

Assistance Received: none
********************************************************************* */
// Draws the GameBoard to the console
void BoardView::DrawBoard(Board &board) {
	//Drawing the board inverted cause zero row is supposed to be at the bottom
	cout << endl;
	for (int row = 7; row >= 0; row--) {
		cout << abs(row + 1) << "\t";
		for (int col = 0; col < 9; col++) {
			if (board.IsSquareOccupied(row, col)) {
				//ATTENTION: Need to work on this after establishing a link between a square and a dice.
				//Try creating a dice within the square class and see if that link assists it in some way.
				//Also add isHuman/isComputer functions to find out if a dice is operated by a human or a comp

				if (board.GetSquareResident(row, col)->IsBotOperated()) {
					cout << "C";
					cout << board.GetSquareResident(row, col)->GetTop() << board.GetSquareResident(row, col)->GetLeft() << "\t";
				}
				else {
					cout << "H";
					cout << board.GetSquareResident(row, col)->GetTop() << board.GetSquareResident(row, col)->GetRight() << "\t";
				}

			}
			else {
				cout << "-\t";
			}
		}
		cout << endl;
	}
	cout << "\t1\t2\t3\t4\t5\t6\t7\t8\t9" << endl << endl;
}

/* *********************************************************************
Function Name: ViewNonCapturedDice

Purpose: Display the array indexes of non captured dice in the gameboard

Parameters: board, the Board to be inspected

Return Value: none

Local Variables: none besides loop counters

Assistance Received: none
********************************************************************* */
// Prints out the indexes of player dice that are still active on the gameboard
void BoardView::ViewNonCapturedDice(Board &board) {
	cout << "Non Captured Human indexes: ";
	for (int i = 0; i < 9; i++) {
		if (!board.humans[i].IsCaptured()) {
			cout << i << " ";
		}
	}
	cout << endl;

	cout << "Non Captured Bot indexes: ";
	for (int j = 0; j < 9; j++) {
		if (!board.bots[j].IsCaptured()) {
			cout << j << " ";
		}
	}
	cout << endl;
}