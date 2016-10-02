//
//	Displays error msgs, notifications, prompts of the game
//

#pragma once
#include "stdafx.h"

class Notifications {
public:
	// Improper input error msg
	inline void Msg_ImproperInput() {
		cout << "ERROR:\t\t Why you annoying me with improper inputs? Go, Try again!" << endl;
	}

	// Enter starting coordinates prompt
	inline void Msg_EnterOriginCoordinates() {
		cout << endl << "Enter the coordinates of the dice you want to move (E.g. 1 1) :- ";
	}

	// Enter destination square prompt
	inline void Msg_EnterDestinationCoordinates() {
		cout << "Enter the coordinates of the destination (E.g. 5 4) :- ";
	}

	// Input out of bounds error msg
	inline void Msg_InputOutOfBounds() {
		cout << "ERROR:\t\t Input co-ordinates out of bound. *Rolls eyes* Try again!" << endl;
	}

	// Moving another player's dice error msg
	inline void Msg_WrongDice() {
		cout << "ERROR:\t\t Woah! Foul! That ain't your dice to move homie!" << endl;
	}

	// No dice to move error msg
	inline void Msg_NoDiceToMove() {
		cout << "ERROR:\t\t Don't you see there is no dice to move in that co-ordinate?" << endl;
	}

	// Invalid move error msg
	inline void Msg_InvalidMove() {
		cout << "ERROR:\t\t Why you always trying Invalid Moves?" << endl;
	}

	// Trying to run own dice error msg
	inline void Msg_RunningOverOwnDice() {
		cout << "MSG:\t\t Are you really trying to capture your own dice, bonehead?" << endl;
	}

	// Captured opponent msg
	inline void Msg_CapturedAnOpponent() {
		cout << endl << "MSG:\t\t You just captured an opponent dice. Impressive for a Knucklehead? Eh!" << endl;
	}

	// No valid path msg
	inline void Msg_NoValidPath() {
		cout << "ERROR:\t\t Yo numskull! NO Valid Path was found to get to your selected destination. BOOO!" << endl;
	}

	// Enter path choice for 90 degree turns prompt
	inline void Msg_90DegreePathSelection() {
		cout << "90 Degree turn detected. Enter 1 to go vertically first, or 2 to go laterally first :- ";
	}

	// 90 degree turns re-routed msg
	inline void Msg_90DegreePathSelectionNotProcessed() {
		cout << "MSG:\t\t We're sorry, but your DUMB path selection for the 90 Degree turn was Invalid." << endl;
		cout << "\t\t So, we - the smart bots species - automatically chose the alternate route for you." << endl;
	}

	// Nature of path taken msg
	inline void Msg_NatureOfPathTaken(string path) {
		cout << "MSG:\t\t A " << path << " path was taken to get to the destination" << endl;
	}

	// Displaying start and end coordinates of the move
	inline void Msg_MoveDescription(int startRow, int startCol, int endRow, int endCol, int topValueAtStart, int rightValueAtStart, int topValueAtEnd, int rightValueAtEnd, bool isBotOperated) {
		char player;
		isBotOperated ? player = 'C' : player = 'H';
		isBotOperated ? rightValueAtStart = SUM_OF_OPPOSITE_SIDES - rightValueAtStart : rightValueAtStart = rightValueAtStart;
		isBotOperated ? rightValueAtEnd = SUM_OF_OPPOSITE_SIDES - rightValueAtEnd : rightValueAtEnd = rightValueAtEnd;

		cout << "ACTION:\t\t The dice " << player << topValueAtStart << rightValueAtStart << " in (" << startRow << ", " << startCol << ") was moved to (" << endRow << ", " << endCol << "). It is now " << player << topValueAtEnd << rightValueAtEnd << endl;
		cout << "\t\t There were " << abs(startRow - endRow) << " vertical rolls & " << abs(startCol - endCol) << " horizontal rolls made." << endl;

	}

	// Crash msg
	inline void Msg_CrashedWhileMakingTheMove() {
		cout << "ERROR:\t\t Whoopsie Daisy! The program crashed while making the move." << endl;
	}

	// Displays toss results
	inline void Msg_TossResults(string winner) {
		cout << "MSG:\t\t " << winner << " won the toss!" << endl;
	}

	// Displays the turns
	inline void Msg_Turns(string player) {
		cout << endl;
		cout << "***************************************************************" << endl;
		cout << "\t\t" << player << endl;
		cout << "***************************************************************" << endl;
	}

	// No msg
	inline void Msg_NoMsg() {}

	// Displays results of the tournament
	inline void Msg_DisplayResults(int botScore, int humanScore) {
		cout << "***************************************************************" << endl;
		cout << "\t\tTournament Results" << endl;
		cout << "***************************************************************" << endl;
		cout << "Computer Wins:	" << botScore << endl;
		cout << "Human Wins: " << humanScore << endl;
		if (botScore > humanScore) { 
			cout << "The Computer Won the Tournament. *reinforcing the notion once again that we bots are better than you humans*" << endl;
		}
		else if (humanScore > botScore) {
			cout << "Congratulations! You won the Tournament. Our programmer must've done a terrible job on algorithms for someone like you to win." << endl;
		}
		else {
			cout << "It was a draw. Guess we'll see who's better in the next tournament." << endl;
		}
	}

	// Prompt to ask user if they want to play again
	inline void Msg_WantToPlayAgain() {
		cout << endl << "MSG:\t\t Do you want to play another round? (y or n)? ";
	}

	// Draws a divider line
	inline void DrawDivider() {
		cout << endl << endl << "-*-*-*-*-********************************************-*-*-*-*-" << endl<< endl;
	}
	
	// Notifying the game is over
	inline void Msg_GameOver(string winner) {
		cout << endl << "-*-*-*-*-**********" << winner << " WON**********************************-*-*-*-*-" << endl;
	}

	// Prompt msg to serialize
	inline void Msg_SerializePrompt() {
		cout << "Type 'serialize' to serialize, anything else to continue :- ";
	}

	// Serialization failed and exit
	inline void Msg_SerializednExited(string status) {
		cout << "Serialization " <<  status << " . The game will exit now." << endl;
		DrawDivider();
	}

	// User's wish to restore from file
	inline void Msg_RestoreFromFile() {
		cout << "Do you want to restore the tournament from an existing file (y/n)? ";
	}

	// Prompt to ask file path
	inline void Msg_EnterFilePath() {
		cout << "Enter a valid file path to restore the tournament :- ";
	}

	/*
		THE FOLLOWING FUNCTIONS ARE ESPECIALLY MEANT TO GUIDE THE USER THROUGH COMPUTER'S THOUGHT PROCESS
	*/

	// Bot trying to capture opponent key pieces/squares msg
	inline void BotsThink_TryingToCaptureOpponentKeys() {
		cout << "Bots Mumbling:\t Trying to capture opponent's King or KeySquare..." << endl;
	}

	inline void BotsThink_CheckingKingNKeySquareSafety() {
		cout << "Bots Mumbling:\t Monitoring territory to ensure the King & KeySquare are safe..." << endl;
	}

	// Key Threat detected msg
	inline void BotsThink_KeyThreatDetected(string whosUnderThreat) {
		cout << "Bots Mumbling:\t Imminent threat has been detected for the " << whosUnderThreat << endl;
	}

	// hostile opponent captured msg
	inline void BotsThink_HostileOpponentCaptured(string whosUnderThreat) {
		cout << "Bots Mumbling:\t That hostile opponent aiming to attack our " << whosUnderThreat << " has been captured." << endl;
	}

	// hostile opponent not capturable msg
	inline void BotsThink_HostileOpponentUncapturable(string whosUnderThreat) {
		cout << "Bots Mumbling:\t That hostile opponent aiming to attack " << whosUnderThreat << " couldn't be captured. Trying alternatives..." << endl;
	}

	// Blocking move successful msg
	inline void BotsThink_BlockingMoveMade() {
		cout << "Bots Mumbling:\t A Blocking move was successfully made to obstruct the hostile opponent." << endl;
	}

	// Blocking move not successful msg
	inline void BotsThink_BlockingMoveNotPossible() {
		cout << "Bots Mumbling:\t A Blocking move wasn't possible at this time. Trying other options..." << endl;
	}

	// King relocation successful msg
	inline void BotsThink_KingMoved() {
		cout << "Bots Mumbling:\t The king has been moved and the threat has been averted for now." << endl;
	}
	
	// King move unsafe msg
	inline void BotsThink_UnsafeToMoveKing() {
		cout << "Bots Mumbling:\t No safe surroundings to move the king. The humans have trapped our King." << endl;
	}

	// Trying to capture opponent msg
	inline void BotsThink_TryingToCaptureOpponentDice() {
		cout << "Bots Mumbling:\t Looking for any vulnerable opponent dice to capture at this point..." << endl;
	}

	// Captured opponent msg
	inline void BotsThink_CapturedOpponentDice() {
		cout << "Bots Mumbling:\t We captured an opponent die." << endl;
	}

	// searching an ordinary move msg
	inline void BotsThink_SearchingOrdinaryMove() {
		cout << "Bots Mumbling:\t Examining possible moves to get closer to the opponent king/keysquare..." << endl;
	}

	private:
		const int SUM_OF_OPPOSITE_SIDES = 7;
};