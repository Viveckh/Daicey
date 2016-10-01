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
	// Default Constructor
	Game();

	// ACCESSOR
	// Returns the board as a reference. Be careful while using it
	Board& getGameBoard() {
		return board;
	}

	// OTHER FUNCTIONS
	// Implements a Round. Return value is 'h' for human winner, 'b' for bot winner, and 's' for Serialization
	char ImplementGame(bool restoringGame, string nextPlayer = "");

private:
	// VARIABLES & OBJECTS DECLARATION

	// Toss Variables
	int humanDieToss;
	int botDieToss;

	// Game Board, Display & Notification objects
	Board board;
	BoardView boardView;
	Notifications notifications;

	// Player objects
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

	// UTILITY FUNCTIONS

	// Asks if user wants to serialize & returns true if user wants to serialize
	bool UserWantsToSerialize();

	// Checks if the condition to end the game has been met
	bool GameOverConditionMet();

	// Gets user input for coordinates if it is a human's turn
	void GetUserInput();

	// Does a toss to determine which team will start the game
	void TossToBegin();
};
