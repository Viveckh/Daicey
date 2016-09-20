#pragma once
#include "stdafx.h"

class Notifications {
public:
	void Msg_InvalidMove() {
		cout << endl << "ERROR: Invalid Move!" << endl << endl;
	}

	void Msg_RunningOverOwnDice() {
		cout << endl << "MSG: Are you really trying to capture your own dice, bud?" << endl << endl;
	}

	void Msg_CapturedAnOpponent() {
		cout << endl << "MSG: You just captured an opponent dice. Great Job!" << endl << endl;
	}

	void Msg_NoValidPath() {
		cout << endl << "ERROR: No Valid Path was found to get to your selected destination." << endl << endl;
	}

	void Msg_90DegreePathSelectionNotProcessed() {
		cout << endl << "MSG: We're sorry, but your path selection for the 90 Degree turn was Invalid. So, we automatically chose the alternate route for you." << endl << endl;
	}

	void Msg_NatureOfPathTaken(string path) {
		cout << endl << "MSG: A " << path << " was taken to get to the destination" << endl << endl;
	}

	void Msg_CrashedWhileMakingTheMove() {
		cout << endl << "ERROR: The program crashed while making the move." << endl << endl;
	}
private:

};