//
//Implements the game
//

#pragma once

#include "human.h"
#include "Computer.h"
#include "BoardView.h"
#include "Board.h"

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
	}

	void ImplementGame() {
		// Draw Initial Board
		boardView.DrawBoard(board);
		boardView.UpdateBoard(board);
		
		TossToBegin();

		// Continue the loop until one of the king is captured, or user chooses to serialize and quit
		do {
			// If it is Computer's turn
			if (botTurn) {
				if (bot.Play()) {
					//Transfer Control
					botTurn = false;
					humanTurn = true;

				}
			}
			
			// If it is human's turn
			if (humanTurn) {
				GetUserInput();
				if (human.Play(startRow, startCol, endRow, endCol, board)) {
					humanTurn = false;
					botTurn = true; //Transfer Control
				}
			}

			// Re-draw the board after each move
			boardView.DrawBoard(board);
			boardView.UpdateBoard(board);
		} while (!board.humans[4].IsCaptured() && !board.bots[4].IsCaptured());

		cout << "One of the kings captured" << endl;
	}


private:

	// Gets user input if it is a human's turn
	void GetUserInput() {
		startRow = 0;
		startCol = 0;
		endRow = 0;
		endCol = 0;

		//ATTENTION: Do error handling for char inputs
		cout << "Enter the coordinates of the dice you want to move (E.g. 1 1) :- ";
		cin >> startRow >> startCol;
		cout << "Enter the coordinates of the destination (E.g. 5 4) :- ";
		cin >> endRow >> endCol;
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
			cout << "You won the Toss" << endl;
		}
		else {
			botTurn = true;
			cout << "The Computer won the Toss" << endl;
		}
	}

	// Toss Variables
	int humanDieToss;
	int botDieToss;

	// Game Board
	Board board;
	BoardView boardView;

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
};
