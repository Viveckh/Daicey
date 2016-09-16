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

	bool IsSquareOccupied(int row, int col) {
		return gameBoard[row][col].IsOccupied();
	}

	void SetSquareOccupied(int row, int col, Dice &dice) {
		return gameBoard[row][col].SetOccupied(dice);
	}

	void SetSquareVacant(int row, int col) {
		return gameBoard[row][col].SetVacant();
	}

	Dice * GetSquareResident(int row, int col) {
		return gameBoard[row][col].GetResident();
	}

	Square GetSquareAtLocation(int row, int col) {
		return gameBoard[row][col];
	}

	//ATTENTION: These should be private/protected but accessible from elsewhere at the same time
	Dice humans[9];
	Dice bots[9];
private:
	Square gameBoard[8][9];
	int startingTopValuesOfDices[9] = { 5, 1, 2, 6, 1, 6, 2, 1, 5 };
};