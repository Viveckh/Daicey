#pragma once
#include "Player.h"

class Computer : public Player {
public:
	Computer() {
		score = 0;
	}

	bool Play() {
		return true;
		// Calculate all the possibilities and make a move
	}

	// Increments the score
	void WinsTheRound() {
		score++;
	}

	int getScore() {
		return score;
	}

private:
	int score;
};