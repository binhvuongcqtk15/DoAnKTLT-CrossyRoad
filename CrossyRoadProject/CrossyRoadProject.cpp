#pragma once
#include "varsANDlibs.h"
#include "consoleControl.h"
#include "gameCommand.h"
#include "gameControl.h"
using namespace std;

int main()
{
	int temp;
	FixConsoleWindow();
	srand(time(NULL));
	//resetData();
	//thread t1(subThread);
	startGame();
	while (1)
	{
		temp = toupper(_getch());
		if (state)
		{
			if (temp == 27)
			{
				//exitGame(t1.native_handle());
				return 0;
			}
			else if (temp == 'P')
			{
				//pauseGame(t1.native_handle());
			}
			else
			{
				//ResumeThread((HANDLE)t1.native_handle());
				if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')
				{
					direction = temp;
					subThread();
				}
			}
		}
		else
		{
			if (temp == 'Y') startGame();
			else
			{
				//exitGame(t1.native_handle());
				return 0;
			}
		}
	}
}