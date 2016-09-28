#pragma once
#include "Player.h"

class Computer : public Player {
public:
	Computer() {}

	bool Play(Board &board) {
	
		Board calculationBoard(board);	// Using implicitly defined copy constructor
		Square humanKingSquare = calculationBoard.GetSquareAtLocation(calculationBoard.GetHumanKing().GetRow(), calculationBoard.GetHumanKing().GetColumn());
		Square humanKeySquare = calculationBoard.GetSquareAtLocation(0, 4);
		Square botKingSquare = calculationBoard.GetSquareAtLocation(calculationBoard.GetBotKing().GetRow(), calculationBoard.GetBotKing().GetColumn());
		Square botKeySquare = calculationBoard.GetSquareAtLocation(7, 4);
		int index;

		// STEP 1: Check if the opponent's king or key square can be captured. If yes, go for it!
		for (index = 0; index < TEAMSIZE; index++) {
			if (!calculationBoard.bots[index].IsCaptured()) {
				// Try to capture the king die
				if (MakeAMove(calculationBoard.bots[index].GetRow(), calculationBoard.bots[index].GetColumn(), humanKingSquare.GetRow(), humanKingSquare.GetColumn(), board, 0)) {
					return true;
				}
				// Try to capture the key square
				if (MakeAMove(calculationBoard.bots[index].GetRow(), calculationBoard.bots[index].GetColumn(), humanKeySquare.GetRow(), humanKeySquare.GetColumn(), board, 0)) {
					return true;
				}
			}
		}
		
		// STEP 2: Check if own king or keysquare is under potential attack. If yes, Save Em'
		for (index = 0; index < TEAMSIZE; index++) {
			if (!calculationBoard.humans[index].IsCaptured()) {
				// ATTENTION: If both kingSquare and KeySquare are under threat, then blocking is the best way to go about it
				
				//Check if KingSquare is under imminent threat
				if (IsValidDestination(calculationBoard.humans[index], botKingSquare)) {
					if (IsPathValid(calculationBoard.humans[index], botKingSquare, calculationBoard)) {
						// Try capturing the hostile opponent first
						if (TryCapturingTheHostileOpponent(calculationBoard.humans[index], board)) {
							cout << "Computer just captured that hostile human opponent aiming to attack the king" << endl;
							return true;
						}
						else {
							cout << "Our King is still in danger" << endl;
						}

						// ATTENTION: Second, Try blocking the hostile opponent

						// ATTENTION: Third, Try moving the king as a last resort and make sure the new position is safe
					}
				}

				//Check if KeySquare is under imminent threat
				if (IsValidDestination(calculationBoard.humans[index], botKeySquare)) {
					if (IsPathValid(calculationBoard.humans[index], botKeySquare, calculationBoard)) {
						// Do something related to blocking
						cout << "Our Key Square is in danger" << endl;
					}
				}
			}
		}

		// Try capturing the opponent's other dices if kings are in safe place
		// We will not send king to capture opponents to make sure king is safe from opponent's trap, king will only capture opponent king which is facilitated above
		for (index = 0; index < TEAMSIZE; index++) {
			// Use the die to hunt only if it is not a king and hasn't been captured yet
			if (index != 4 && !calculationBoard.bots[index].IsCaptured()) {
				for (int jindex = 0; jindex < TEAMSIZE; jindex++) {
					if (!calculationBoard.humans[index].IsCaptured()) {
						if (MakeAMove(calculationBoard.bots[index].GetRow(), calculationBoard.bots[index].GetColumn(), calculationBoard.humans[jindex].GetRow(), calculationBoard.humans[jindex].GetColumn(), board, 0)) {
							return true;
						}
					}
				}
			}
		}


		return true;
		// Calculate all the possibilities and make a move
	}

private:

	// in case of a hostile opponent found, try capturing it
	bool TryCapturingTheHostileOpponent(Dice hostileDice, Board &board) {
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

	const int TEAMSIZE = 9;
};