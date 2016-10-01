#pragma once
#include "Player.h"

class Computer : public Player {
public:

	// Default Constructor
	Computer() {}

	// Prioritizes, Calculates and makes the proper move for Computer on its turn
	bool Play(Board &board);

private:

	// CONSTANTS, VARIABLES AND OBJECT DECLARATIONS
	const int TEAMSIZE = 9;
	Notifications notifications;

	// UTILITY FUNCTIONS
	// Attempts to block the path of an opponent who is a potential threat
	bool TryBlockingAttack(Dice hostileDice, Square squareToProtect, Board &board);

	// Finds a co-ordinate to place blocking dice on the vertical route
	bool FindBlockPointVertically(Dice &hostileDice, Square &squareToProtect, Board &board);

	// Finds a co-ordinate to place blocking dice on the lateral route
	bool FindBlockPointLaterally(Dice &hostileDice, Square &squareToProtect, Board &board);

	// Tries capturing a hostile opponent who is a potential threat
	bool TryCapturingTheHostileOpponent(Dice hostileDice, Board &board);

	// Tries moving the king to a secure position
	bool TryMovingKing(Square kingSquare, Board &board);

	// Checks if a given square is at risk from opponent dices
	bool IsInDanger(Square squareAtRisk, Board board);
};