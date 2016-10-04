/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#include "Player.h"

// Initializing static variable for toggling notifications print
bool Player::printNotifications = true;

// Default Constructor
Player::Player() {
	pathChoice = 0;
	multiplePathPossible = false;
	tempStorage1 = 0;
	tempStorage2 = 0;
	counterRowsTraversed = 0;
	counterColumnsTraversed = 0;
}

/*
//
// NEW SECTION: THESE FUNCTIONS CAN BE USED TO CHANGE STATES EITHER IN A TEMPORARY OR A PERMANENT GAME BOARD
//
*/

/* *********************************************************************
Function Name: RollUp

Purpose: To Roll up a dice by one row and change the appropriate dice & board values accordingly to reflect changes

Parameters:
dice, the dice to be moved (passed by ref)
board, the board in context (passed by ref)

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Does one up roll of the dice
void Player::RollUp(Dice &dice, Board &board) {

	//if (dice.GetRow() < 7) {}		Put this wrapper around the entire function to validate coordinates
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
		printNotifications ? notifications.Msg_CapturedAnOpponent() : notifications.Msg_NoMsg();
	}

	board.SetSquareOccupied(dice.GetRow(), dice.GetColumn(), dice);
}

/* *********************************************************************
Function Name: RollDown

Purpose: To Roll down a dice by one row and change the appropriate dice & board values accordingly to reflect changes

Parameters:
dice, the dice to be moved (passed by ref)
board, the board in context (passed by ref)

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Does one down roll of the dice
void Player::RollDown(Dice &dice, Board &board) {
	//if (dice.GetRow() > 0) {}		Put this wrapper around the entire function to validate coordinates
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
		printNotifications ? notifications.Msg_CapturedAnOpponent() : notifications.Msg_NoMsg();
	}

	board.SetSquareOccupied(dice.GetRow(), dice.GetColumn(), dice);
}

/* *********************************************************************
Function Name: RollLeft

Purpose: To Roll left a dice by one column and change the appropriate dice & board values accordingly to reflect changes

Parameters:
dice, the dice to be moved (passed by ref)
board, the board in context (passed by ref)

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Does one left roll of the dice
void Player::RollLeft(Dice &dice, Board &board) {
	// if (dice.GetColumn() > 0) {}		Put this wrapper around the entire function to validate coordinates
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
		printNotifications ? notifications.Msg_CapturedAnOpponent() : notifications.Msg_NoMsg();
	}

	board.SetSquareOccupied(dice.GetRow(), dice.GetColumn(), dice);
}

/* *********************************************************************
Function Name: RollRight

Purpose: To Roll right a dice by one column and change the appropriate dice & board values accordingly to reflect changes

Parameters:
dice, the dice to be moved (passed by ref)
board, the board in context (passed by ref)

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Does one right roll of the dice
void Player::RollRight(Dice &dice, Board &board) {
	// if (dice.GetColumn() < 8) {}		Put this wrapper around the entire function to validate coordinates
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
		printNotifications ? notifications.Msg_CapturedAnOpponent() : notifications.Msg_NoMsg();
	}

	board.SetSquareOccupied(dice.GetRow(), dice.GetColumn(), dice);
}

/*
//
// NEW SECTION: THE FOLLOWING FUNCTIONS WILL FORM TEMPORARY PASSED-BY-VALUE GAME OBJECTS AND CHECK THE VALIDITY OF ROUTE/DESTINATION
//
*/

/* *********************************************************************
Function Name: IsValidDestination

Purpose: To check if the given square is a valid destination distance-wise for the given dice

Parameters:
dice, the dice as the origin
destination, the destination square

Return Value: true if a valid destination, false if not

Local Variables: none

Assistance Received: none
********************************************************************* */
// Checks if the destination is a valid one
bool Player::IsValidDestination(Dice dice, Square destination) {

	// Destination square should either be null or contain a dice of different team other than the one moving.
	if ((destination.GetResident() == NULL) || (destination.GetResident()->IsBotOperated() && !dice.IsBotOperated()) || (!destination.GetResident()->IsBotOperated() && dice.IsBotOperated())) {

		// (Destination row - source row) + (Destination col - source col) gives the distance between the source and destination squares
		if (dice.GetTop() == abs(destination.GetRow() - dice.GetRow()) + abs(destination.GetColumn() - dice.GetColumn())) {
			return true;
		}
		else {
			printNotifications ? notifications.Msg_InvalidMove() : notifications.Msg_NoMsg();
		}
	}
	else {
		printNotifications ? notifications.Msg_RunningOverOwnDice() : notifications.Msg_NoMsg();
	}
	return false;
}

/* *********************************************************************
Function Name: IsPathValid

Purpose: To find an appropriate path, if exists, between the origin and destination
		 It sets the pathChoice varible with the proper path number
		 1 for vertical & lateral, 2 for lateral & vertical, 3 for vertical only, 4 for lateral only

Parameters:
dice, the dice as the origin
destination, the destination square
board, the board in context

Return Value: true if a path exists, false if not

Local Variables: none

Assistance Received: none
********************************************************************* */
// Checks the validity of a path to get from origin to destination square
bool Player::IsPathValid(Dice dice, Square destination, Board board) {
	// The temporary dice jumps from one square to the other and checks if it is already occupied

	counterRowsTraversed = 0;
	counterColumnsTraversed = 0;
	pathChoice = 0;
	multiplePathPossible = false;

	// CASE 1
	// If both the rows & columns differ in the destination, it means this is a frontal-lateral combined move attempt
	// TWO possible paths
	// ATTENTION: Need to work on this
	if ((dice.GetRow() != destination.GetRow()) && (dice.GetColumn() != destination.GetColumn())) {

		//Only one path needs to pass
		// Path 1 - First row traversal, then Column
		if (TraversedRowsWithoutBlockade(dice, destination, board) && TraversedColumnsWithoutBlockade(dice, destination, board)) {
			pathChoice = 1;
		}

		// In case we need to check the validity of second path, the dice needs to be reverted back to its original spot 
		// based on the counters gathered while traversing above
		dice.SetRow(counterRowsTraversed, false);
		dice.SetColumn(counterColumnsTraversed, false);

		// Path 2 - First column traversal, then row
		if (TraversedColumnsWithoutBlockade(dice, destination, board) && TraversedRowsWithoutBlockade(dice, destination, board)) {
			// If the previous path was valid too, then there are surely two paths
			if (pathChoice == 1) {
				multiplePathPossible = true;
				return true;
			}

			pathChoice = 2;
			return true;
		}

		// If the first path was the only one valid
		if (pathChoice == 1) {
			return true;
		}

		//If both the path couldn't return true, then the path is invalid
		printNotifications ? notifications.Msg_NoValidPath() : notifications.Msg_NoMsg();
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
			printNotifications ? notifications.Msg_NoValidPath() : notifications.Msg_NoMsg();
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
			printNotifications ? notifications.Msg_NoValidPath() : notifications.Msg_NoMsg();
			return false;
		}
	}

	// If moving from and to the current location, still true lol
	return true;
}

/* *********************************************************************
Function Name: TraversedRowsWithoutBlockade

Purpose: To traverse rows and make sure blockade don't exist
		 Used in conjunction with IsPathValid() function.
		The passed by reference values are actually the temporary values passed by value in IsPathValid() function

Parameters:
The passed by reference values are actually the temporary values passed by value in IsPathValid() function
dice, the dice as the origin
destination, the destination square
board, the board in context

Return Value: true if traversal along rows successful without blockade, false otherwise

Local Variables: none

Assistance Received: none
********************************************************************* */
// Returns true if traversal is successful without blockade until the destination row (The passed by reference dice is actually a temporary dice itself)
bool Player::TraversedRowsWithoutBlockade(Dice &dice, Square destination, Board board) {
	// Still passed by reference cause in case of a 90 degree turn, we want the dice state preserved to call TraversedColumnsWithoutBlockade
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

/* *********************************************************************
Function Name: TraversedColumnsWithoutBlockade

Purpose: To traverse columns and make sure blockade don't exist
		Used in conjunction with IsPathValid() function.
		The passed by reference values are actually the temporary values passed by value in IsPathValid() function

Parameters:
The passed by reference values are actually the temporary values passed by value in IsPathValid() function
dice, the dice as the origin
destination, the destination square
board, the board in context

Return Value: true if traversal along columns successful without blockade, false otherwise

Local Variables: none

Assistance Received: none
********************************************************************* */
// Returns true if traversal is successful without blockade until the destination column (The passed by reference dice is actually a temporary dice itself)
bool Player::TraversedColumnsWithoutBlockade(Dice &dice, Square destination, Board board) {
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
//
// NEW SECTION: THE FOLLOWING FUNCTIONS WILL ACTUALLY MODIFY THE REAL GAMEBOARD.
//
*/

/* *********************************************************************
Function Name: MakeAMove

Purpose: To validate the move from and to the given coordinates, and process it if valid

Parameters:
startRow, integer value of start row coordinate
startCol, integer value of start column coordinate
endRow, integer value of end row coordinate
endCol, integer value of end Column coordinate
board, the board in context where the move is to be made (passed by ref)
path, the path selected by the human player in case of a 90 degree turn, if any

Return Value: true if move successful, false otherwise

Local Variables:
topValueAtStart, the top value of the dice at starting coordinate
rightValueAtStart, the right value of the dice at starting coordinate

Assistance Received: none
********************************************************************* */
// Checks the validity of a given move, and performs it on the gameboard if valid
bool Player::MakeAMove(int startRow, int startCol, int endRow, int endCol, Board &board, bool helpModeOn, int path) {
	//Check if destination is valid, then if path is valid
	//Then, either make the move or log an error
	// This can be used for both human or computer after verifying that they are moving their own players.
	// Path 1 and 2 need to offset the changes done by the first function, and hence the startRow/startCol has a counter added in the second function
	if (IsValidDestination(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol))) {
		if (IsPathValid(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board)) {
			// If help mode is on, no need to make the actual move, return true here and print suggestion
			if (helpModeOn) {
				notifications.Msg_HelpModeRecommendedMove(startRow + 1, startCol + 1, endRow + 1, endCol + 1, pathChoice);
				return true;
			}
			
			int topValueAtStart = board.GetSquareResident(startRow, startCol)->GetTop();
			int rightValueAtStart = board.GetSquareResident(startRow, startCol)->GetRight();

			// If user has input a preferred path in case of a 90 degree turn, we need to honor that
			if (path != 0) {
				if (path == 1 && pathChoice == 1) {
					pathChoice = 1;
				}

				if ((path == 2) && (pathChoice == 2 || multiplePathPossible)) {
					pathChoice = 2;
				}

				// Display a notification if the user's choice of path wasn't valid and had to be superceded by the next best route
				if (path != pathChoice) {
					printNotifications ? notifications.Msg_90DegreePathSelectionNotProcessed() : notifications.Msg_NoMsg();
				}
			}

			switch (pathChoice)
			{
				// First vertically, a 90 degree turn, then laterally
			case 1:
				KeepRollingVertically(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board);
				KeepRollingLaterally(*board.GetSquareResident(startRow + counterRowsTraversed, startCol), board.GetSquareAtLocation(endRow, endCol), board);
				notifications.Msg_NatureOfPathTaken("VERTICAL & LATERAL");
				break;
				// First laterally, a 90 degree turn, then vertically
			case 2:
				KeepRollingLaterally(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board);
				KeepRollingVertically(*board.GetSquareResident(startRow, startCol + counterColumnsTraversed), board.GetSquareAtLocation(endRow, endCol), board);
				notifications.Msg_NatureOfPathTaken("LATERAL & VERTICAL");
				break;
				// Vertically only
			case 3:
				KeepRollingVertically(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board);
				notifications.Msg_NatureOfPathTaken("VERTICAL");
				break;
				// Laterally only
			case 4:
				KeepRollingLaterally(*board.GetSquareResident(startRow, startCol), board.GetSquareAtLocation(endRow, endCol), board);
				notifications.Msg_NatureOfPathTaken("LATERAL");
				break;
			default:
				//ATTENTION: LOG ERROR SAYING THE PATH DESTINATION COULDN'T BE SET FOR SOME REASON
				notifications.Msg_CrashedWhileMakingTheMove();
				return false;
			}
			notifications.Msg_MoveDescription(startRow + 1, startCol + 1, endRow + 1, endCol + 1, topValueAtStart, rightValueAtStart, board.GetSquareResident(endRow, endCol)->GetTop(), board.GetSquareResident(endRow, endCol)->GetRight(), board.GetSquareResident(endRow, endCol)->IsBotOperated());	// +1 To compensate for 1 offset in the array indexes
			return true;
		}
	}
	return false;
}

//These two following functions will modify the actual gameboard. So pass the real game objects
// Make sure you check the validity of the path beforehand. Cause they won't do the checking

/* *********************************************************************
Function Name: KeepRollingVertically

Purpose: To continue the move vertically until the dice reaches the destination row
		Used in conjunction with the MakeAMove() function
		This modifies the actually gameboard in context, so be careful while using it

Parameters:
dice, the dice of origin
destination, the destination square to be reached
board, the board in context (will be modified permanently)

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Rolls the dice vertically until it is in the destination row
void Player::KeepRollingVertically(Dice &dice, Square &destination, Board &board) {
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

/* *********************************************************************
Function Name: KeepRollingLaterally

Purpose: To continue the move laterally until the dice reaches the destination column
Used in conjunction with the MakeAMove() function
This modifies the actually gameboard in context, so be careful while using it

Parameters:
dice, the dice of origin
destination, the destination square to be reached
board, the board in context (will be modified permanently)

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Rolls the die laterally until it is in the destination column
void Player::KeepRollingLaterally(Dice &dice, Square &destination, Board &board) {
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

