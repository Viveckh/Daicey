#pragma once
#include "Notifications.h"
#include "Game.h"

class Tournament {
public:
	Tournament() {
		humanScore = 0;
		botScore = 0;
		gameResult = ' ';
		quit = false;
		temp = ' ';
		nextPlayer = "";
	}


	// Playing the tournament
	void PlayTournament() {
		do {
			// Implement a fresh game
			Game game;
			gameResult = game.ImplementGame();

			// If a player has won the game
			if (gameResult == 'h') {
				humanScore++;
			}
			if (gameResult == 'b') {
				botScore++;
			}

			// 'S' refers to serialize during computer's turn & 's' refers to serialize during human's turn
			if (gameResult == 'S' || gameResult == 's') {
				
				// Store the next player in a string
				if (gameResult == 'S') {
					nextPlayer = "Computer";
				}
				else {
					nextPlayer = "Human";
				}

				// Write the serialized output to a file and exit
				if (game.getBoardView().WriteToFile(botScore, humanScore, nextPlayer)) {
					notifications.Msg_SerializednExited("SUCCESSFUL");
				}
				else {
					notifications.Msg_SerializednExited("FAILED");
				}
				return;
			}

			notifications.Msg_WantToPlayAgain();
			while (!(cin >> temp) || (temp != 'y' && temp != 'n')) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				notifications.Msg_ImproperInput();
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (temp == 'n') {
				quit = true;
			}

			notifications.DrawDivider();
		} while (!quit);

		// ATTENTION: Print out the tournament results and serialize if asked to do so
		notifications.Msg_DisplayResults(botScore, humanScore);
		return;
	}

private:
	int humanScore;
	int botScore;

	char gameResult;
	bool quit;

	char temp;
	string nextPlayer;
	Notifications notifications;
};
