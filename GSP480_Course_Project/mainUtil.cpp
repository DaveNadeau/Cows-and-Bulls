#include"mainUtil.h"

void mainUtil::printPlayerSequence(PlayerHandler &player) 
{
	for (int i = 0; i < 4; i++)
	{
		//std::cout << input.List[i];
		std::cout << player.PlayerSequence[i];
	}
	
}

void mainUtil::printAISequence(AI_Handler AI)  //TEST FUNCTION
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << AI.AISequence[i].value;
	}
}

void mainUtil::printAIDisplaySequence(AI_Handler AI) //DISPLAYS BULLS AND UNKNOWNS
{
	for (int i = 0; i < 4; i++)
	{
		if (AI.AIDisplaySequence[i].isBull)
		{
			std::cout << AI.AISequence[i].value;
		}
		else
			std::cout << "_";
		
	}
}

void mainUtil::printCows(CattleCows *cows, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (cows[i].value != INVALID)
		{
			std::cout << cows[i].value << ", ";
		}
	}
		
}

void mainUtil::drawScreen(tempStash &input, AI_Handler &AI, PlayerHandler &Player) //draws screen
{
	std::cout << "                         Round: " << ROUND << std::endl;
	std::cout << "Player:                                      " << "Opponent:" << std::endl;
	printPlayerSequence(Player);
	
	std::cout << "                    Known opponent code: ";
	printAIDisplaySequence(AI);

	/*TEST FUNCTION, UNCOMMENT TO SEE THE AI SEQUENCE AND EXPERIMENT*/
	/*printAISequence(AI);  */           

	std::cout << std::endl;
	std::cout << "                                             Known Cows: ";
	printCows(AI.KnownAICows, AI.NumKnownCowsAI); //Fixed
	std::cout << std::endl;

}

//void mainUtil::checkWin(PlayerHandler &player, AI_Handler &AI)
//{
//	if (AI.bullCount == 4)
//	{
//		AI.hasWon = true;
//	}
//	else if (AI.PlayerBullCount == 4)
//	{
//		player.hasWon = true;
//	}
//}

void mainUtil::handleInput(tempStash &input)
{
	/*std::cin >> input.List[0] >> input.List[1] >> input.List[2] >> input.List[3];*/

	bool checking = true;

	while (checking) 
	{
		if (std::cin.fail() ||
			input.List[0] > 9 || input.List[0] < 0 || input.List[1] > 9 || input.List[1] < 0 ||
			input.List[2] > 9 || input.List[2] < 0 || input.List[3] > 9 || input.List[3] < 0)
		{
			std::cout << "You've entered an invalid option.\n";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "please enter 4 numbers with a space between each digit: ";
			std::cin >> input.List[0] >> input.List[1] >> input.List[2] >> input.List[3];
		}
		else
		{
			checking = false;
		}
	}
}

void mainUtil::RunGame()
{
	srand(time(NULL)); //initalize rand()
	char winner = 'T'; //holds winner of the game

	AI_Handler AI;
	PlayerHandler Player;

	tempStash input;
	std::cout << "please enter your secret code with a space between each digit: ";
	std::cin >> input.List[0] >> input.List[1] >> input.List[2] >> input.List[3];
	handleInput(input);
	Player.PlayerInputCheck(input);
	Player.PlayerSecret(Player, input);

	while (ROUND != (MAX_ROUND + 1) && !AI.WhoWon(winner))
	{
		

		if (whoseTurn == 0)	  //player turn
		{
			system("CLS");
			drawScreen(input, AI, Player);
			std::cout << "Player's turn..." << std::endl;
			std::cout << "What is your guess? Enter 4 numbers with a space in between:\n";
			std::cin >> input.List[0] >> input.List[1] >> input.List[2] >> input.List[3];	//player sequence
			handleInput(input);
			Player.PlayerInputCheck(input);
			AI.AI_Answer(input);
			/*checkWin(Player, AI);
			if (Player.hasWon)
			{
				system("CLS");
				drawScreen(input, AI, Player);
				Sleep(3000);
				break;
			}*/
			whoseTurn = 1;
			Sleep(3000);
		}
		else                  //AI turn
		{
			if (ROUND == 1)
			{
				AI.firstTurn = true;
			}
			else
			AI.firstTurn = false;
			system("CLS");
			drawScreen(input, AI, Player);
			AI.AI_Turn(Player);
			/*checkWin(Player, AI);
			if (AI.hasWon)
			{
				system("CLS");
				drawScreen(input, AI, Player);
				Sleep(3000);
				break;
			}*/
			ROUND += 1;
			whoseTurn = 0;
			Sleep(3000);
		}
	}
	if (winner == 'T')
	{
		std::cout << "                                  TIE!!!" << std::endl;
	}
	else if (winner == 'P')
	{
		std::cout << "\n" << "                          YOU WON IN " << ROUND << " ROUNDS!!!!";
	}
	else if (winner == 'A')
	{
		std::cout << "\n" << "            Sorry, you lost.  The computer guessed your sequence in " << ROUND << " rounds.";
	}
	
}