//
//Implements the game
//

#pragma once

#include "human.h"
#include "Computer.h"
#include "BoardView.h"
#include "Board.h"
#include "Notifications.h"

class Game {
public:
	Game() {
		humanDieToss = 0;
		botDieToss = 0;
		humanTurn = false;
		botTurn = false;

		startRow = 0;
		startCol = 0;
		endRow = 0;
		endCol = 0;
		path = 0;
	}


	// Made this function return a value in order to stop the tournament
	// Ret value is 'h' for human winner, 'b' for bot winner, and 's' for Serialization
	char ImplementGame() {
		// Draw Initial Board
		boardView.DrawBoard(board);
		
		TossToBegin();

		// Continue the loop until one of the king is captured, one of the key squares gets occupied or user chooses to serialize and quit
		do {
			// If it is Computer's turn
			if (botTurn) {
				if (bot.Play(board)) {
					//Transfer Control
					botTurn = false;
					humanTurn = true;
					notifications.Msg_Turns("BOARD AFTER COMPUTER'S MOVE");
					goto ReloadGameBoard;	//Using Goto to prevent human's loop from running
				}
				else {
					notifications.Msg_InvalidMove();
					continue;
				}
			}
			
			// If it is human's turn
			if (humanTurn) {

				GetUserInput();
				if (human.Play(startRow, startCol, endRow, endCol, board, path)) {
					humanTurn = false;
					botTurn = true; //Transfer Control
					notifications.Msg_Turns("BOARD AFTER HUMAN'S MOVE");
				}
				else {
					notifications.Msg_InvalidMove();
					continue;
				}
			}

			ReloadGameBoard:
			// Re-draw the board after each move
			boardView.DrawBoard(board);

			// If game over condition met
			if (GameOverConditionMet()) {
				// Whoever just received the control is the one who lost
				if (humanTurn) {
					notifications.Msg_GameOver("COMPUTER");
					return 'b';	// Bot winner
				}
				else {
					notifications.Msg_GameOver("HUMAN");
					return 'h';	// Human winner
				}
			}

			// Stop the game and Return if user wants to serialize
			// return 'S' if serializing during computer's turn, 's' if serializing during human's turn
			if (UserWantsToSerialize()) {
				if (botTurn) { return 'S';  }
				if (humanTurn) { return 's'; }
			}
 		} while (1);
	}

	Board getGameBoard() {
		return board;
	}

private:
	// Returns true if user wants to serialize
	bool UserWantsToSerialize() {
		notifications.Msg_SerializePrompt();
		//cin >> wishToSerialize;
		while (!(cin >> wishToSerialize)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			notifications.Msg_ImproperInput();
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (wishToSerialize == "serialize") {
			return true;
		}
		return false;
	}


	bool GameOverConditionMet() {
		//If one of the kings captured
		if (board.humans[4].IsCaptured() || board.bots[4].IsCaptured()) {
			return true;
		}

		//If the human key square is occupied by a bot die
		if (board.IsSquareOccupied(0, 4)) {
			if (board.GetSquareResident(0, 4)->IsBotOperated()) {
				return true;
			}
		}

		//If the computer key square is occupied by a human die
		if (board.IsSquareOccupied(7, 4)) {
			if (!board.GetSquareResident(7, 4)->IsBotOperated()) {
				return true;
			}
		}

		//If none of the game over conditions are met
		return false;
	}

	// Gets user input if it is a human's turn
	void GetUserInput() {
		startRow = 0;
		startCol = 0;
		endRow = 0;
		endCol = 0;
		path = 0;

		//ATTENTION: Do error handling for char inputs
		// ATTENTION: Put an "Enter -1 to serialize and quit anytime inside both these loop"
		notifications.Msg_EnterOriginCoordinates();
		while (!(cin >> startRow >> startCol)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			notifications.Msg_ImproperInput();
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		notifications.Msg_EnterDestinationCoordinates();
		while (!(cin >> endRow >> endCol)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			notifications.Msg_ImproperInput();
		}
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// If a 90 degree turn involved, ask user for the path choice
		if ((startRow != endRow) && (startCol != endCol)) {
			notifications.Msg_90DegreePathSelection();
			while (!(cin >> path)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				notifications.Msg_ImproperInput();
			}
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// Does a toss to determine which team will start the game
	void TossToBegin() {
		srand(time(NULL));
		// Continue until both have different Toss results
		do {
			humanDieToss = (rand() % 6) + 1;
			botDieToss = (rand() % 6) + 1;
		} while (humanDieToss == botDieToss);

		// Whoever has the highest number on top - wins the toss
		if (humanDieToss > botDieToss) {
			humanTurn = true;
			notifications.Msg_TossResults("You");
		}
		else {
			botTurn = true;
			notifications.Msg_TossResults("Computer");
		}
	}

	// Toss Variables
	int humanDieToss;
	int botDieToss;

	// Game Board
	Board board;
	BoardView boardView;
	Notifications notifications;

	// Players
	Human human;
	Computer bot;

	// Control Variables
	bool humanTurn;
	bool botTurn;

	// Variables to store user input of coordinates
	int startRow;
	int startCol;
	int endRow;
	int endCol;
	int path;		//1 for vertical first, 2 for lateral first
	string wishToSerialize;
};
