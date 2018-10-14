#pragma once
/*
* Holds all the structures and headers needed
* for the AI and possibly the player handler
*/

#include <iostream>
#include <time.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <Windows.h>
#include <algorithm>

#define MAX_SIZE 4
#define INVALID 100

struct Sequence
{
	bool isBull;			//If true, hold this
	bool alreadyUsed;		//If true, move to a different spot
	int value;				//Value itself
};

struct tempStash
{
	int List[4];	//Holds temporary sequences or pushes
					//guessed sequences into a vector

	tempStash()		//Constructor
	{
		List[0] = List[1] = List[2] = List[3] = INVALID; //Used 10 to check if a position is empty
														 //10 is an invalid option, so it will be used
														 //as a place holder
	}

	bool operator==(const tempStash& stash) //operator to compare tempStash
	{
		return (List[0] == stash.List[0] && List[1] == stash.List[1] &&
			List[2] == stash.List[2] && List[3] == stash.List[3]);
	}
};

struct CattleCows
{
	bool alreadyUsed;		//See if this value has been used
	int value;				//Value itself
	bool previousPos[4];	//See what position it had before

	CattleCows()
	{
		alreadyUsed = false;
		value = INVALID;
		for (int i = 0; i < MAX_SIZE; ++i)
		{
			previousPos[i] = false; // true means it already had this position
		}
	}

	void ResetPos() //reset previousPos array
	{
		for (int i = 0; i < MAX_SIZE; ++i)
		{
			previousPos[i] = false;
		}
	}
};