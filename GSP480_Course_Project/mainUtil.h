#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include"AI_Handler.h"
#include"Player.h"

class mainUtil
{
public:


	int ROUND = 1;
	int MAX_ROUND = 6;
	int whoseTurn = 0;  //controls whose turn in an if statement
	//all pretty self explanatory
	void printPlayerSequence(PlayerHandler &player);  //for test purposes
	void printAIDisplaySequence(AI_Handler AI);
	void printAISequence(AI_Handler AI);
	void printCows(CattleCows *cows, int size);
	void drawScreen(tempStash &input, AI_Handler &AI, PlayerHandler &player);
	/*void checkWin(PlayerHandler &player, AI_Handler & AI);*/
	void handleInput(tempStash &input);
	void RunGame();
};