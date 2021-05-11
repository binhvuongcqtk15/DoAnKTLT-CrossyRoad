#pragma once
#include "varsANDlibs.h"
#include "consoleControl.h"
#include "gameControl.h"
using namespace std;

void deleteCarArray() {
	for (int i = 0; i < MAX_CAR; i++)
		delete[] carArray[i];
	delete[] carArray;
}

void startMenu()
{
	GotoXY(45, 10); printf("Tai lai Game (Nhan phim T)");
	GotoXY(45, 11); printf("Bat dau choi (Phim bat ki)");
}

void startGame() {
	system("cls");
	resetData();
	drawBoard(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
	drawBoard(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
	state = true;
}

void exitGame(HANDLE t) {
	system("cls"); 
	TerminateThread(t, 0);
	deleteCarArray();
	exit(1);
}

void pauseGame(HANDLE t) {
	SuspendThread(t);
}