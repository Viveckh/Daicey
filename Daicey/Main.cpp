/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

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