//
// Moves - Various valid moves in the game
//

#pragma once
#include "Board.h"
#include "Dice.h"

class Moves {
public:
	// ATTENTION: Don't forget to increment/decrement the rows and columns after the moves
	// ALSO, don't forget to update the newly occupied coordinate and release the currently occupied square.
	void RollForward(Dice &dice, Board &board) {

		if (dice.GetRow() < 7 && !board.gameBoard[dice.GetRow()+1][dice.GetColumn()].IsOccupied()) {
			tempStorage1 = dice.GetFront();
			tempStorage2 = dice.GetRear();

			dice.SetFront(dice.GetTop());
			dice.SetRear(dice.GetBottom());
			dice.SetBottom(tempStorage1);
			dice.SetTop(tempStorage2);

			//Set the currently occupied square to empty, and place the dice in the new square
			board.gameBoard[dice.GetRow()][dice.GetColumn()].SetVacant();
			dice.SetRow(1, true);
			board.gameBoard[dice.GetRow()][dice.GetColumn()].SetOccupied(dice);
		}
		else {
			cout << "INVALID MOVE" << endl;
		}
	}

	void RollBackward(Dice &dice, Board &board) {
		if (dice.GetRow() > 0 && !board.gameBoard[dice.GetRow() - 1][dice.GetColumn()].IsOccupied()) {
			tempStorage1 = dice.GetFront();
			tempStorage2 = dice.GetRear();

			dice.SetRear(dice.GetTop());
			dice.SetFront(dice.GetBottom());
			dice.SetTop(tempStorage1);
			dice.SetBottom(tempStorage2);

			//Set the currently occupied square to empty, and place the dice in the new square
			board.gameBoard[dice.GetRow()][dice.GetColumn()].SetVacant();
			dice.SetRow(1, false);
			board.gameBoard[dice.GetRow()][dice.GetColumn()].SetOccupied(dice);
		}
	}

	void RollLeft(Dice &dice, Board &board) {
		if (dice.GetColumn() > 0 && !board.gameBoard[dice.GetRow()][dice.GetColumn() - 1].IsOccupied()) {
			tempStorage1 = dice.GetLeft();
			tempStorage2 = dice.GetRight();

			dice.SetLeft(dice.GetTop());
			dice.SetRight(dice.GetBottom());
			dice.SetBottom(tempStorage1);
			dice.SetTop(tempStorage2);

			//Set the currently occupied square to empty, and place the dice in the new square
			board.gameBoard[dice.GetRow()][dice.GetColumn()].SetVacant();
			dice.SetColumn(1, false);
			board.gameBoard[dice.GetRow()][dice.GetColumn()].SetOccupied(dice);
		}
	}

	void RollRight(Dice &dice, Board &board) {
		if (dice.GetColumn() < 8 && !board.gameBoard[dice.GetRow()][dice.GetColumn() + 1].IsOccupied()) {
			tempStorage1 = dice.GetLeft();
			tempStorage2 = dice.GetRight();

			dice.SetRight(dice.GetTop());
			dice.SetLeft(dice.GetBottom());
			dice.SetTop(tempStorage1);
			dice.SetBottom(tempStorage2);

			//Set the currently occupied square to empty, and place the dice in the new square
			board.gameBoard[dice.GetRow()][dice.GetColumn()].SetVacant();
			dice.SetColumn(1, true);
			board.gameBoard[dice.GetRow()][dice.GetColumn()].SetVacant();
		}
	}

	bool IsValidDestination(Dice dice, Square destination) {
		
		// Destination square should be empty
		if (destination.GetResident() == NULL) {

			// (Destination row - source row) + (Destination col - source col) gives the distance between the source and destination squares
			if (dice.GetTop() == abs(destination.GetRow() - dice.GetRow()) + abs(destination.GetColumn() - dice.GetColumn())) {
				return true;
			}
		}
		return false;
	}

	// The temporary dice goes and sits jumps from one square to the other and checks if it is already occupied
	bool IsPathValid(Dice dice, Square destination, Board board) {

		// CASE 1
		// If both the rows & columns differ in the destination, it means this is a frontal-lateral combined move attempt
		// TWO possible paths
		// ATTENTION: Need to work on this
		if ((dice.GetRow() != destination.GetRow()) && (dice.GetColumn() != destination.GetColumn())) {

			//Only one path needs to pass
			// Path 1 - First row traversal, then Column
			if (TraversedRowsWithoutBlockade(dice, destination, board) && TraversedColumnsWithoutBlockade(dice, destination, board)) {
				return true;
			}

			// Path 2 - First column traversal, then row
			if (TraversedColumnsWithoutBlockade(dice, destination, board) && TraversedRowsWithoutBlockade(dice, destination, board)) {
				return true;
			}

			//If both the path couldn't return true, then the path is invalid
			return false;
		}

		// CASE 2
		// If only the rows change in destination, it means this is a frontal/backward move attempt
		// ONE possible path
		if (dice.GetRow() != destination.GetRow()) {
			if (TraversedRowsWithoutBlockade(dice, destination, board)) {
				return true;
			}
			else {
				return false;
			}
		}

		// CASE 3
		// If only the column change, it means this is a lateral move attempt
		// ONE possible path
		if (dice.GetColumn() != destination.GetColumn()) {
			if (TraversedColumnsWithoutBlockade(dice, destination, board)) {
				return true;
			}
			else {
				return false;
			}
		}

		// If moving from and to the current location, still true lol
		return true;
	}

	// The passed by reference dice is actually a temporary dice itself
	bool TraversedRowsWithoutBlockade(Dice &dice, Square destination, Board board) {
		do {
			// Increment if destination is in a upper row, decrement if in a lower row
			if (dice.GetRow() < destination.GetRow()) {
				dice.SetRow(1, true);
			}
			else {
				dice.SetRow(1, false);
			}

			// Check if there is a blockade on the path as you go.
			// If yes, the path is invalid
			if (board.gameBoard[dice.GetRow()][dice.GetColumn()].IsOccupied()) {
				return false;
			}
		} while (dice.GetRow() == destination.GetRow());
		// If it gets to this point without any false returns, it is a valid path
		return true;
	}

	// The passed by reference dice is actually a temporary dice itself
	bool TraversedColumnsWithoutBlockade(Dice &dice, Square destination, Board board) {
		do {

			// Increment if destination is in a right column, decrement if in a left column
			if (dice.GetColumn() < destination.GetColumn()) {
				dice.SetColumn(1, true);
			}
			else {
				dice.SetColumn(1, false);
			}

			// Check if there is a blockade on the path as you go.
			// If yes, the path is invalid
			if (board.gameBoard[dice.GetRow()][dice.GetColumn()].IsOccupied()) {
				return false;
			}
		} while (dice.GetColumn() != destination.GetColumn());
		return true;
	}

private:
	int tempStorage1;
	int tempStorage2;
};