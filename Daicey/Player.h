//
//  Player - Stats/Actions of a Game Player
//

#pragma once
#include "Board.h"
#include "Dice.h"

class Player {
public:
	Player() {
		wins = 0;
		score = 0;
		pathChoice = 0;
		tempStorage1 = 0;
		tempStorage2 = 0;
		counterRowsTraversed = 0;
		counterColumnsTraversed = 0;
	}

	// FUNCTIONS FOR RECORDING THE PLAYER STATS
	void WinsTheRound() {
		wins++;
	}


	/*

	// NEW SECTION: THESE FUNCTIONS CAN BE USED TO CHANGE STATES EITHER IN A TEMPORARY OR A PERMANENT GAME BOARD

	*/
	
	// ALSO, don't forget to update the newly occupied coordinate and release the currently occupied square.
	void RollUp(Dice &dice, Board &board) {

		if (dice.GetRow() < 7) {
			tempStorage1 = dice.GetFront();
			tempStorage2 = dice.GetRear();

			dice.SetFront(dice.GetTop());
			dice.SetRear(dice.GetBottom());
			dice.SetBottom(tempStorage1);
			dice.SetTop(tempStorage2);

			//Set the currently occupied square to empty (also capturing the current dice, if in destination), and place our dice in the next square
			board.SetSquareVacant(dice.GetRow(), dice.GetColumn());
			dice.SetRow(1, true);

			//This capture statement will only be executed at the destination square if path checking is done beforehand
			if (board.GetSquareResident(dice.GetRow(), dice.GetColumn()) != NULL) {
				board.GetSquareResident(dice.GetRow(), dice.GetColumn())->SetCaptured(true);
			}
			
			board.SetSquareOccupied(dice.GetRow(), dice.GetColumn(), dice);
		}
		else {
			cout << "INVALID MOVE" << endl;
		}
	}

	void RollDown(Dice &dice, Board &board) {
		if (dice.GetRow() > 0) {
			tempStorage1 = dice.GetFront();
			tempStorage2 = dice.GetRear();

			dice.SetRear(dice.GetTop());
			dice.SetFront(dice.GetBottom());
			dice.SetTop(tempStorage1);
			dice.SetBottom(tempStorage2);

			//Set the currently occupied square to empty (also capturing the current dice, if in destination), and place our dice in the next square
			board.SetSquareVacant(dice.GetRow(), dice.GetColumn());
			dice.SetRow(1, false);
			
			//This capture statement will only be executed at the destination square if path checking is done beforehand
			if (board.GetSquareResident(dice.GetRow(), dice.GetColumn()) != NULL) {
				board.GetSquareResident(dice.GetRow(), dice.GetColumn())->SetCaptured(true);
			}
			
			board.SetSquareOccupied(dice.GetRow(), dice.GetColumn(), dice);
		}
	}

	void RollLeft(Dice &dice, Board &board) {
		if (dice.GetColumn() > 0) {
			tempStorage1 = dice.GetLeft();
			tempStorage2 = dice.GetRight();

			dice.SetLeft(dice.GetTop());
			dice.SetRight(dice.GetBottom());
			dice.SetBottom(tempStorage1);
			dice.SetTop(tempStorage2);

			//Set the currently occupied square to empty (also capturing the current dice, if in destination), and place our dice in the next square
			board.SetSquareVacant(dice.GetRow(), dice.GetColumn());
			dice.SetColumn(1, false);

			//This capture statement will only be executed at the destination square if path checking is done beforehand
			if (board.GetSquareResident(dice.GetRow(), dice.GetColumn()) != NULL) {
				board.GetSquareResident(dice.GetRow(), dice.GetColumn())->SetCaptured(true);
			}

			board.SetSquareOccupied(dice.GetRow(), dice.GetColumn(), dice);
		}
	}

	void RollRight(Dice &dice, Board &board) {
		if (dice.GetColumn() < 8) {
			tempStorage1 = dice.GetLeft();
			tempStorage2 = dice.GetRight();

			dice.SetRight(dice.GetTop());
			dice.SetLeft(dice.GetBottom());
			dice.SetTop(tempStorage1);
			dice.SetBottom(tempStorage2);

			//Set the currently occupied square to empty (also capturing the current dice, if in destination), and place our dice in the next square
			board.SetSquareVacant(dice.GetRow(), dice.GetColumn());
			dice.SetColumn(1, true);

			//This capture statement will only be executed at the destination square if path checking is done beforehand
			if (board.GetSquareResident(dice.GetRow(), dice.GetColumn()) != NULL) {
				board.GetSquareResident(dice.GetRow(), dice.GetColumn())->SetCaptured(true);
			}

			board.SetSquareOccupied(dice.GetRow(), dice.GetColumn(), dice);
		}
	}

	/*

	// NEW SECTION: THE FOLLOWING FUNCTIONS WILL FORM TEMPORARY PASSED-BY-VALUE GAME OBJECTS AND CHECK THE VALIDITY OF ROUTE/DESTINATION

	*/

	bool IsValidDestination(Dice dice, Square destination) {
		
		// Destination square does not need to be empty, so I commented the below condition
		// if (destination.GetResident() == NULL) {} If square 

		// (Destination row - source row) + (Destination col - source col) gives the distance between the source and destination squares
		if (dice.GetTop() == abs(destination.GetRow() - dice.GetRow()) + abs(destination.GetColumn() - dice.GetColumn())) {
			return true;
		}
		return false;
	}

	// The temporary dice goes and sits jumps from one square to the other and checks if it is already occupied
	bool IsPathValid(Dice dice, Square destination, Board board) {
		counterRowsTraversed = 0;
		counterColumnsTraversed = 0;
		pathChoice = 0;

		// CASE 1
		// If both the rows & columns differ in the destination, it means this is a frontal-lateral combined move attempt
		// TWO possible paths
		// ATTENTION: Need to work on this
		if ((dice.GetRow() != destination.GetRow()) && (dice.GetColumn() != destination.GetColumn())) {

			//Only one path needs to pass
			// Path 1 - First row traversal, then Column
			if (TraversedRowsWithoutBlockade(dice, destination, board) && TraversedColumnsWithoutBlockade(dice, destination, board)) {
				pathChoice = 1;
				return true;
			}

			// In case we need to check the validity of second path, the dice needs to be reverted back to its original spot 
			// based on the counters gathered while traversing above
			dice.SetRow(counterRowsTraversed, false);
			dice.SetColumn(counterColumnsTraversed, false);

			// Path 2 - First column traversal, then row
			if (TraversedColumnsWithoutBlockade(dice, destination, board) && TraversedRowsWithoutBlockade(dice, destination, board)) {
				pathChoice = 2;
				return true;
			}

			//If both the path couldn't return true, then the path is invalid
			cout << "Invalid path in route 1 and 2" << endl;
			return false;
		}

		// CASE 2
		// If only the rows change in destination, it means this is a frontal/backward move attempt
		// ONE possible path
		if (dice.GetRow() != destination.GetRow()) {
			if (TraversedRowsWithoutBlockade(dice, destination, board)) {
				pathChoice = 3;
				return true;
			}
			else {
				cout << "Invalid path in route 3" << endl;
				return false;
			}
		}

		// CASE 3
		// If only the column change, it means this is a lateral move attempt
		// ONE possible path
		if (dice.GetColumn() != destination.GetColumn()) {
			if (TraversedColumnsWithoutBlockade(dice, destination, board)) {
				pathChoice = 4;
				return true;
			}
			else {
				cout << "Invalid path in route 4" << endl;
				return false;
			}
		}

		// If moving from and to the current location, still true lol
		return true;
	}

	// The passed by reference dice is actually a temporary dice itself
	// Still passed by reference cause in case of a 90 degree turn, we want the dice state preserved to call TraversedColumnsWithoutBlockade
	bool TraversedRowsWithoutBlockade(Dice &dice, Square destination, Board board) {
		counterRowsTraversed = 0;
		do {
			// Increment if destination is in a upper row, decrement if in a lower row
			if (dice.GetRow() < destination.GetRow()) {
				dice.SetRow(1, true);
				counterRowsTraversed++;
			}
			else {
				dice.SetRow(1, false);
				counterRowsTraversed--;
			}
			
			// No need to check on the destination. If it reaches there, the traversal is considered successful
			if ((dice.GetRow() == destination.GetRow()) && (dice.GetColumn() == destination.GetColumn())) {
				return true;
			}

			// Check if there is a blockade on the path as you go.
			// If yes, the path is invalid
			if (board.IsSquareOccupied(dice.GetRow(), dice.GetColumn())) {
				return false;
			}
		} while (dice.GetRow() != destination.GetRow());
		// If it gets to this point without any false returns, it is a valid path
		return true;
	}

	// The passed by reference dice is actually a temporary dice itself
	bool TraversedColumnsWithoutBlockade(Dice &dice, Square destination, Board board) {
		counterColumnsTraversed = 0;
		do {

			// Increment if destination is in a right column, decrement if in a left column
			if (dice.GetColumn() < destination.GetColumn()) {
				dice.SetColumn(1, true);
				counterColumnsTraversed++;
			}
			else {
				dice.SetColumn(1, false);
				counterColumnsTraversed--;
			}

			// No need to check on the destination. If it reaches there, the traversal is considered successful
			if ((dice.GetRow() == destination.GetRow()) && (dice.GetColumn() == destination.GetColumn())) {
				return true;
			}

			// Check if there is a blockade on the path as you go.
			// If yes, the path is invalid
			if (board.IsSquareOccupied(dice.GetRow(), dice.GetColumn())) {
				return false;
			}
		} while (dice.GetColumn() != destination.GetColumn());
		return true;
	}


	/*

	// NEW SECTION: THE FOLLOWING FUNCTIONS WILL ACTUALLY MODIFY THE REAL GAMEBOARD.
	
	*/

	void MakeAMove(int startRow, int startCol, int endRow, int endCol, Board &board) {
		//Check if destination is valid, then if path is valid
		//Then, either make the move or log an error
		// This can be used for both human or computer after verifying that they are moving their own players.
		// Path 1 and 2 need to offset the changes done by the first function, and hence the startRow/startCol has a counter added in the second function
		if (IsValidDestination(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol))) {
			if (IsPathValid(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board)) {
				cout << "Took path " << pathChoice << endl;
				switch (pathChoice)
				{
				// First vertically, a 90 degree turn, then laterally
				case 1:
					KeepRollingVertically(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board);
					KeepRollingLaterally(*board.GetSquareResident(startRow + counterRowsTraversed, startCol), board.GetSquareAtLocation(endRow, endCol), board);
					break;
				// First laterally, a 90 degree turn, then laterally
				case 2:
					KeepRollingLaterally(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board);
					KeepRollingVertically(*board.GetSquareResident(startRow, startCol + counterColumnsTraversed), board.GetSquareAtLocation(endRow, endCol), board);
					break;
				// Vertically only
				case 3:
					KeepRollingVertically(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board);
					break;
				// Laterally only
				case 4:
					KeepRollingLaterally(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board);
					break;
				default:
					//ATTENTION: LOG ERROR SAYING THE PATH DESTINATION COULDN'T BE SET FOR SOME REASON
					break;
				}
			}
		}


		// This section was already done in the rollup, rolldown functions
		// The origin square will now be set to vacant, and the destination square pointer will be pointed to the dice
		//board.SetSquareOccupied(endRow, endCol, *board.GetSquareResident(startRow, startCol));
		//board.SetSquareVacant(startRow, startCol);
	}

	//These two following functions will modify the actual gameboard. So pass the real game objects
	// Make sure you check the validity of the path beforehand. Cause they won't do the checking
	void KeepRollingVertically(Dice &dice, Square &destination, Board &board){
		counterRowsTraversed = 0;
		do {
			if (dice.GetRow() < destination.GetRow()) {
				RollUp(dice, board);
				counterRowsTraversed++;
			}
			else {
				RollDown(dice, board);
				counterRowsTraversed--;
			}
		} while (dice.GetRow() != destination.GetRow());
	}

	void KeepRollingLaterally(Dice &dice, Square &destination, Board &board) {
		counterColumnsTraversed = 0;
		do {
			if (dice.GetColumn() < destination.GetColumn()) {
				RollRight(dice, board);
				counterColumnsTraversed++;
			}
			else {
				RollLeft(dice, board);
				counterColumnsTraversed--;
			}
		} while (dice.GetColumn() != destination.GetColumn());
	}

protected:

private:
	// Variables for Player Stats
	int score;
	int wins;		// Stats for the tournament
	int pathChoice;	// Choice of what type of path to take out of available four types

	// Variables for Player Strategies
	int tempStorage1;
	int tempStorage2;

	// Counting variables for traversals to reset back the die position
	int counterRowsTraversed;
	int counterColumnsTraversed;
};