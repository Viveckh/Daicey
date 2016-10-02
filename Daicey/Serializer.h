//
// Class Serializer
// Contains necessary member functions to serialize or restore a tournament to and from a text file.
//

/*	************************************************************
* Name:			Vivek Pandey								*
* Project:		Duell C++									*
* Class:		CMPS 366									*
* Date:			10/4/2016									*
************************************************************ */


#pragma once
#include "stdafx.h"
#include "Board.h"

class Serializer {
public:
	//Default Constructor
	Serializer();

	// Writing serialized game state along with tournament history results to file
	bool WriteToFile(Board &board, int botWins, int humanWins, string nextPlayer);

	// Reads a serialization file and stores in a multidimensional string array for restoring purposes
	bool ReadAFile(string fileName, Board &board, int &botWins, int &humanWins, string &nextPlayer);

private:
	// VARIABLES AND OBJECTS DECLARATION
	string serializedGameBoard[8][9];
	string fileName;

	// Sets the given board based on the contents of the string array restored by reading file
	void SetBoard(Board &board);

	// Stores the game state in a multidimensional string array.
	void UpdateSerializedBoard(Board &board);
};