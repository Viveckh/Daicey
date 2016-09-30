#pragma once
#include "Player.h"

class Computer : public Player {
public:
	Computer() {
	}

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
						
						// First, Try capturing the hostile opponent
						if (TryCapturingTheHostileOpponent(calculationBoard.humans[index], board)) {
							cout << "Computer just captured that hostile human opponent aiming to attack the king" << endl;
							return true;
						}
						else {
							cout << "Hostile opponent couldn't be captured. King still in danger" << endl;
						}

						// Second, Try blocking the hostile opponent
						if (TryBlockingAttack(calculationBoard.humans[index], botKingSquare, board)) {
							cout << "A blocking move has been made to avert the attack on the king" << endl;
							return true;
						}
						else {
							cout << "Any Blocking move wasn't possible at this time" << endl;
						}
						

						// Third, Try moving the king as a last resort and make sure the new position is safe
						if (TryMovingKing(botKingSquare, board)) {
							cout << "King has been moved and the threat has been averted for now" << endl;
							return true;
						}
						else {
							cout << "No safe surroundings to move the king" << endl;
						}
					}
				}

				//Check if KeySquare is under imminent threat
				if (IsValidDestination(calculationBoard.humans[index], botKeySquare)) {
					if (IsPathValid(calculationBoard.humans[index], botKeySquare, calculationBoard)) {
						// First, Try capturing the hostile opponent
						if (TryCapturingTheHostileOpponent(calculationBoard.humans[index], board)) {
							cout << "Computer just captured that hostile human opponent aiming to attack the key square" << endl;
							return true;
						}
						else {
							cout << "Hostile opponent couldn't be captured. Key square still in danger" << endl;
						}

						// Second, Try blocking the hostile opponent
						if (TryBlockingAttack(calculationBoard.humans[index], botKeySquare, board)) {
							cout << "A blocking move has been made to avert the attack on the key square" << endl;
							return true;
						}
					}
				}
			}
		}

		// STEP 3: Try capturing the opponent's other dices if kings are in safe place
		// We will not send king to capture opponents to make sure king is safe from opponent's trap, king will only capture opponent king which is facilitated above
		for (index = 0; index < TEAMSIZE; index++) {
			// Use the die to hunt only if it is not a king and hasn't been captured yet
			if (!calculationBoard.bots[index].IsKing() && !calculationBoard.bots[index].IsCaptured()) {
				for (int jindex = 0; jindex < TEAMSIZE; jindex++) {
					if (!calculationBoard.humans[jindex].IsCaptured()) {
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


	bool TryBlockingAttack(Dice hostileDice, Square squareToProtect, Board &board) {
		//Get the path choice first
		IsPathValid(hostileDice, squareToProtect, board);
		int path = GetPathChoice();

		cout << "Taking path " << path << endl;
		//Then based on that path, check which coordinate is best suited to jam the route
		switch (path) 
		{
		// First vertically, a 90 degree turn, then laterally
		case 1:
			if (FindBlockPointVertically(hostileDice, squareToProtect, board)) return true;
			if (FindBlockPointLaterally(hostileDice, squareToProtect, board)) return true;
		
		// First laterally, a 90 degree turn, then vertically
		case 2:
			if (FindBlockPointLaterally(hostileDice, squareToProtect, board)) return true;
			if (FindBlockPointVertically(hostileDice, squareToProtect, board)) return true;
			
		// Vertically only
		case 3:
			if (FindBlockPointLaterally(hostileDice, squareToProtect, board)) return true;

		// laterally only
		case 4:
			if (FindBlockPointLaterally(hostileDice, squareToProtect, board)) return true;

		default:
			break;
		}
		return false;
	}

	bool FindBlockPointVertically(Dice &hostileDice, Square &squareToProtect, Board &board) {
		do {
			//Bump up/down the coordinate to check first
			if (hostileDice.GetRow() < squareToProtect.GetRow()) {
				hostileDice.SetRow(1, true);
			}
			else {
				hostileDice.SetRow(1, false);
			}
			cout << "Checking square" << hostileDice.GetRow() << hostileDice.GetColumn() << endl;

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

	bool FindBlockPointLaterally(Dice &hostileDice, Square &squareToProtect, Board &board) {
		do {
			//Bump up/down the coordinate to check first
			if (hostileDice.GetColumn() < squareToProtect.GetColumn()) {
				hostileDice.SetColumn(1, true);
			}
			else {
				hostileDice.SetColumn(1, false);
			}
			cout << "Checking square" << hostileDice.GetRow() << hostileDice.GetColumn() << endl;
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

	bool TryMovingKing(Square kingSquare, Board &board) {
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

	bool IsInDanger(Square squareAtRisk, Board board) {
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

	const int TEAMSIZE = 9;
};