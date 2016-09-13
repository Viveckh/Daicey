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
	cout << endl;
	board.DrawBoard();
	system("pause");
}