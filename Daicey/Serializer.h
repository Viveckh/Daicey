#pragma once
#include "Board.h"

class Serializer {
public:
	Serializer() {
		fileName = "C:\\Duell_LastGameSerialization.txt";
	}

	// Writing serialized game state along with tournament history results to file
	bool WriteToFile(Board &board, int botWins, int humanWins, string nextPlayer) {
		// Update the multidimensional string array for serialization first
		UpdateSerializedBoard(board);

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

private:
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

	string serializedGameBoard[8][9];
	string fileName;
};