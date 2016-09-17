#pragma once
#include "Player.h"

class Human: public Player {
public:
	void Play(int startRow, int startCol, int endRow, int endCol, Board &board) {
		// Verify the dice is not bot operated so that the dice belongs to human player
		if (board.GetSquareResident(startRow, startCol) != NULL) {
			if (!board.GetSquareResident(startRow, startCol)->IsBotOperated()) {
				MakeAMove(startRow, startCol, endRow, endCol, board);
			}
		}
	}
private:

};