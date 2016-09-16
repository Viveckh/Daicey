#include "stdafx.h"
#include "Board.h"
#include "Moves.h"

int main(int argc, char *argv[]) {
	Board board;
	board.DrawBoard();
	board.UpdateBoard();
	Moves humanMoves;
	humanMoves.RollForward(board.humans[0], board);
	humanMoves.RollForward(board.humans[0], board);
	humanMoves.RollForward(board.humans[0], board);
	humanMoves.RollForward(board.humans[0], board);
	humanMoves.RollForward(board.humans[0], board);
	humanMoves.RollForward(board.humans[0], board);
	humanMoves.RollForward(board.humans[0], board);
	humanMoves.RollForward(board.humans[0], board);
	humanMoves.RollForward(board.humans[0], board);
	board.DrawBoard();

	Moves computerMoves;
	computerMoves.RollBackward(board.bots[4], board);
	board.DrawBoard();
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
	system("pause");
}