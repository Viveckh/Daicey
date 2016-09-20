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

			// ATTENTION: You can implement Serialization in a similar if condition
			if (gameResult == 's') {
				// Serialize the game
				break;	// Break the loop to stop the game
			}

			notifications.Msg_WantToPlayAgain();
			while (!(cin >> temp) || (temp != 'y' && temp != 'n')) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				notifications.Msg_ImproperInput();
			}
			if (temp == 'n') {
				quit = true;
			}

			notifications.DrawDivider();
		} while (gameResult != 's' && !quit);

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
	Notifications notifications;
};
