/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#include "Tournament.h"

// Default Constructor
Tournament::Tournament() {
	humanScore = 0;
	botScore = 0;
	gameResult = ' ';
	quit = false;
	restoringGame = false;
	temp = ' ';
	nextPlayer = "";
}

/* *********************************************************************
Function Name: PlayTournament

Purpose: Runs a series of games and maintains score until user serializes or quits

Parameters: none

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Runs a Tournament
void Tournament::PlayTournament() {
	// Ask user if they want to restore the tournament from existing file
	notifications.Msg_RestoreFromFile();
	DecisionToContinue();

	if (temp == 'y') {
		restoringGame = true;
		notifications.Msg_EnterFilePath();
		cin >> restoreFilePath;
	}

	do {
		// Implement a fresh game
		Game game;

		// ATTENTION: Modify the board and other tournament, game objects from serialization file here if one is provided
		if (restoringGame) {
			// Exit the game if restore failed
			if (!serializer.ReadAFile(restoreFilePath, game.getGameBoard(), botScore, humanScore, nextPlayer)) {
				notifications.Msg_SerializednExited("FAILED");
				return;
			}
			gameResult = game.ImplementGame(restoringGame, nextPlayer);
			restoringGame = false;
		}
		else {
			gameResult = game.ImplementGame(restoringGame);
		}

		// If a player has won the game
		if (gameResult == 'h') {
			humanScore++;
		}
		if (gameResult == 'b') {
			botScore++;
		}

		// 'S' refers to serialize during computer's turn & 's' refers to serialize during human's turn
		if (gameResult == 'S' || gameResult == 's') {
			SerializeGame(game);
			return;
		}

		notifications.Msg_WantToPlayAgain();
		DecisionToContinue();

		if (temp == 'n') {
			quit = true;
		}

		notifications.DrawDivider();
	} while (!quit);

	// ATTENTION: Print out the tournament results and serialize if asked to do so
	notifications.Msg_DisplayResults(botScore, humanScore);
	return;
}

/* *********************************************************************
Function Name: SerializeGame

Purpose: Processes the serialization request from the human player

Parameters: game, the current game object

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Serializes a Tournament state
void Tournament::SerializeGame(Game &game) {
	// Store the next player in a string
	if (gameResult == 'S') {
		nextPlayer = "Computer";
	}
	else {
		nextPlayer = "Human";
	}

	// Write the serialized output to a file and exit
	if (serializer.WriteToFile(game.getGameBoard(), botScore, humanScore, nextPlayer)) {
		notifications.Msg_SerializednExited("SUCCESSFUL");
	}
	else {
		notifications.Msg_SerializednExited("FAILED");
	}
}

/* *********************************************************************
Function Name: DecisionToContinue

Purpose: To Ask user if they want to continue the tournament after a game is voer

Parameters: none

Return Value: none

Local Variables: none

Assistance Received: none
********************************************************************* */
// Gets user's choice on whether to continue to another round
void Tournament::DecisionToContinue() {
	temp = ' ';
	while (!(cin >> temp) || (temp != 'y' && temp != 'n')) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		notifications.Msg_ImproperInput();
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

