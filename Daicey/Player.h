//
// Player - Actions of a Game Player

#pragma once

class Player {

public:
	void WinsTheRound() {
		wins++;
	}

private:
	int score;

	// Stats for the tournament
	int wins;
};
