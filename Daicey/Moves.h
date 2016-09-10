//
// Moves - Various valid moves in the game
//

#pragma once
#include "Dice.h"

class Moves {
public:
	// ATTENTION: Don't forget to increment/decrement the rows and columns after the moves
	void RollForward(Dice &dice) {
		tempStorage1 = dice.getFront;
		tempStorage2 = dice.getRear;
		
		dice.SetFront = dice.getTop;
		dice.SetRear = dice.getBottom;
		dice.SetBottom = tempStorage1;
		dice.SetTop = tempStorage2;
	}

	void RollBackward(Dice &dice) {
		tempStorage1 = dice.getFront;
		tempStorage2 = dice.getRear;

		dice.SetRear = dice.getTop;
		dice.SetFront = dice.getBottom;
		dice.SetTop = tempStorage1;
		dice.SetBottom = tempStorage2;
	}

	void RollLeft(Dice &dice) {
		tempStorage1 = dice.getLeft;
		tempStorage2 = dice.getRight;

		dice.SetLeft = dice.getTop;
		dice.SetRight = dice.getBottom;
		dice.SetBottom = tempStorage1;
		dice.SetTop = tempStorage2;
	}

	void RollRight(Dice &dice) {
		tempStorage1 = dice.getLeft;
		tempStorage2 = dice.getRight;
		
		dice.SetRight = dice.getTop;
		dice.SetLeft = dice.getBottom;
		dice.SetTop = tempStorage1;
		dice.SetBottom = tempStorage2;
	}
private:
	int tempStorage1;
	int tempStorage2;
};