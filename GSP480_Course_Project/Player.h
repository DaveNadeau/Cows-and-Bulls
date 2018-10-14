#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include"AI_Util.h"
/*
* Player Handler
* GSP480
* Macalanda, Jordan
*/

class PlayerHandler
{
public:
	int bullCount = 0;
	bool hasWon = false;
	char check[4];
	char lowercheck[4];
	int PlayerSequence[4];
	int AISequence[4];
	void AIGuess(PlayerHandler& Player, tempStash& input);
	void PlayerSecret(PlayerHandler& Player, tempStash& guess);
	void PlayerInputCheck(tempStash& input);
	void PlayerConfirmCheck(char& input0, char& input1, char& input2, char& input3, PlayerHandler& Player);

};