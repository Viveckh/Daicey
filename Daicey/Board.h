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
		for (int currentRow = 1; currentRow <= 8; currentRow++) {
			for (int currentCol = 1; currentCol <= 9; currentCol++) {
				gameBoard[currentRow][currentCol].SetRow(currentRow);
				gameBoard[currentRow][currentCol].SetColumn(currentCol);

				if (currentRow == 1 || currentRow == 8) {
					gameBoard[currentRow][currentCol].SetOccupied(true);
				}
			}
		}
	}

private:
	Square gameBoard[8][9];
};


