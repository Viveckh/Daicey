//
// Displays and serializes the Game Board
//

#pragma once
#include "stdafx.h"
#include "Square.h"
#include "Dice.h"
#include "Board.h"

class BoardView {
public:

	// Default Constructor
	BoardView() {}

	void DrawBoard(Board &board) {
		//Drawing the board inverted cause zero row is supposed to be at the bottom
		cout << endl;
		for (int row = 7; row >= 0; row--) {
			cout << abs(row + 1) << "\t";
			for (int col = 0; col < 9; col++) {
				if (board.IsSquareOccupied(row, col)) {
					//ATTENTION: Need to work on this after establishing a link between a square and a dice.
					//Try creating a dice within the square class and see if that link assists it in some way.
					//Also add isHuman/isComputer functions to find out if a dice is operated by a human or a comp

					if (board.GetSquareResident(row, col)->IsBotOperated()) {
						cout << "C";
						cout << board.GetSquareResident(row, col)->GetTop() << board.GetSquareResident(row, col)->GetLeft() << "\t";
					}
					else {
						cout << "H";
						cout << board.GetSquareResident(row, col)->GetTop() << board.GetSquareResident(row, col)->GetRight() << "\t";
					}
					
				}
				else {
					cout << "-\t";
				}
			}
			cout << endl;
		}
		cout << "\t1\t2\t3\t4\t5\t6\t7\t8\t9" << endl << endl;
	}
	

	// Print out the captured players
	void ViewNonCapturedDice(Board &board) {
		cout << "Non Captured Human indexes: ";
		for (int i = 0; i < 9; i++) {
			if (!board.humans[i].IsCaptured()) {
				cout << i << " ";
			}
		}
		cout << endl;

		cout << "Non Captured Bot indexes: ";
		for (int j = 0; j < 9; j++) {
			if (!board.bots[j].IsCaptured()) {
				cout << j << " ";
			}
		}
		cout << endl;
	}

private:
};