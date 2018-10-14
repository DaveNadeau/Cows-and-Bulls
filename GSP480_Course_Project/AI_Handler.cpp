#include "AI_Handler.h"

AI_Handler::AI_Handler()
{
	CowCol = 0;
	firstGuess = true;
	alreadyGuessed.clear();
	ResetCows();
	NumKnownCowsAI = 0;

	tempStash Guess, GuessP;

	for (int i = 0; i < 4; ++i) //Generate original, random guess
	{
		AISequence[i].isBull = false;
		AISequence[i].alreadyUsed = false;

		Guess.List[i] = rand() % 10;

		GuessPlayerSequence[i].isBull = false;
		GuessPlayerSequence[i].alreadyUsed = false;
		
		GuessP.List[i] = rand() % 10;
	}

	CheckDuplicate(Guess); //Determine if there are any duplicates
	CheckDuplicate(GuessP);

	for (int i = 0; i < MAX_SIZE; ++i)
	{
		AISequence[i].value = Guess.List[i]; // Set it equal to the AISequence
		GuessPlayerSequence[i].value = GuessP.List[i];
	}
}

AI_Handler::~AI_Handler()
{

}


void AI_Handler::GuessSequence(PlayerHandler& Player)
{
	tempStash Guess;
	bool searching = true;

	for (int i = 0; i < MAX_SIZE; ++i)
	{
		Guess.List[i] = GuessPlayerSequence[i].value;
	}

	while (searching)
	{
		if (!firstGuess)
		{
			SequenceGenerator(Guess); //Come up with a random sequence
		}
		
		CheckDuplicate(Guess);  //Check for duplicates

		if (!SearchGuessed(Guess)) //If there are no duplicates
		{
			ResetCows();
			ResetPlayerPos();
			searching = false;
		}
	}

	for (int i = 0; i < MAX_SIZE; ++i) //Store in Player Sequence to update it
	{
		GuessPlayerSequence[i].value = Guess.List[i];
	}

	std::cout << "Coumputer: Thinking...\n";
	Sleep(500);
	std::cout << "Computer: I guess " << Guess.List[0] << " " << Guess.List[1] 
			  << " " << Guess.List[2] << " " << Guess.List[3] << "\n";

	
	Player.AIGuess(Player, Guess);
}

void AI_Handler::SequenceGenerator(tempStash& Guess)
{
	int temp;
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		if (GuessPlayerSequence[i].isBull) //Check if Bull
		{
			Guess.List[i] = GuessPlayerSequence[i].value;
			GuessPlayerSequence[i].alreadyUsed = true;
			continue;
		}

		int Guesstemp = Guess.List[i]; //temporarily hold

		temp = ReturnCow(i); //Get a good cow
		if (temp != INVALID)
		{
			Guess.List[i] = Cows[temp].value; //set it to this cow value
			Cows[temp].alreadyUsed = true; //this cow has been used
			Cows[temp].previousPos[i] = true; //this cow cannot use this space again
			GuessPlayerSequence[i].alreadyUsed = true; //a spot has been taken
			continue;
		}

		if (Guesstemp == Guess.List[i] && !GuessPlayerSequence[i].alreadyUsed)
		{
			Guess.List[i] = rand() % 10;
			continue;
		}
	}
}

bool AI_Handler::SearchGuessed(tempStash Guess)
{
	int i;
	int guessedSize = alreadyGuessed.size();
	if (guessedSize == 0) //if the vector is empty
	{
		alreadyGuessed.push_back(Guess); //push back Guess
		return false;
	}
	else
	{
		for (i = 0; i < guessedSize; ++i) //search through vector
		{
			if (alreadyGuessed[i] == Guess) //if there is a copy of a sequence
			{
				return true; 
			}
		}
	}

	alreadyGuessed.push_back(Guess); //push back Guess since it is not inside the vector
	return false; //else return as false
}

void AI_Handler::CheckDuplicate(tempStash &Guess)
{
	//base case
	if (Guess.List[0] != Guess.List[1] && Guess.List[0] != Guess.List[2] &&
		Guess.List[0] != Guess.List[3] && Guess.List[1] != Guess.List[2] &&
		Guess.List[1] != Guess.List[3] && Guess.List[2] != Guess.List[3])
	{
		return; //stop recursing once there are no repeats
	}

	//find and replace duplicates
	else
	{
		int i = 0, j = 1;
		bool checking = true;

		while (checking)
		{
			if (Guess.List[i] == Guess.List[j])
			{
				if (!firstGuess)
				{
					if (GuessPlayerSequence[i].alreadyUsed)
					{
						Guess.List[j] = rand() % 10;
					}
					else if (GuessPlayerSequence[j].alreadyUsed)
					{
						Guess.List[i] = rand() % 10;
					}
					else
					{
						Guess.List[j] = rand() % 10;
					}
				}
				else
				{
					Guess.List[j] = rand() % 10;
				}
			}

			j++;
			if (j == MAX_SIZE)
			{
				j = 1;
				i++;
			}
			if (i == 3)
			{
				checking = false;
			}
		}
		CheckDuplicate(Guess); //Recursive

	}
}

void AI_Handler::DeterminePlayerInput(char *input)
{
	for (int i = 0; i < 4; ++i)
	{
		switch (input[i])
		{
			case 'B':
			case 'b':
				GuessPlayerSequence[i].isBull = true;
				RemoveCow(Cows, GuessPlayerSequence[i].value, CowCol);
				TakeInBull(i);
				break;
			case 'C':
			case 'c':
				if (CowCol != MAX_SIZE && canBePlaced(Cows, GuessPlayerSequence[i].value))
				{
					Cows[CowCol].value = GuessPlayerSequence[i].value;
					Cows[CowCol].previousPos[i] = true;
					++CowCol;
				}
				break;
			case 'N':
			case 'n':
			default:
				break;
		}
	}
}

bool AI_Handler::WhoWon(char &winner)
{
	bullCount = 0;
	PlayerBullCount = 0;

	for (int i = 0; i < 4; ++i)
	{
		if (GuessPlayerSequence[i].isBull)
		{
			++bullCount; //count number of bulls (isBull == true)
		}
		if (AIDisplaySequence[i].isBull)
		{
			++PlayerBullCount;
		}
	}

	if (bullCount == 4) //If all 4 positions are BULL
	{
		winner = 'A'; //AI knows the player's sequence
		return true;
	}

	if (PlayerBullCount == 4) //If all 4 positions are BULL
	{
		winner = 'P'; //Player knows the AI's sequence
		return true;
	}

	return false;
}



void AI_Handler::AI_Turn(PlayerHandler& Player)
{
	char input[MAX_SIZE]; //Holds user input
	GuessSequence(Player); //Guess Sequence

	firstGuess = false;

	std::cout << "Enter C, B and N. With a space in between each: ";
	std::cin >> input[0] >> input[1] >> input[2] >> input[3];
	Player.PlayerConfirmCheck(input[0], input[1], input[2], input[3], Player);
	DeterminePlayerInput(input);
	std::cout << "Computer: Let me note that...\n";
	Sleep(3000);
}

//void AI_Handler::handleCows(int &j, std::vector<int> &cows)
//{
//	//only enters cows into vector if they are not there yet
//	if (std::find(cows.begin(), cows.end(), j) == cows.end())
//	{
//		cows.push_back(j);
//	}
//}


void AI_Handler::AI_Answer(tempStash input)
{
	char output[MAX_SIZE] =     //Holds AI response of B, C and N
	{'N','N', 'N', 'N'}; //Set N to everything as default

	
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		//Check for BULLS first
		if (AISequence[i].value == input.List[i]) //check for the same position
												  // and value
		{
			output[i] = 'B';
			if (!AIDisplaySequence[i].isBull)					//if it's not already a bull
			{
				AIDisplaySequence[i].isBull = true;				//set this index in array to is a bull
				//++PlayerBullCount;									//increment bull count

				RemoveCow(KnownAICows, AISequence[i].value, NumKnownCowsAI);

				continue;

				//get rid of cow if it is now a bull
				//playerGuessedCows.erase(std::remove(playerGuessedCows.begin(), playerGuessedCows.end(),
				//	input.List[i]), playerGuessedCows.end());
			}
		}

		//Check for COWS next
		for (int j = 0; j < MAX_SIZE; ++j) //check for same value, but different position
		{
			if (input.List[i] == AISequence[j].value && i != j)
			{
				output[i] = 'C';									//place c where the guess is, not in the actual sequence
				//handleCows(AISequence[i].value, playerGuessedCows);  //ADDED BY DAVE NADEAU, cheat/bug: if multiple cows are
																	//guessed in one turn, list is ordered in the correct sequence
				if (canBePlaced(KnownAICows, input.List[i]))
				{
					KnownAICows[NumKnownCowsAI].value = AISequence[j].value;
					++NumKnownCowsAI;
					j = MAX_SIZE;
				}
				
			}
		}
	}

	std::cout << "Computer: That would be...\n" << output[0] << " " 
			  << output[1] << " " << output[2] << " " 
			  << output[3] << "\n";
}

bool AI_Handler::canBePlaced(CattleCows* cattle, int value)
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		if (cattle[i].value == value) //If this value exists
		{
			return false;
		}
	}
	return true; //value does not exist
}

void AI_Handler::ResetCows()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		Cows[i].alreadyUsed = false; //Reset if it's been used
	}
}

int AI_Handler::ReturnCow(int LoopPos)
{
	int col = INVALID;

	for (int i = 0; i < MAX_SIZE; ++i)
	{
		//If cow isn't used, not invalid and has not been in this position
		if (!Cows[i].alreadyUsed && Cows[i].value != INVALID
			&& !Cows[i].previousPos[LoopPos])
		{
			col = i;
			i = MAX_SIZE; // leave loop
		}
	}

	return col; //return desired cow position
}

void AI_Handler::RemoveCow(CattleCows *cattle, int value, int size)
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{

		if (cattle[i].value == value) //if value is inside cow list
		{
			cattle[i].value = INVALID; //remove it
			cattle[i].ResetPos(); //Reset it's previos positions
			if (size > 0) //if number of cattle in list is > 0
			{
				--size; //remove a cow
			}
		}
	}
}

void AI_Handler::TakeInBull(int bullPos)
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		Cows[i].previousPos[bullPos] = true; // Set all values at bull to true
	}
}

void AI_Handler::ResetPlayerPos()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		GuessPlayerSequence[i].alreadyUsed = false;
	}
}
