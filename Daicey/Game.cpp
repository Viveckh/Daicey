/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#include "Game.h"

// Default Constructor
Game::Game() {
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

/* *********************************************************************
Function Name: ImplementGame

Purpose: Runs a full game until someone wins or user requests serialization

Parameters:
restoringGame, boolean value stating whether a restore of previous game was requested by user
nextPlayer, a string that contains who's turn is next (if restoring)

Return Value: 'b' if bot wins, 'h' if human wins, 'S' if serialization requested during bot turn, 's' if serialization requested during human turn

Local Variables: none

Assistance Received: none
********************************************************************* */
// Implements a Round. Return value is 'h' for human winner, 'b' for bot winner, and 's' for Serialization
char Game::ImplementGame(bool restoringGame, string nextPlayer) {
	// Set the turns if restoring a game from saved state
	if (restoringGame) {
		if (nextPlayer == "Computer") {
			botTurn = true;
		}
		if (nextPlayer == "Human") {
			humanTurn = true;
		}
	}

	// Draw Initial Board
	boardView.DrawBoard(board);

	// Conduct a toss if the controls haven't been assigned wile restoring
	if (!humanTurn && !botTurn) {
		TossToBegin();
	}

	// Continue the loop until one of the king is captured, one of the key squares gets occupied or user chooses to serialize and quit
	do {
		// If it is Computer's turn
		if (botTurn) {
			notifications.Msg_Turns("COMPUTER'S TURN");
			if (bot.Play(board)) {
				//Transfer Control
				botTurn = false;
				humanTurn = true;
				notifications.Msg_Turns("BOARD AFTER COMPUTER'S MOVE");
				goto ReloadGameBoard;	//Using Goto to prevent human's loop from running
			}
			else {
				continue;
			}
		}

		// If it is human's turn
		if (humanTurn) {
			notifications.Msg_Turns("YOUR TURN");
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
			if (botTurn) { return 'S'; }
			if (humanTurn) { return 's'; }
		}
	} while (1);
}

/* *********************************************************************
Function Name: UserWantsToSerialize

Purpose: Ask human player if they want to serialize

Parameters: none

Return Value: true if user requests serialization, false otherwise

Local Variables: none

Assistance Received: none
********************************************************************* */
// Asks if user wants to serialize & returns true if user wants to serialize
bool Game::UserWantsToSerialize() {
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

/* *********************************************************************
Function Name: GameOverConditionMet

Purpose: To check if the condition for game over has been met

Parameters: none

Return Value: true if condition met for game to be over, false otherwise

Local Variables: none

Assistance Received: none
********************************************************************* */
// Checks if the condition to end the game has been met
bool Game::GameOverConditionMet() {
	//If one of the kings captured
	if (board.humans[4].IsCaptured() || board.bots[4].IsCaptured()) {
		return true;
	}

	//If the human key square is occupied by the bots King die 
	if (board.IsSquareOccupied(0, 4)) {
		if (board.GetSquareResident(0, 4)->IsBotOperated()) {
			if (board.GetSquareResident(0, 4)->IsKing()) {
				return true;
			}
		}
	}

	//If the computer key square is occupied by the human King die
	if (board.IsSquareOccupied(7, 4)) {
		if (!board.GetSquareResident(7, 4)->IsBotOperated()) {
			if (board.GetSquareResident(7, 4)->IsKing()) {
				return true;
			}
		}
	}

	//If none of the game over conditions are met
	return false;
}

/* *********************************************************************
Function Name: GetUserInput

Purpose: To get user input for coordinates

Parameters: none

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Gets user input for coordinates if it is a human's turn
void Game::GetUserInput() {
	startRow = 0;
	startCol = 0;
	endRow = 0;
	endCol = 0;
	path = 0;

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

/* *********************************************************************
Function Name: TossToBegin

Purpose: To conduct a toss and set the turn of appropriate player to true

Parameters: none

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Does a toss to determine which team will start the game
void Game::TossToBegin() {
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