/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#include "Computer.h"

/* *********************************************************************
Function Name: Play

Purpose: Calculate the best move on behalf of the Computer Player and process the move

Parameters: board, the current state of the board where the move needs to be made

Return Value: true if a move is made successfully, false if no move made

Local Variables: 
calculationBoard, a copy of current board to use for move calculation purposes
humanKingSquare, a copy of human's king square
humanKeySquare, a copy of human's key square
botKingSquare, a copy of bot's king square
botKeySquare, a copy of bot's key square
index & jindex, counter for loops
moveCoordinates, tuple to store start and end coordinates of the best move calculated so far
minDistance, integer to store the minimum distance of a move so far
distanceFromFinalDestination,  integer to store the distance from key pieces in current calculated move

Assistance Received: none
********************************************************************* */
// Prioritizes, Calculates and makes the proper move for Computer on its turn
bool Computer::Play(Board &board) {
	printNotifications = false;

	Board calculationBoard(board);	// Using implicitly defined copy constructor
	Square humanKingSquare = calculationBoard.GetSquareAtLocation(calculationBoard.GetHumanKing().GetRow(), calculationBoard.GetHumanKing().GetColumn());
	Square humanKeySquare = calculationBoard.GetSquareAtLocation(0, 4);
	Square botKingSquare = calculationBoard.GetSquareAtLocation(calculationBoard.GetBotKing().GetRow(), calculationBoard.GetBotKing().GetColumn());
	Square botKeySquare = calculationBoard.GetSquareAtLocation(7, 4);
	int index;

	notifications.BotsThink_TryingToCaptureOpponentKeys();
	// STEP 1: Check if the opponent's king or key square can be captured. If yes, go for it!
	for (index = 0; index < TEAMSIZE; index++) {
		if (!calculationBoard.bots[index].IsCaptured()) {
			// Try to capture the king die
			if (MakeAMove(calculationBoard.bots[index].GetRow(), calculationBoard.bots[index].GetColumn(), humanKingSquare.GetRow(), humanKingSquare.GetColumn(), board, 0)) {
				return true;
			}
			// Try to capture the key square by the king die
			if (calculationBoard.bots[index].IsKing()) {
				if (MakeAMove(calculationBoard.bots[index].GetRow(), calculationBoard.bots[index].GetColumn(), humanKeySquare.GetRow(), humanKeySquare.GetColumn(), board, 0)) {
					return true;
				}
			}
		}
	}

	notifications.BotsThink_CheckingKingNKeySquareSafety();
	// STEP 2: Check if own king or keysquare is under potential attack. If yes, Save Em'
	for (index = 0; index < TEAMSIZE; index++) {
		if (!calculationBoard.humans[index].IsCaptured()) {
			// ATTENTION: If both kingSquare and KeySquare are under threat, then blocking is the best way to go about it

			//Check if KingSquare is under imminent threat
			if (IsValidDestination(calculationBoard.humans[index], botKingSquare)) {
				if (IsPathValid(calculationBoard.humans[index], botKingSquare, calculationBoard)) {
					// King is under imminent threat
					notifications.BotsThink_KeyThreatDetected("King");

					// First, Try capturing the hostile opponent
					if (TryCapturingTheHostileOpponent(calculationBoard.humans[index], board)) {
						notifications.BotsThink_HostileOpponentCaptured("King");
						return true;
					}
					else {
						notifications.BotsThink_HostileOpponentUncapturable("King");
					}

					// Second, Try blocking the hostile opponent
					if (TryBlockingAttack(calculationBoard.humans[index], botKingSquare, board)) {
						notifications.BotsThink_BlockingMoveMade();
						return true;
					}
					else {
						notifications.BotsThink_BlockingMoveNotPossible();
					}


					// Third, Try moving the king as a last resort and make sure the new position is safe
					if (TryMovingKing(botKingSquare, board)) {
						notifications.BotsThink_KingMoved();
						return true;
					}
					else {
						notifications.BotsThink_UnsafeToMoveKing();
					}
				}
			}

			// Check if KeySquare is under imminent threat by opponent's king dice
			if (calculationBoard.humans[index].IsKing()) {
				// This might actually not be helpful at all since everything that is being done here to stop opponent king has already been attempted above.
				if (IsValidDestination(calculationBoard.humans[index], botKeySquare)) {
					if (IsPathValid(calculationBoard.humans[index], botKeySquare, calculationBoard)) {
						notifications.BotsThink_KeyThreatDetected("KeySquare");
						// First, Try capturing the hostile opponent (though capturing the opponent king has already been attempted above)
						if (TryCapturingTheHostileOpponent(calculationBoard.humans[index], board)) {
							notifications.BotsThink_HostileOpponentCaptured("KeySquare");
							return true;
						}
						else {
							notifications.BotsThink_HostileOpponentUncapturable("KeySquare");
						}

						// Second, Try blocking the hostile opponent (this can't really be done since the opponent will be right next to the square.)
						if (TryBlockingAttack(calculationBoard.humans[index], botKeySquare, board)) {
							notifications.BotsThink_BlockingMoveMade();
							return true;
						}
						else {
							notifications.BotsThink_BlockingMoveNotPossible();
						}
					}
				}
			}
		}
	}

	// STEP 3: Try capturing the opponent's other dices if kings are in safe place
	// We will not send king to capture opponents to make sure king is safe from opponent's trap, king will only capture opponent king which is facilitated above
	notifications.BotsThink_TryingToCaptureOpponentDice();
	for (index = 0; index < TEAMSIZE; index++) {
		// Use the die to hunt only if it is not a king and hasn't been captured yet
		if (!calculationBoard.bots[index].IsKing() && !calculationBoard.bots[index].IsCaptured()) {
			for (int jindex = 0; jindex < TEAMSIZE; jindex++) {
				if (!calculationBoard.humans[jindex].IsCaptured()) {
					if (MakeAMove(calculationBoard.bots[index].GetRow(), calculationBoard.bots[index].GetColumn(), calculationBoard.humans[jindex].GetRow(), calculationBoard.humans[jindex].GetColumn(), board, 0)) {
						notifications.BotsThink_CapturedOpponentDice();
						return true;
					}
				}
			}
		}
	}

	// STEP 4: Go through the remaining possibilities and move a die with intentions of getting it closer to the king or key square.

	// Variables to store the best combination of origin and destination co-ordinates for a move, and also the minDistance that has been attained.
	tuple<int, int, int, int> moveCoordinates = make_tuple(0, 0, 0, 0);
	int minDistance = 99;
	int distanceFromFinalDestination = 99;

	notifications.BotsThink_SearchingOrdinaryMove();
	//For each of the die, go through every square in the gameboard and find the most optimal square to move in current state
	for (index = 0; index < TEAMSIZE; index++) {
		if (!calculationBoard.bots[index].IsKing() && !calculationBoard.bots[index].IsCaptured()) {						// For every uncaptured soldier die
			for (int row = 0; row < 8; row++) {																			// Go through the entire board and
				for (int col = 0; col < 9; col++) {
					if (IsValidDestination(calculationBoard.bots[index], calculationBoard.GetSquareAtLocation(row, col))) {			// Check if valid dest
						if (IsPathValid(calculationBoard.bots[index], calculationBoard.GetSquareAtLocation(row, col), board)) {		// Check if valid path
							if (!IsInDanger(board.GetSquareAtLocation(row, col), board)) {											// Check if safe
																																	// Compare distance to get to the king square from new location
								distanceFromFinalDestination = abs(humanKingSquare.GetRow() - row) + abs(humanKingSquare.GetColumn() - col);
								if (distanceFromFinalDestination < minDistance) {													// Check if distance to key becomes minimum & then assign
									minDistance = distanceFromFinalDestination;
									moveCoordinates = make_tuple(calculationBoard.bots[index].GetRow(), calculationBoard.bots[index].GetColumn(), row, col);	// In order: startRow, startCol, endRow, endCol
								}

								//Compare distance to get to the key square from new location
								distanceFromFinalDestination = abs(humanKeySquare.GetRow() - row) + abs(humanKeySquare.GetColumn() - col);
								if (distanceFromFinalDestination < minDistance) {													// Check if distance to key becomes minimum & then assign
									minDistance = distanceFromFinalDestination;
									moveCoordinates = make_tuple(calculationBoard.bots[index].GetRow(), calculationBoard.bots[index].GetColumn(), row, col);	// In order: startRow, startCol, endRow, endCol
								}
							}
						}
					}
				}
			}

		}
	}

	// If a better path was found from the above intensive checking
	if (minDistance < 99) {
		if (MakeAMove(get<0>(moveCoordinates), get<1>(moveCoordinates), get<2>(moveCoordinates), get<3>(moveCoordinates), board, 0)) {
			return true;
		}
	}
	return true;
}

/* *********************************************************************
Function Name: TryBlockingAttack

Purpose: To attempt to make a blocking move on a hostile dice

Parameters:
hostileDice, a Dice object that needs to be blocked
squareToProtect, the square to be protected from hostile dice
board, the board where the blocking needs to be done (passed by ref)

Return Value: true if blocking move successful, false if unsuccessful

Local Variables:
path, integer to store the potential path that will be used by the hostile dice to get to squareToProtect

Assistance Received: none
********************************************************************* */
// Attempts to block the path of an opponent who is a potential threat
bool Computer::TryBlockingAttack(Dice hostileDice, Square squareToProtect, Board &board) {
	//Get the path choice first
	IsPathValid(hostileDice, squareToProtect, board);
	int path = GetPathChoice();

	//Then based on that path, check which coordinate is best suited to jam the route
	switch (path)
	{
		// First vertically, a 90 degree turn, then laterally
	case 1:
		if (FindBlockPointVertically(hostileDice, squareToProtect, board)) return true;
		if (FindBlockPointLaterally(hostileDice, squareToProtect, board)) return true;
		break;
		// First laterally, a 90 degree turn, then vertically
	case 2:
		if (FindBlockPointLaterally(hostileDice, squareToProtect, board)) return true;
		if (FindBlockPointVertically(hostileDice, squareToProtect, board)) return true;
		break;
		// Vertically only
	case 3:
		if (FindBlockPointVertically(hostileDice, squareToProtect, board)) return true;
		break;
		// laterally only
	case 4:
		if (FindBlockPointLaterally(hostileDice, squareToProtect, board)) return true;
		break;
	default:
		break;
	}
	return false;
}

/* *********************************************************************
Function Name: FindBlockPointVertically

Purpose: To Find a block point in vertical direction to block a hostile dice
		Called in conjunction with above TryBlockingAttack() function

Parameters:
Normally Passed by reference from the above function of TryBlockingAttack
hostileDice, a Dice object that needs to be blocked (passed by ref)
squareToProtect, the square to be protected from hostile dice (passed by ref)
board, the board where the blocking needs to be done (passed by ref)

Return Value: true if blocking successful, false if unsuccessful

Local Variables: none

Assistance Received: none
********************************************************************* */
// Finds a co-ordinate to place blocking dice on the vertical route
bool Computer::FindBlockPointVertically(Dice &hostileDice, Square &squareToProtect, Board &board) {
	do {
		//Bump up/down the coordinate to check first
		if (hostileDice.GetRow() < squareToProtect.GetRow()) {
			hostileDice.SetRow(1, true);
		}
		else {
			hostileDice.SetRow(1, false);
		}

		// See if any of the own dies can take that spot and block
		for (int i = 0; i < TEAMSIZE; i++) {
			if (!board.bots[i].IsKing() && !board.bots[i].IsCaptured()) {
				if (MakeAMove(board.bots[i].GetRow(), board.bots[i].GetColumn(), hostileDice.GetRow(), hostileDice.GetColumn(), board, 0)) {
					return true;
				}
			}
		}
	} while (hostileDice.GetRow() != squareToProtect.GetRow());
	return false;
}

/* *********************************************************************
Function Name: FindBlockPointLaterally

Purpose: To Find a block point in lateral direction to block a hostile dice
Called in conjunction with above TryBlockingAttack() function

Parameters:
Normally Passed by reference from the above function of TryBlockingAttack
hostileDice, a Dice object that needs to be blocked (passed by ref)
squareToProtect, the square to be protected from hostile dice (passed by ref)
board, the board where the blocking needs to be done (passed by ref)

Return Value: true if blocking successful, false if unsuccessful

Local Variables: none

Assistance Received: none
********************************************************************* */
// Finds a co-ordinate to place blocking dice on the lateral route
bool Computer::FindBlockPointLaterally(Dice &hostileDice, Square &squareToProtect, Board &board) {
	do {
		//Bump up/down the coordinate to check first
		if (hostileDice.GetColumn() < squareToProtect.GetColumn()) {
			hostileDice.SetColumn(1, true);
		}
		else {
			hostileDice.SetColumn(1, false);
		}

		// See if any of the own dies can take that spot and block
		for (int i = 0; i < TEAMSIZE; i++) {
			if (!board.bots[i].IsKing() && !board.bots[i].IsCaptured()) {
				if (MakeAMove(board.bots[i].GetRow(), board.bots[i].GetColumn(), hostileDice.GetRow(), hostileDice.GetColumn(), board, 0)) {
					return true;
				}
			}
		}
	} while (hostileDice.GetColumn() != squareToProtect.GetColumn());
	return false;
}

/* *********************************************************************
Function Name: TryCapturingTheHostileOpponent

Purpose: To try and capture a hostile opponent

Parameters:
hostileDice, the hostile dice that needs to be captured
board, the game board in context (passed by ref)

Return Value: true if capture successful, false if unsuccessful

Local Variables: none

Assistance Received: none
********************************************************************* */
// Tries capturing a hostile opponent who is a potential threat
bool Computer::TryCapturingTheHostileOpponent(Dice hostileDice, Board &board) {
	for (int i = 0; i < TEAMSIZE; i++) {
		if (!board.bots[i].IsCaptured()) {
			// Try to capture the king die
			if (MakeAMove(board.bots[i].GetRow(), board.bots[i].GetColumn(), hostileDice.GetRow(), hostileDice.GetColumn(), board, 0)) {
				return true;
			}
		}
	}
	return false;
}

/* *********************************************************************
Function Name: TryMovingKing

Purpose: To move the king to protect from opponent attack

Parameters:
kingSquare, the square where the king is located
board, the game board in context

Return Value: true if the move successful, false if unsuccessful

Local Variables: none

Assistance Received: none
********************************************************************* */
// Tries moving the king to a secure position
bool Computer::TryMovingKing(Square kingSquare, Board &board) {
	// Check if it is possible/safe to move the king upwards in the board
	if (kingSquare.GetRow() < 7) {
		if (IsValidDestination(*kingSquare.GetResident(), board.GetSquareAtLocation(kingSquare.GetRow() + 1, kingSquare.GetColumn()))) {
			if (!IsInDanger(board.GetSquareAtLocation(kingSquare.GetRow() + 1, kingSquare.GetColumn()), board)) {
				if (MakeAMove(kingSquare.GetRow(), kingSquare.GetColumn(), kingSquare.GetRow() + 1, kingSquare.GetColumn(), board, 0)) {
					return true;
				}
			}
		}
	}

	// Check if it is possible/safe to move the king downwards in the board
	if (kingSquare.GetRow() > 0) {
		if (IsValidDestination(*kingSquare.GetResident(), board.GetSquareAtLocation(kingSquare.GetRow() - 1, kingSquare.GetColumn()))) {
			if (!IsInDanger(board.GetSquareAtLocation(kingSquare.GetRow() - 1, kingSquare.GetColumn()), board)) {
				if (MakeAMove(kingSquare.GetRow(), kingSquare.GetColumn(), kingSquare.GetRow() - 1, kingSquare.GetColumn(), board, 0)) {
					return true;
				}
			}
		}
	}

	// Check if it is possible/safe to move the king rightwards in the board
	if (kingSquare.GetColumn() < 8) {
		if (IsValidDestination(*kingSquare.GetResident(), board.GetSquareAtLocation(kingSquare.GetRow(), kingSquare.GetColumn() + 1))) {
			if (!IsInDanger(board.GetSquareAtLocation(kingSquare.GetRow(), kingSquare.GetColumn() + 1), board)) {
				if (MakeAMove(kingSquare.GetRow(), kingSquare.GetColumn(), kingSquare.GetRow(), kingSquare.GetColumn() + 1, board, 0)) {
					return true;
				}
			}
		}
	}

	// Check if it is possible/safe to move the king leftwards in the board
	if (kingSquare.GetColumn() > 0) {
		if (IsValidDestination(*kingSquare.GetResident(), board.GetSquareAtLocation(kingSquare.GetRow(), kingSquare.GetColumn() - 1))) {
			if (!IsInDanger(board.GetSquareAtLocation(kingSquare.GetRow(), kingSquare.GetColumn() - 1), board)) {
				if (MakeAMove(kingSquare.GetRow(), kingSquare.GetColumn(), kingSquare.GetRow(), kingSquare.GetColumn() - 1, board, 0)) {
					return true;
				}
			}
		}
	}
	return false;
}

/* *********************************************************************
Function Name: IsInDanger

Purpose: To check and see if the given square is at risk in the given gameboard

Parameters:
squareAtRisk, the square that needs to be checked if it is in danger
board, the game board in context

Return Value: true if square at risk, false if safe

Local Variables: none

Assistance Received: none
********************************************************************* */
// Checks if a given square is at risk from opponent dices
bool Computer::IsInDanger(Square squareAtRisk, Board board) {
	for (int index = 0; index < TEAMSIZE; index++) {
		// This even considers threat from the king and just not normal soldier attacks
		if (!board.humans[index].IsCaptured()) {
			if (IsValidDestination(board.humans[index], squareAtRisk)) {
				if (IsPathValid(board.humans[index], squareAtRisk, board)) {
					return true;
				}
			}
		}
	}
	return false;
}