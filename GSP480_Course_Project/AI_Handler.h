#pragma once
/*
* AI Handler for Bulls and Cows
* GSP480
* Miranda, Celeste
*/
#include "AI_Util.h"
#include"Player.h"
class AI_Handler
{
private:
	/******************************* VARIABLES *****************************************/
		
	bool AI_Win;							// Determines whether the AI won or not
	std::vector<tempStash> alreadyGuessed;	//Holds all the guessed values
	bool firstGuess;						//AI's first guess
								//Holds how many cows are in the list
	CattleCows Cows[4];						//Holds the numbers that are called as cow
	int CowCol;

	/******************************* FUNCTIONS *****************************************/
	void GuessSequence(PlayerHandler& Player);				//Return a guessed sequence
	void CheckDuplicate(tempStash&);	//Removes and replaces all duplicates
	void DeterminePlayerInput(char*);	//Determine information based on player's input
	bool SearchGuessed(tempStash);		//Search alreadyGuessed to find repeats
										//Return true if it finds a copy, else returns fasle
	void SequenceGenerator(tempStash&); //Come up with a random sequence 
	bool canBePlaced(CattleCows*, int); //Can this number be placed
	void ResetCows(); // Restart its usage and value
	int ReturnCow(int); //Return a cow
	void RemoveCow(CattleCows*, int, int); //Remove Cow after it's bull
	void TakeInBull(int);  //Take into account it's bulls and cannot use those positions
	void ResetPlayerPos(); //Reset alreadyUsed bool in PlayerSequence


public:
	int bullCount = 0;
	int PlayerBullCount = 0;
	bool hasWon = false;
	
	CattleCows KnownAICows[4];
	int NumKnownCowsAI;

	Sequence GuessPlayerSequence[4];			//The AI's guess on the player's sequence
	//std::vector<int> playerGuessedCows;         //list of players cows to be displayed
	bool firstTurn;								//Set true once the AI has taken its first turn
	Sequence AISequence[4];                     //The AI's own sequence
	Sequence AIDisplaySequence[4];				//displays bulls and keeps bullCount

	AI_Handler();								//Constructor
	~AI_Handler();								//Destructor

	bool WhoWon(char &winner);			//Returns if the AI_Won or not  
	void AI_Turn(PlayerHandler& Player);				//Handles what to do when it is the AI's turn
	void AI_Answer(tempStash);	//Responds to player with Bulls, Cows and Neither
								//Use this during player's turn
	//void handleCows(int &j, std::vector<int> &cows);

};