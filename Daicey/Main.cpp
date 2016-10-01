//
//	Entry point for the game
//

#pragma once

#include "Tournament.h"

int main(int argc, char *argv[]) {
	Tournament tournament;
	tournament.PlayTournament();
	system("pause");
}