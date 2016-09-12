//
// Board - The properties and state of a game board
//

#pragma once
#include "Square.h"
#include "Dice.h"

class Board {

public:
	// Default Constructor
	Board() {

		// Defining which ones are the kings
		humans[4].SetKing(true);
		bots[4].SetKing(true);

		// Arranging the orientation of the dices in the board
		for (int index = 0; index < 9; index++) {
			//Supplying the top values since the rear value is 3 by default
			if (!humans[index].IsKing()) {
				humans[index].SetBeginningOrientation(startingTopValuesOfDices[index]);
				bots[index].SetBeginningOrientation(startingTopValuesOfDices[index]);
			}
			cout << humans[index].getTop() << humans[index].getLeft() << humans[index].getBottom() << humans[index].getRight() << endl;
		}

		// General board setup with Squares and Dices
		for (int currentRow = 0; currentRow < 8; currentRow++) {
			for (int currentCol = 0; currentCol < 9; currentCol++) {
				gameBoard[currentRow][currentCol].SetCoordinates(currentRow, currentCol);
				
				cout << "(" << gameBoard[currentRow][currentCol].GetRow() << ", " << gameBoard[currentRow][currentCol].GetColumn() << ")\t";

				if (currentRow == 0) {
					gameBoard[currentRow][currentCol].SetOccupied(true);
					humans[currentCol].SetCoordinates(currentRow, currentCol);
				}

				if (currentRow == 7) {
					gameBoard[currentRow][currentCol].SetOccupied(true);
					bots[currentCol].SetCoordinates(currentRow, currentCol);
				}
			}
			cout << endl;
		}	
	}

	void DrawBoard() {
		//Drawing the board inverted cause zero row is supposed to be at the bottom
		for (int row = 7; row >= 0; row++) {
			for (int col = 0; col < 9; col++) {
				if (gameBoard[row][col].IsOccupied()) {
					//ATTENTION: Need to work on this after establishing a link between a square and a dice.
					//Try creating a dice within the square class and see if that link assists it in some way.
					//Also add isHuman/isComputer functions to find out if a dice is operated by a human or a comp
				}
				else {
					cout << "-\t";
				}
			}
			cout << endl;
		}

	}

private:
	Square gameBoard[8][9];
	Dice humans[9];
	Dice bots[9];
	int startingTopValuesOfDices[9] = { 5, 1, 2, 6, 1, 6, 2, 1, 5 };
};


