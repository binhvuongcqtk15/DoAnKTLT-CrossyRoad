#include "varsANDlibs.h"
#include "gameCommand.h"
#include "gameControl.h"
#include "gameMovement.h"
#include "consoleControl.h"
using namespace std;


//Hàm lưu người chơi
/*void SaveGame(char* player)
{
	//strcat(player,".txt");
	//FILE* fp = fopen(player,"w");
	fprintf(fp,"%d\n",speed);
	for (int i=0;i<MAX_CAR;i++)
	{
		for (int j=0;j<MAX_CAR_LENGTH;j++)
			fprintf(fp,"%d ",carArray[i][j].x);
		fprintf(fp,"\n");
	}
	if (speed>1)
		fprintf(fp,"%d",currpos[0]);
	if (speed>2)
		fprintf(fp," %d",currpos[1]);
	fprintf(fp,"\n%d %d",player.x,player.y);
	fclose(fp);
}*/
//Hàm đọc lại dữ liệu người chơi
/*void ReGame(char* player)
{
	system("cls");
	drawBoard(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
	strcat(player,".txt");
	FILE* fp = fopen(player,"r");
	fscanf(fp,"%d",&speed);
	for (int i=0;i<MAX_CAR;i++)
		for (int j=0;j<MAX_CAR_LENGTH;j++)
			fscanf(fp,"%d",&carArray[i][j].x);
	if (speed>1)
	{
		fscanf(fp,"%d ",&currpos[0]);
		GotoXY(currpos[0],1);
		printf("Y");
	}
	if (speed>2)
	{
		fscanf(fp,"%d ",&currpos[1]);
		GotoXY(currpos[1],1);
		printf("Y");
	}
	fscanf(fp,"%d %d",&player.x,&player.y);
	fclose(fp);
	DrawCars("=");
	drawCharacter(player,"Y");
}*/
int main()
{
	int temp;
	FixConsoleWindow();
	srand(time(NULL));
	thread t1(subThread);
	startMenu();
	temp=toupper(_getch());
	if (temp=='T')
	{
		resetData();
		pauseGame(t1.native_handle());
		GotoXY(0, PLAYGROUND_SECTION_HEIGHT + 2);
		printf("Type name: ");
		//gets(player_name);
		//ReGame(player_name);
		state = true;
	}
	else
		startGame();
	while (1)
	{
		temp = toupper(_getch());
		if (state)
		{
			if (temp == 27)
			{
				exitGame(t1.native_handle());
				return 0;
			}
			else if (temp == 'P')
			{
			 	pauseGame(t1.native_handle());
			}
			else if (temp == 'L')
			{
				pauseGame(t1.native_handle());
				GotoXY(0, PLAYGROUND_SECTION_HEIGHT + 2);
				printf("Type name: ");
				//gets(player_name);
				//SaveGame(player_name);
				exitGame(t1.native_handle());
			}
			else if (temp=='T')
			{
				pauseGame(t1.native_handle());
				GotoXY(0, PLAYGROUND_SECTION_HEIGHT + 2);
				printf("Type name: ");
				//gets(player_name);
				//ReGame(player_name);
			}
			else
			{
				ResumeThread((HANDLE)t1.native_handle());
				if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')
				{
					direction = temp;
				}
			}
		}
		else
		{
			if (temp == 'Y') startGame();
			else
			{
				exitGame(t1.native_handle());
				return 0;			}
		}
	}
}
