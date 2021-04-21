#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

//Min and max methods for limiting the cursor
int min(int a, int b)
{
	return (a < b)? a : b;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

#define CHAR_A 'X'
#define CHAR_B 'O'
#define PLACE_KEY 'l'
#define ROW_CAP "+-----------+\n"
#define ROW_BREAK "|---+---+---|\n"

int main()
{
	//Main loop
	while (true)
	{
		char cGridState[3][3]{};
		int iCurX = 1;
		int iCurY = 1;
		bool bPlayer1Turn = true;
		//Used to end game after 9 turns
		int iTurnCounter = 0;
		char winner = 0;
		
		//Round loop
		while (true)
		{
			//Clear screen
			system("CLS");

			//Initialise output string
			char cOutput[100];
			//Add top cap
			strcpy_s(cOutput, 100, ROW_CAP);

			int iRowOffset = 0;
			for (int y = 0; y < 3; ++y)
			{
				//How many chars to skip over to reach row
				iRowOffset = y * 28 + 14;

				for (int x = 0; x < 3; ++x)
				{
					//Only draw walls and spaces once per row
					if (x == 0)
					{
						//Add walls
						for (int i = 0; i < 4; ++i)
							cOutput[iRowOffset + i * 4] = '|';
						//Add spaces
						for (int i = 0; i < 6; ++i)
							cOutput[iRowOffset + 1 + i * 2] = ' ';
					}
					else if (x == 2)
					{
						//Add newline
						cOutput[iRowOffset + 13] = '\n';
						//Add row break
						cOutput[iRowOffset + 14] = 0;
						strcat_s(cOutput, 100, ROW_BREAK);
					}

					//Draw cursor if current x/y pos match cursor x/y pos
					if (iCurX == x && iCurY == y)
					{
						cOutput[iRowOffset + 1 + 4 * x] = '[';
						cOutput[iRowOffset + 3 + 4 * x] = ']';
					}

					//Draw character, but ignore if not set yet
					if (cGridState[x][y] != 0)
						cOutput[iRowOffset + 2 + 4 * x] = cGridState[x][y];
				}
			}
			cOutput[84] = 0;
			strcat_s(cOutput, 100, ROW_CAP);
			cOutput[99] = 0;

			//DRAW!
			std::cout << cOutput;

			//Check win conditions after drawing the thing so player can see final move
			//Check centre range
			char centre = cGridState[1][1];
			if (centre != 0)
			{
				if ((centre == cGridState[0][1] && centre == cGridState[2][1]) ||
					(centre == cGridState[1][0] && centre == cGridState[1][2]) ||
					(centre == cGridState[0][0] && centre == cGridState[2][2]) ||
					(centre == cGridState[0][2] && centre == cGridState[2][0]))
				{
					winner = centre;
				}
			}
			//If no match then check edges
			if (winner == 0)
			{
				//top left, middle left, bottom left
				if ((cGridState[0][0] == cGridState[0][1]) && (cGridState[0][1] == cGridState[0][2]))
					winner = cGridState[0][1];
				//top left, top middle, top right
				else if ((cGridState[0][0] == cGridState[1][0]) && (cGridState[1][0] == cGridState[2][0]))
					winner = cGridState[1][0];
				//top right, right middle, bottom right
				else if ((cGridState[2][0] == cGridState[2][1]) && (cGridState[2][1] == cGridState[2][2]))
					winner = cGridState[2][1];
				//bottom right, bottom middle, bottom left
				else if ((cGridState[2][2] == cGridState[1][2]) && (cGridState[1][2] == cGridState[0][2]))
					winner = cGridState[1][2];
			}

			if (winner != 0 || iTurnCounter >= 9)
			{
				break;
			}

			//Print player turn message
			if (bPlayer1Turn)
				cout << "P1 turn" << endl;
			else
				cout << "P2 turn" << endl;

			cout << "WASD to move cursor. " << PLACE_KEY << " to place piece." << endl;

			//Get input
			char ch = _getch();

			//Resolve input
			switch (ch)
			{
				case 'a':
					iCurX--;
					break;
				case 'd':
					iCurX++;
					break;
				case 'w':
					iCurY--;
					break;
				case 's':
					iCurY++;
					break;
				case 'l':
					if (cGridState[iCurX][iCurY] == 0)
					{
						//Place char and increment turn
						cGridState[iCurX][iCurY] = bPlayer1Turn ? CHAR_A : CHAR_B;						
						bPlayer1Turn = !bPlayer1Turn;
						iTurnCounter++;
					}
				default:
					break;
			}

			//Limit cursor to playspace
			iCurX = max(0, min(iCurX, 2));
			iCurY = max(0, min(iCurY, 2));
		}

		//Print win messages
		if (winner == CHAR_A)
			cout << "Player 1 wins!" << endl;
		else if (winner == CHAR_B)
			cout << "Player 2 wins!" << endl;
		else
			cout << "Tie!" << endl;

		//Restart/quit prompt
		cout << "Any input to restart, 'q' to quit." << endl;
		if (_getch() == 'q')
			break;
	}
	
	return 0;
}