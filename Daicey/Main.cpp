#include "stdafx.h"
#include "Board.h"
#include "BoardView.h"
#include "Player.h"

int main(int argc, char *argv[]) {
	Board board;
	BoardView boardView;
	boardView.DrawBoard(board);
	boardView.UpdateBoard(board);
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
	system("pause");
}