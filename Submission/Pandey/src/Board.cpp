/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#include "Board.h"

/* *********************************************************************
Function Name: Board Constructor

Purpose: Sets up a board with the player dices in their respective spots

Parameters: None

Return Value: None

Local Variables: none besides loop counters

Assistance Received: none
********************************************************************* */
// Default Constructor
Board::Board() {

	// Defining which ones are the kings
	humans[4].SetKing(true);
	bots[4].SetKing(true);

	// Arranging the initial orientation of the dices in the board
	for (int index = 0; index < 9; index++) {
		//Supplying the top values since the rear value is 3 by default
		if (!humans[index].IsKing()) {
			humans[index].SetBeginningOrientation(startingTopValuesOfDices[index], false);
			bots[index].SetBeginningOrientation(startingTopValuesOfDices[index], true);
		}
		//cout << humans[index].GetTop() << humans[index].GetLeft() << humans[index].GetBottom() << humans[index].GetRight() << endl;
	}

	// General board setup with Squares and Dices
	for (int currentRow = 0; currentRow < 8; currentRow++) {
		for (int currentCol = 0; currentCol < 9; currentCol++) {
			gameBoard[currentRow][currentCol].SetCoordinates(currentRow, currentCol);

			//cout << "(" << gameBoard[currentRow][currentCol].GetRow() << ", " << gameBoard[currentRow][currentCol].GetColumn() << ")\t";

			//Humans Home Row
			if (currentRow == 0) {
				gameBoard[currentRow][currentCol].SetOccupied(humans[currentCol]);
				humans[currentCol].SetCoordinates(currentRow, currentCol);
				humans[currentCol].SetBotControl(false);
			}

			//Bots Home Row
			if (currentRow == 7) {
				gameBoard[currentRow][currentCol].SetOccupied(bots[currentCol]);
				bots[currentCol].SetCoordinates(currentRow, currentCol);
				bots[currentCol].SetBotControl(true);
			}
		}
		//cout << endl;
	}
}

// Sets the given square in the gameboard as occupied with the given dice
void Board::SetSquareOccupied(int row, int col, Dice &dice) {
	return gameBoard[row][col].SetOccupied(dice);
}

// Sets a square vacant from any dice occupancies
void Board::SetSquareVacant(int row, int col) {
	return gameBoard[row][col].SetVacant();
}