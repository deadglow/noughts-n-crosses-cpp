#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

//Methods
int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

//Vars
const char cRowCap[] = "+-----------+\n";
const char cRowBreak[] = "|---+---+---|\n";
const char cCharA = 'X';
const char cCharB = 'O';
char cGridState[3][3]{};
int iCurX = 0;
int iCurY = 0;
bool bPlayer1Turn = true;

int main()
{
	while (true)
	{
		//Clear screen
		system("CLS");

		//Initialise output string
		char cOutput[100];
		//Add top cap
		strcpy_s(cOutput, 100, cRowCap);
	
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
					{
						cOutput[iRowOffset + i * 4] = '|';
					}
					//Add spaces
					for (int i = 0; i < 6; ++i)
					{
						cOutput[iRowOffset + 1 + i * 2] = ' ';
					}
				}
				else if (x == 2)
				{
					//Add newline
					cOutput[iRowOffset + 13] = '\n';
					//Add row break
					cOutput[iRowOffset + 14] = 0;
					strcat_s(cOutput, 100, cRowBreak);
				}

				//Draw cursor if current x/y pos match cursor x/y pos
				if (iCurX == x && iCurY == y)
				{
					cOutput[iRowOffset + 1 + 4 * x] = '[';
					cOutput[iRowOffset + 3 + 4 * x] = ']';
				}

				//Draw character, but ignore if not set yet
				if (cGridState[x][y] != 0)
				{
					cOutput[iRowOffset + 2 + 4 * x] = cGridState[x][y];
				}
			}
		}
		cOutput[84] = 0;
		strcat_s(cOutput, 100, cRowCap);
		cOutput[99] = 0;
	
		std::cout << cOutput;
		
		char ch;

		ch = _getch();

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
					if (bPlayer1Turn)
					{
						cGridState[iCurX][iCurY] = cCharA;
					}
					else
					{
						cGridState[iCurX][iCurY] = cCharB;
					}
					bPlayer1Turn = !bPlayer1Turn;
				}
			default:
				break;
		}

		iCurX = max(0, min(iCurX, 2));
		iCurY = max(0, min(iCurY, 2));

	}
	
	return 0;
}
