#pragma once
#include "varsANDlibs.h"
#include "gameMovement.h"
using namespace std;

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void startMenu() {
	GotoXY(12, 5); cout << "OOOOOO   OOOOOO   OOOOOOO   OOOOOO   OOOOOO   OO  OO       OOOOOO   OOOOOOO   OOOOOOO   OOOOO";
	GotoXY(12, 6); cout << "OO       OO  OO   OO   OO   OO       OO       OO  OO       OO  OO   OO   OO   OO   OO   OO  OO";
	GotoXY(12, 7); cout << "OO       OO OO    OO   OO   OOOOOO   OOOOOO     OO    ===  OO OO    OO   OO   OOOOOOO   OO   OO";
	GotoXY(12, 8); cout << "OO       OO  OO   OO   OO       OO       OO     OO         OO  OO   OO   OO   OO   OO   OO  OO";
	GotoXY(12, 9); cout << "OOOOOO   OO   OO  OOOOOOO   OOOOOO   OOOOOO     OO         OO   OO  OOOOOOO   OO   OO   OOOOO";

	GotoXY(48, 12); cout << "+-----------+-------+";
	GotoXY(48, 13); cout << "|  Option   | Press |";
	GotoXY(48, 14); cout << "+-----------+-------+";
	GotoXY(48, 15); cout << "| New Game  |   N   |";
	GotoXY(48, 16); cout << "| Load Game |   L   |";
	GotoXY(48, 17); cout << "| Exit      |  Esc  |";
	GotoXY(48, 18); cout << "| About     |   O   |";
	GotoXY(48, 19); cout << "+-----------+-------+";
	GotoXY(0, 0);
}

void infoMenu() {

}

void subThread() {
	while (1) {
		if (state) {
			switch (direction) {
			case 'A': moveLeft(); break;
			case 'D': moveRight(); break;
			case 'W': moveUp(); break;
			case 'S': moveDown(); break;
			}
			//system("pause");
			direction = ' ';
			eraseCars();
			moveCars();
			drawCars("=");
			drawInfo();
			drawBoard(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
			drawBoard(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
			if (isImpact(player_pos, player_pos.y)) {
				processDead();
			}
			if (player_pos.y == 2) {
				if (player_pos.x == prevPos[0] || player_pos.x == prevPos[1]) 
					processDead();
				else
					processPass(player_pos);
			}
		}
	}
}