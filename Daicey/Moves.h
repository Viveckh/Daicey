//
// Moves - Various valid moves in the game
//

#pragma once
#include "Board.h"
#include "Dice.h"

class Moves {
public:
	// ATTENTION: Don't forget to increment/decrement the rows and columns after the moves
	// ALSO, don't forget to update the newly occupied coordinate and release the currently occupied square.
	void RollForward(Dice &dice, Board &board) {
		tempStorage1 = dice.getFront;
		tempStorage2 = dice.getRear;
		
		dice.SetFront(dice.getTop);
		dice.SetRear(dice.getBottom);
		dice.SetBottom(tempStorage1);
		dice.SetTop(tempStorage2);
		dice.SetRow(1, true);
		//board[dice.getRow()][dice.getColumn()].SetOccupied(true);
	}

	void RollBackward(Dice &dice) {
		tempStorage1 = dice.getFront;
		tempStorage2 = dice.getRear;

		dice.SetRear(dice.getTop);
		dice.SetFront(dice.getBottom);
		dice.SetTop(tempStorage1);
		dice.SetBottom(tempStorage2);
		dice.SetRow(1, false);
	}

	void RollLeft(Dice &dice) {
		tempStorage1 = dice.getLeft;
		tempStorage2 = dice.getRight;

		dice.SetLeft(dice.getTop);
		dice.SetRight(dice.getBottom);
		dice.SetBottom(tempStorage1);
		dice.SetTop(tempStorage2);
		dice.SetColumn(1, false);
	}

	void RollRight(Dice &dice) {
		tempStorage1 = dice.getLeft;
		tempStorage2 = dice.getRight;
		
		dice.SetRight(dice.getTop);
		dice.SetLeft(dice.getBottom);
		dice.SetTop(tempStorage1);
		dice.SetBottom(tempStorage2);
		dice.SetColumn(1, true);
	}

private:
	int tempStorage1;
	int tempStorage2;
};