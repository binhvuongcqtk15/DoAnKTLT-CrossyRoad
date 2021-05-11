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

void startMenu() {
	GotoXY(12, 5); cout << "OOOOOO   OOOOOO   OOOOOOO   OOOOOO   OOOOOO   OO  OO       OOOOOO   OOOOOOO   OOOOOOO   OOOOO";
	GotoXY(12, 6); cout << "OO       OO  OO   OO   OO   OO       OO       OO  OO       OO  OO   OO   OO   OO   OO   OO  OO"; 
	GotoXY(12, 7); cout << "OO       OO OO    OO   OO   OOOOOO   OOOOOO     OO    ===  OO OO    OO   OO   OOOOOOO   OO   OO"; 
	GotoXY(12, 8); cout << "OO       OO  OO   OO   OO       OO       OO     OO         OO  OO   OO   OO   OO   OO   OO  OO"; 
	GotoXY(12, 9); cout << "OOOOOO   OO   OO  OOOOOOO   OOOOOO   OOOOOO     OO         OO   OO  OOOOOOO   OO   OO   OOOOO";
	
	GotoXY(48, 12); cout << "+-----------+-------+";
	GotoXY(48, 13); cout << "|  Option   | Press |";
	GotoXY(48, 14); cout << "|-----------+-------+";
	GotoXY(48, 15); cout << "| New Game  |   N   |";
	GotoXY(48, 16); cout << "| Load Game |   L   |";
	GotoXY(48, 17); cout << "| Exit      |  Esc  |";
	GotoXY(48, 18); cout << "| About     |   O   |";
	GotoXY(48, 19); cout << "+-----------+-------+";
	GotoXY(0, 0);
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