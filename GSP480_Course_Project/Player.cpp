#include"Player.h"

void PlayerHandler::PlayerInputCheck(tempStash& input)
{

	int c = 0;
	int p = 1;
	char test = 1;
	while (c < 4 && p < 4)
	{
		for (int i = 0 ; i < 4; i++)
		{
			check[i] = input.List[i];
		}
		if (input.List[c] > 9 || input.List[c] < 0)
		{
			std::cout << "There are invalid numbers.\n"
				<< "Only enter whole numbers that are 0 through 9.\n"
				<< "Please re-enter your input with a space between each digit:\n";
			std::cin >> input.List[0] >> input.List[1] >> input.List[2] >> input.List[3];

			Sleep(3000);
			check[0] = input.List[0];
			check[1] = input.List[1];
			check[2] = input.List[2];
			check[3] = input.List[3];
			p = 0;
		}
		if (check[c] == input.List[p])
		{
			std::cout << "There are duplicates.\n"
				      << "Please re-enter your input with a space between each digit: \n";
			std::cin >> input.List[0] >> input.List[1] >> input.List[2] >> input.List[3];
			p=0;
		}
		if (p == 3)
		{
			c++;
			p = c; 
		}
		p++;
	}
}

void PlayerHandler::PlayerConfirmCheck(char& input0, char& input1, char& input2, char& input3, PlayerHandler& Player)
{

	bool good = false;
	int i = 0;
	check[0] = 'N';
	check[1] = 'N';
	check[2] = 'N';
	check[3] = 'N';
	lowercheck[0] = 'n';
	lowercheck[1] = 'n';
	lowercheck[2] = 'n';
	lowercheck[3] = 'n';
	char input[4] = { input0,input1,input2,input3 };
	while (good != true)
	{
		if ((input0 == 'C' || input0 == 'B' || input0 == 'N' || input0 == 'c' || input0 == 'b' || input0 == 'n') &&
			(input1 == 'C' || input1 == 'B' || input1 == 'N' || input1 == 'c' || input1 == 'b' || input1 == 'n') &&
			(input2 == 'C' || input2 == 'B' || input2 == 'N' || input2 == 'c' || input2 == 'b' || input2 == 'n') &&
			(input3 == 'C' || input3 == 'B' || input3 == 'N' || input3 == 'c' || input3 == 'b' || input3 == 'n'))
		{
			good = true;
		}
		else
		{
			std::cout << "There is an invalid input slot.\n" 
					  << "Please only enter C, B, N with a space between each letter:\n";
			std::cin >> input0 >> input1 >> input2 >> input3;
			input[0] = input0;
			input[1] = input1;
			input[2] = input2;
			input[3] = input3;
		}
	}
	for (i = 0;i < 4; i++)
	{
		if (Player.PlayerSequence[i] == Player.AISequence[i])
		{
			check[i] = 'B';
			lowercheck[i] = 'b';
		}
	}
	for (i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (Player.PlayerSequence[i] == Player.AISequence[j])
			{
				if (check[j] != 'B')
				{
					check[j] = 'C';
					lowercheck[j] = 'c';   //switched to lowercheck from "check".  DN
					break;
				}
			}
		}
	}
	for (i = 0;i < 4;i++)
	{
		//if (check[i] != input[i] || lowercheck[i] != input[i])  //one of these will always be true and result in re-input 
		if (check[i] != input[i] && lowercheck[i] != input[i])		//changed to &&. DN
		{
			std::cout << "Please dont cheat the AI. Re-input the correct designations:\n";
			std::cin >> input0 >> input1 >> input2 >> input3;
			good = false;
			while (good != true)
			{
				if ((input0 == 'C' || input0 == 'B' || input0 == 'N' || input0 == 'c' || input0 == 'b' || input0 == 'n') &&
					(input1 == 'C' || input1 == 'B' || input1 == 'N' || input1 == 'c' || input1 == 'b' || input1 == 'n') &&
					(input2 == 'C' || input2 == 'B' || input2 == 'N' || input2 == 'c' || input2 == 'b' || input2 == 'n') &&
					(input3 == 'C' || input3 == 'B' || input3 == 'N' || input3 == 'c' || input3 == 'b' || input3 == 'n'))
				{
					input[0] = input0;
					input[1] = input1;
					input[2] = input2;
					input[3] = input3;
					i = -1;
					good = true;
				}
				else
				{
					std::cout << "There is an invalid input slot.\n"
							  << "Please only enter C, B, N with a space between each letter:\n";
					std::cin >> input0 >> input1 >> input2 >> input3;
					input[0] = input0;
					input[1] = input1;
					input[2] = input2;
					input[3] = input3;
				}
			}
		}
	}
}
void PlayerHandler::AIGuess(PlayerHandler& Player, tempStash& guess)
{
	for (int i = 0;i < 4;i++)
	{
		Player.AISequence[i] = guess.List[i];
	}
}
void PlayerHandler::PlayerSecret(PlayerHandler& Player, tempStash& input)
{
	for (int i = 0;i < 4;i++)
	{
		Player.PlayerSequence[i] = input.List[i];
	}
}