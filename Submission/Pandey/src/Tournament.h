//
// Tournament Class
// Runs a series of games, maintains the score for human and computer player, processes game serialization/restoration requests & declares winner.
//

/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */

#pragma once
#include "Notifications.h"
#include "Game.h"
#include "Serializer.h"

class Tournament {
public:
	// Default Constructor
	Tournament();

	// Runs a Tournament
	void PlayTournament();

	// Serializes a Tournament state
	void SerializeGame(Game &game);

private:
	// VARIABLE & OBJECT DECLARATIONS
	Serializer serializer;

	int humanScore;
	int botScore;

	char gameResult;
	bool quit;
	bool restoringGame;
	string restoreFilePath;

	char temp;
	string nextPlayer;
	Notifications notifications;

	// UTILITY FUNCTIONS
	// Gets user's choice on whether to continue to another round
	void DecisionToContinue();

};
