#pragma once
#include "stdafx.h"

class Notifications {
public:
	void Msg_ImproperInput() {
		cout << "ERROR: Why you annoying me with improper inputs? Go, Try again!" << endl;
	}

	void Msg_EnterOriginCoordinates() {
		cout << endl << "Enter the coordinates of the dice you want to move (E.g. 1 1) :- ";
	}

	void Msg_EnterDestinationCoordinates() {
		cout << "Enter the coordinates of the destination (E.g. 5 4) :- ";
	}

	void Msg_InputOutOfBounds() {
		cout << "ERROR: Input co-ordinates out of bound. *Rolls eyes* Try again!" << endl;
	}

	void Msg_WrongDice() {
		cout << "ERROR: Woah! Foul! That ain't your dice to move homie!" << endl;
	}

	void Msg_NoDiceToMove() {
		cout << "ERROR: Don't you see there is no dice to move in that co-ordinate?" << endl;
	}

	void Msg_InvalidMove() {
		cout << "ERROR: Why you always trying Invalid Moves?" << endl;
	}

	void Msg_RunningOverOwnDice() {
		cout << "MSG: Are you really trying to capture your own dice, bonehead?" << endl;
	}

	void Msg_CapturedAnOpponent() {
		cout << endl << "MSG: You just captured an opponent dice. Impressive for a Knucklehead? Eh!" << endl;
	}

	void Msg_NoValidPath() {
		cout << "ERROR: Yo numskull! NO Valid Path was found to get to your selected destination. BOOO!" << endl;
	}

	void Msg_90DegreePathSelection() {
		cout << "90 Degree turn detected. Enter 1 to go vertically first, or 2 to go laterally first :- ";
	}

	void Msg_90DegreePathSelectionNotProcessed() {
		cout << "MSG: We're sorry, but your DUMB path selection for the 90 Degree turn was Invalid." << endl;
		cout << "So, we - the smart bots species - automatically chose the alternate route for you." << endl;
	}

	void Msg_NatureOfPathTaken(string path) {
		cout << "MSG: A " << path << " path was taken to get to the destination" << endl;
	}

	void Msg_CrashedWhileMakingTheMove() {
		cout << "ERROR: Whoopsie Daisy! The program crashed while making the move." << endl;
	}

	void Msg_TossResults(string winner) {
		cout << "MSG: " << winner << " won the toss!" << endl;
	}

	void Msg_Turns(string player) {
		cout << endl;
		cout << "***************************************************************" << endl;
		cout << "\t\t" << player << endl;
		cout << "***************************************************************" << endl;
	}

	void Msg_DisplayResults(int botScore, int humanScore) {
		cout << "***************************************************************" << endl;
		cout << "\t\tTournament Results" << endl;
		cout << "***************************************************************" << endl;
		cout << "Computer Wins:	" << botScore << endl;
		cout << "Human Wins: " << humanScore << endl;
	}

	void Msg_WantToPlayAgain() {
		cout << endl << "MSG: Do you want to play another round? (y or n)? ";
	}

	void DrawDivider() {
		cout << endl << endl << "-*-*-*-*-********************************************-*-*-*-*-" << endl<< endl;
	}

	void Msg_GameOver(string winner) {
		cout << endl << "-*-*-*-*-**********" << winner << " WON**********************************-*-*-*-*-" << endl;
	}

	void Msg_SerializePrompt() {
		cout << "Type 'serialize' to serialize, anything else to continue :- ";
	}

	void Msg_SerializednExited(string status) {
		cout << "Serialization " <<  status << " . The game will exit now." << endl;
		DrawDivider();
	}

private:

};