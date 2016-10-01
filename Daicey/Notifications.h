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

	void Msg_MoveDescription(int startRow, int startCol, int endRow, int endCol) {
		cout << "ACTION: The dice in (" << startRow << ", " << startCol << ") was moved to (" << endRow << ", " << endCol << ")" << endl;
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

	void Msg_NoMsg() {}

	void Msg_DisplayResults(int botScore, int humanScore) {
		cout << "***************************************************************" << endl;
		cout << "\t\tTournament Results" << endl;
		cout << "***************************************************************" << endl;
		cout << "Computer Wins:	" << botScore << endl;
		cout << "Human Wins: " << humanScore << endl;
		if (botScore > humanScore) { 
			cout << "The Computer Won the Tournament. *reinforcing the notion once again that we bots are better than you humans*" << endl;
		}
		else if (humanScore > botScore) {
			cout << "Congratulations! You won the Tournament. Our programmer must've done an inefficient job on algorithms for someone like you to win." << endl;
		}
		else {
			cout << "It was a draw. Guess we'll see who's better in the next tournament." << endl;
		}
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

	void Msg_RestoreFromFile() {
		cout << "Do you want to restore the tournament from an existing file (y/n)? ";
	}

	void Msg_EnterFilePath() {
		cout << "Enter a valid file path to restore the tournament :- ";
	}

	/*
		THE FOLLOWING FUNCTIONS ARE ESPECIALLY MEANT TO GUIDE THE USER THROUGH COMPUTER'S THOUGHT PROCESS
	*/

	void BotsThink_TryingToCaptureOpponentKeys() {
		cout << "Bots Mumbling: Trying to capture opponent's King or KeySquare..." << endl;
	}

	void BotsThink_KeyThreatDetected(string whosUnderThreat) {
		cout << "Bots Mumbling: Imminent threat has been detected for the " << whosUnderThreat << endl;
	}

	void BotsThink_HostileOpponentCaptured(string whosUnderThreat) {
		cout << "Bots Mumbling: That hostile opponent aiming to attack our " << whosUnderThreat << " has been captured." << endl;
	}

	void BotsThink_HostileOpponentUncapturable(string whosUnderThreat) {
		cout << "Bots Mumbling: That hostile opponent aiming to attack " << whosUnderThreat << " couldn't be captured. Trying alternatives..." << endl;
	}

	void BotsThink_BlockingMoveMade() {
		cout << "Bots Mumbling: A Blocking move was successfully made to obstruct the hostile opponent." << endl;
	}

	void BotsThink_BlockingMoveNotPossible() {
		cout << "Bots Mumbling: A Blocking move wasn't possible at this time. Trying other options..." << endl;
	}

	void BotsThink_KingMoved() {
		cout << "Bots Mumbling: The king has been moved and the threat has been averted for now." << endl;
	}

	void BotsThink_UnsafeToMoveKing() {
		cout << "Bots Mumbling: No safe surroundings to move the king. The humans have trapped our King." << endl;
	}

	void BotsThink_TryingToCaptureOpponentDice() {
		cout << "Bots Mumbling: Looking for any vulnerable opponent dice to capture at this point..." << endl;
	}

	void BotsThink_CapturedOpponentDice() {
		cout << "Bots Mumbling: We captured an opponent die." << endl;
	}

	void BotsThink_SearchingOrdinaryMove() {
		cout << "Bots Mumbling: Examining possible moves to get closer to the opoonent king/keysquare..." << endl;
	}
private:

};