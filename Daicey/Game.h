//
//Implements the game
//

#pragma once

#include "human.h"
#include "BoardView.h"
#include "Board.h"

class Game {
public:
	Game() {
		humanDieToss = 0;
		botDieToss = 0;
	}

	void ImplementGame() {
		// Draw Initial Board
		boardView.DrawBoard(board);
		boardView.UpdateBoard(board);
		
		TossToBegin();

		cout << humanDieToss << " " << botDieToss << endl;
		// Whoever has the highest number on top - wins the toss
		if (humanDieToss > botDieToss) {
			cout << "You won the Toss" << endl;
		}
		else {
			cout << "The Computer won the Toss" << endl;
		}


		// Continue the loop until one of the king is captured, or user chooses to serialize and quit
		do {

		} while (!board.humans[4].IsCaptured() && !board.bots[4].IsCaptured());
	}


private:

	// Does a toss to determine which team will start the game
	void TossToBegin() {
		srand(time(NULL));
		// Continue until both have different Toss results
		do {
			humanDieToss = (rand() % 6) + 1;
			botDieToss = (rand() % 6) + 1;
		} while (humanDieToss == botDieToss);
	}

	int humanDieToss;
	int botDieToss;

	Board board;
	BoardView boardView;
};
