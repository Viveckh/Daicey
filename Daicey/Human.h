#pragma once
#include "Player.h"

class Human: public Player {
public:
	// ATTENTION: Validate the input
	bool Play(int startRow, int startCol, int endRow, int endCol, Board &board) {
		
		if (IndexOutOfBounds(startRow, startCol, endRow, endCol)) {
			// Log error here
			cout << "Input co-ordinates out of bound. Try again!" << endl;
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
				MakeAMove(startRow, startCol, endRow, endCol, board);
				return true;
			}
			else {
				cout << "Not your player" << endl;
				return false;
			}
		}
		else {
			cout << "No dices in the square" << endl;
			return false;
		}
	}

	// Returns true if any input values are out of bounds
	// Call before decrementing the input values to match the gameboard array indexes
	bool IndexOutOfBounds(int startRow, int startCol, int endRow, int endCol) {
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

private:

};