#pragma once
#include "stdafx.h"
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

	bool ReadAFile(string fileName, Board &board, int &botWins, int &humanWins, string &nextPlayer) {
		ifstream reader;
		string line;
		istringstream lineStream;
		string temp;

		reader.open(fileName, ofstream::in);
		if (reader.fail()) {
			return false;
		}
		//Reading the line containing "Board" text
		getline(reader, line);
		lineStream.clear();

		// Reading the board
		for (int row = 7; row >= 0; row--) {
			getline(reader, line);
			//stringstream lineStream(line);
			lineStream.clear();
			lineStream.str(line);
			lineStream >> noskipws;	//Initializing skip whitespaces
			for (int col = 0; col < 9; col++) {
				//getline(lineStream, serializedGameBoard[row][col], '\t');
				lineStream >> ws >> serializedGameBoard[row][col] >> ws;	// ws is whitespace skipper
				cout << serializedGameBoard[row][col] << "\t";
			}
			cout << endl;
		}

		// Reading the scores and turns
		while (!reader.eof()) {
			getline(reader, line);
			//If line is empty or full of spaces, skip it
			if (line.empty() || _All_of(line.begin(), line.end(), isspace)) {
				continue;
			}
			
			transform(line.begin(), line.end(), line.begin(), ::tolower);	//Convert everything to lowercase
			lineStream.clear();
			lineStream.str(line);
			//lineStream >> noskipws;	//Initializing skip whitespaces
			if (line.find("computer wins") != string::npos) {
				// The last part of the string is the computer score
				while (!lineStream.eof()) {
					lineStream >> ws >> temp >> ws;
				}
				botWins = stoi(temp);
			}
			
			if (line.find("human wins") != string::npos) {
				// The last part of the string is the human score
				while (!lineStream.eof()) {
					lineStream >> ws >> temp >> ws;
				}
				humanWins = stoi(temp);
			}

			if (line.find("next player") != string::npos) {
				if (line.find("computer") != string::npos) {
					nextPlayer = "Computer";
				}
				else {
					nextPlayer = "Human";
				}
			}
		}
		
		reader.close();
		
		SetBoard(board);
		
		return true;
	}

private:
	void SetBoard(Board &board) {
		int humanCount = 0;
		int botCount = 0;

		// Go through every index of the serializedGameBoard stored in the string array and update the actual game board
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 9; col++) {
				if (serializedGameBoard[row][col].at(0) == '0') {
					board.SetSquareVacant(row, col);
					continue;
				}

				if (serializedGameBoard[row][col].at(0) == 'C') {
					board.bots[botCount].SetBotControl(true);
					board.bots[botCount].SetCaptured(false);
					board.bots[botCount].SetCoordinates(row, col);
					board.bots[botCount].SetTop(int(serializedGameBoard[row][col].at(1)) - int('0'));		// Subtracting ascii of 0 to get the actual number on the index
					board.bots[botCount].SetRight(int(serializedGameBoard[row][col].at(2)) - int('0'));		// Subtracting ascii of 0 to get the actual number on the index
					
					if (board.bots[botCount].GetTop() == 1 && board.bots[botCount].GetRight() == 1) {
						board.bots[botCount].SetKing(true);
					}

					board.SetSquareOccupied(row, col, board.bots[botCount]);
					botCount++;
				}

				if (serializedGameBoard[row][col].at(0) == 'H') {
					board.humans[humanCount].SetBotControl(false);
					board.humans[humanCount].SetCaptured(false);
					board.humans[humanCount].SetCoordinates(row, col);
					board.humans[humanCount].SetTop(int(serializedGameBoard[row][col].at(1)) - int('0'));	// Subtracting ascii of 0 to get the actual number on the index
					board.humans[humanCount].SetRight(int(serializedGameBoard[row][col].at(2)) - int('0')); // Subtracting ascii of 0 to get the actual number on the index

					if (board.humans[humanCount].GetTop() == 1 && board.humans[humanCount].GetRight() == 1) {
						board.humans[humanCount].SetKing(true);
					}

					board.SetSquareOccupied(row, col, board.humans[humanCount]);
					humanCount++;
				}
			}
		}
		while (botCount != 9) {
			board.bots[botCount].SetCaptured(true);
			botCount++;
		}
		while (humanCount != 9) {
			board.humans[humanCount].SetCaptured(true);
			humanCount++;
		}
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

	string serializedGameBoard[8][9];
	string fileName;
};