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
	BoardView() {
		fileName = "C:\\Duell_LastGameSerialization.txt";
	}

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
					}
					else {
						cout << "H";
					}
					cout << board.GetSquareResident(row, col)->GetTop() << board.GetSquareResident(row, col)->GetRight() << "\t";
				}
				else {
					cout << "-\t";
				}
			}
			cout << endl;
		}
		cout << "\t1\t2\t3\t4\t5\t6\t7\t8\t9" << endl << endl;
	}
	
	
	// Stores the game state in a multidimensional string array.
	void UpdateSerializedBoard(Board &board) {
		for (int row = 7; row >= 0; row--) {
			for (int col = 0; col < 9; col++) {
				serializedGameBoard[row][col].assign("0");
				if (board.IsSquareOccupied(row, col)) {
					if (board.GetSquareResident(row, col)->IsBotOperated()) {
						serializedGameBoard[row][col].assign("C");
					}
					else {
						serializedGameBoard[row][col].assign("H");
					}
					// Append the top and right value of the occupying dice
					serializedGameBoard[row][col].append(to_string(board.GetSquareResident(row, col)->GetTop()));
					serializedGameBoard[row][col].append(to_string(board.GetSquareResident(row, col)->GetRight()));
				}
				//cout << serializedGameBoard[row][col] << "\t";
			}
			//cout << endl;
		}
	}

	// Writing serialized game state along with tournament history results to file
	bool WriteToFile(int botWins, int humanWins, string nextPlayer) {
		// ADD TRUE/FALSE
		
		ofstream writer;
		writer.open(fileName, ofstream::out | ofstream::trunc);
		if (writer.fail()) {
			return false;
		}

		// Writing the board first
		for (int row = 7; row >= 0; row--) {
			for (int col = 0; col < 9; col++) {
				writer << serializedGameBoard[row][col] << '\t';
			}
			writer << endl;
		}

		// Writing the number of wins and next Player
		writer << "Computer Wins: " << botWins << endl;
		writer << "Human Wins: " << humanWins << endl;
		writer << "Next Player: " << nextPlayer << endl;
		writer.close();
		return true;
	}

	// Print out the captured players
	void ViewCapturedDice(Board &board) {
		cout << "Captured Human indexes: ";
		for (int i = 0; i < 9; i++) {
			if (board.humans[i].IsCaptured()) {
				cout << i << " ";
			}
		}
		cout << endl;

		cout << "Captured Bot indexes: ";
		for (int j = 0; j < 9; j++) {
			if (board.bots[j].IsCaptured()) {
				cout << j << " ";
			}
		}
		cout << endl;
	}

private:
	string serializedGameBoard[8][9];
	string fileName;
};