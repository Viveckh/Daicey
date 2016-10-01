#pragma once
#include "Player.h"
#include "Notifications.h"

class Human: public Player {
public:

	Human() {}

	// ATTENTION: Validate the input
	bool Play(int startRow, int startCol, int endRow, int endCol, Board &board, int path = 0) {
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
				if (MakeAMove(startRow, startCol, endRow, endCol, board, path)) {
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
	Notifications notifications;
};