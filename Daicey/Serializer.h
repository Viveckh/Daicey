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
		// This one is for going through the Human's player dices
		int humanCount = 0;
		int botCount = 0;

		// This one is for temporary purposes 
		int tempHumanIndex = 0;
		int tempBotIndex = 0;

		// Go through every index of the serializedGameBoard stored in the string array and update the actual game board
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 9; col++) {
				// If the square is empty
				if (serializedGameBoard[row][col].at(0) == '0') {
					board.SetSquareVacant(row, col);
					continue;
				}

				// If the square is occupied by computer dice
				if (serializedGameBoard[row][col].at(0) == 'C') {
					// Check if the dice at hand is a king, and determine the index accordingly
					if (serializedGameBoard[row][col].at(1) == '1' && serializedGameBoard[row][col].at(2) == '1') {
						// it is a king, so assign the king index
						tempBotIndex = 4;
					}
					else {
						tempBotIndex = botCount;
					}

					// Setting bot properties
					board.bots[tempBotIndex].SetBotControl(true);
					board.bots[tempBotIndex].SetCaptured(false);
					board.bots[tempBotIndex].SetCoordinates(row, col);
					board.bots[tempBotIndex].SetTop(int(serializedGameBoard[row][col].at(1)) - int('0'));		// Subtracting ascii of 0 to get the actual number on the index
					board.bots[tempBotIndex].SetRight(int(serializedGameBoard[row][col].at(2)) - int('0'));		// Subtracting ascii of 0 to get the actual number on the index
					board.bots[tempBotIndex].SetRemainingSides(board.bots[tempBotIndex].GetTop(), board.bots[tempBotIndex].GetRight());
	
					if (board.bots[tempBotIndex].GetTop() == 1 && board.bots[tempBotIndex].GetRight() == 1) {
						board.bots[tempBotIndex].SetKing(true);
					}

					// setting square properties
					board.SetSquareOccupied(row, col, board.bots[tempBotIndex]);
					
					// Incrementing counts
					botCount++;
					if (botCount == 4) { botCount++; }	// This index is reserved for the king
				}

				// If the square is occupied by human dice
				if (serializedGameBoard[row][col].at(0) == 'H') {
					// Check if the dice at hand is a king, and determine the index accordingly
					if (serializedGameBoard[row][col].at(1) == '1' && serializedGameBoard[row][col].at(2) == '1') {
						// it is a king, so assign the king index
						tempHumanIndex = 4;
					}
					else {
						tempHumanIndex = botCount;
					}

					// Setting human properties
					board.humans[tempHumanIndex].SetBotControl(false);
					board.humans[tempHumanIndex].SetCaptured(false);
					board.humans[tempHumanIndex].SetCoordinates(row, col);
					board.humans[tempHumanIndex].SetTop(int(serializedGameBoard[row][col].at(1)) - int('0'));	// Subtracting ascii of 0 to get the actual number on the index
					board.humans[tempHumanIndex].SetRight(int(serializedGameBoard[row][col].at(2)) - int('0')); // Subtracting ascii of 0 to get the actual number on the index
					board.humans[tempHumanIndex].SetRemainingSides(board.humans[tempHumanIndex].GetTop(), board.humans[tempHumanIndex].GetRight());

					if (board.humans[tempHumanIndex].GetTop() == 1 && board.humans[tempHumanIndex].GetRight() == 1) {
						board.humans[tempHumanIndex].SetKing(true);
					}

					// setting square properties
					board.SetSquareOccupied(row, col, board.humans[tempHumanIndex]);
					
					// incrementing counts
					humanCount++;
					if (humanCount == 4) { humanCount++; }	// This index is reserved for the king
				}
			}
		}

		// The dices not found are definitely captured, so set the flags
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