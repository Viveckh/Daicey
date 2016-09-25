#include "stdafx.h"
#include "Board.h"
#include "BoardView.h"
#include "Player.h"
#include "Human.h"
#include "Game.h"
#include "Tournament.h"
#include "Serializer.h"

int main(int argc, char *argv[]) {
	//Tournament tournament;
	//tournament.PlayTournament();
	Board board;
	int humanWins = 0;
	int botWins = 0;
	string fileName = "C:\\Duell_LastGameSerialization.txt";
	string nextPlayer = "";


	Serializer serialize;
	serialize.ReadAFile(fileName, board, botWins, humanWins, nextPlayer);

	cout << botWins << endl;
	cout << humanWins << endl;
	cout << nextPlayer << endl << endl;

	BoardView boardview;
	boardview.DrawBoard(board);
	/*
	Board board;
	BoardView boardView;
	boardView.DrawBoard(board);
	boardView.UpdateBoard(board);


	// ATTENTION: These test cases are producing errors in different parts of path validation and moves
	Human hx;
	hx.Play(0, 0, 5, 0, board);	// vertical human move
	boardView.DrawBoard(board);	
	hx.Play(7, 2, 2, 0, board);	// Trying to move opponent's piece
	boardView.DrawBoard(board);
	hx.Play(5, 0, 5, 3, board);	// lateral move
	boardView.DrawBoard(board);
	hx.Play(0, 3, 6, 3, board);	// trying to hope past a taken spot
	boardView.DrawBoard(board);
	hx.Play(0, 3, 5, 2, board);	// trying to hope past a taken spot and do a 90 degree turn
	boardView.DrawBoard(board);
	hx.Play(0, 3, 3, 6, board);	//trying to do a 90 degree
	boardView.DrawBoard(board);
	hx.Play(5, 3, 3, 7, board);	//trying to do a 90 degree but only one path (2nd one) is valid
	boardView.DrawBoard(board);
	hx.Play(3, 7, 3, 6, board);	//capturing a piece
	boardView.DrawBoard(board);
	boardView.ViewCapturedDice(board);
	*/


	/*
	Player humanMoves;
	humanMoves.RollUp(board.humans[0], board);
	humanMoves.RollUp(board.humans[0], board);
	humanMoves.RollUp(board.humans[0], board);
	humanMoves.RollUp(board.humans[0], board);
	humanMoves.RollUp(board.humans[0], board);
	humanMoves.RollUp(board.humans[0], board);
	humanMoves.RollUp(board.humans[0], board);
	humanMoves.RollUp(board.humans[0], board);
	humanMoves.RollUp(board.humans[0], board);
	boardView.DrawBoard(board);

	Player computerMoves;
	computerMoves.RollDown(board.bots[4], board);
	boardView.DrawBoard(board);
	cout << endl;

	if (humanMoves.IsValidDestination(board.humans[0], board.GetSquareAtLocation(4, 1))) {
		cout << "1valid";
	}
	
	if (humanMoves.IsValidDestination(board.humans[0], board.GetSquareAtLocation(7, 1))) {
		cout << "2valid";
	}
	if (humanMoves.IsValidDestination(board.humans[0], board.GetSquareAtLocation(5, 1))) {
		cout << "3valid";
	}
	if (humanMoves.IsValidDestination(board.humans[0], board.GetSquareAtLocation(6, 2))) {
		cout << "4valid";
	}
	*/
	system("pause");

}