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
	// Welcome Msg
	cout << "--------------------------------------------------------------------" << endl;
	cout << "WELCOME TO DUELL - THE GAME OF DICE" << endl;
	cout << "--------------------------------------------------------------------" << endl << endl;
	cout << "Message from the BOTS: \"Hey Human! You here to get beat in Duell again?\"" << endl << endl;
	
	Tournament tournament;
	tournament.PlayTournament();
	system("pause");
}