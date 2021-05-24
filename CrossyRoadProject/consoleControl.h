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
	GotoXY(13, 5); cout << "OOOOOO   OOOOOO   OOOOOOO   OOOOOO   OOOOOO   OO  OO       OOOOOO   OOOOOOO   OOOOOOO   OOOOO";
	GotoXY(13, 6); cout << "OO       OO  OO   OO   OO   OO       OO       OO  OO       OO  OO   OO   OO   OO   OO   OO  OO";
	GotoXY(13, 7); cout << "OO       OO OO    OO   OO   OOOOOO   OOOOOO     OO    ===  OO OO    OO   OO   OOOOOOO   OO   OO";
	GotoXY(13, 8); cout << "OO       OO  OO   OO   OO       OO       OO     OO         OO  OO   OO   OO   OO   OO   OO  OO";
	GotoXY(13, 9); cout << "OOOOOO   OO   OO  OOOOOOO   OOOOOO   OOOOOO     OO         OO   OO  OOOOOOO   OO   OO   OOOOO";

	for (int i = 0; i <= 3; ++i)
		drawSelectBox(51, 12 + 3 * i, 16, 2);

	GotoXY(52, 13); cout << "New Game";
	GotoXY(65, 13); cout << "N";
	GotoXY(52, 16); cout << "Load Game";
	GotoXY(65, 16); cout << "L";
	GotoXY(52, 19); cout << "Exit";
	GotoXY(64, 19); cout << "Esc";
	GotoXY(52, 22); cout << "About";
	GotoXY(65, 22); cout << "O";
	GotoXY(0, 0);


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
			direction = ' ';
			if (isImpact(player_pos)) {
				processDead();
				continue;
			}
			eraseCars();
			moveCars();
			drawCars("=");
			drawInfo();
			drawPlayGround(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
			drawPlayGround(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
			if (player_pos.y == 2) {
				if (player_pos.x == prevPos[0] || player_pos.x == prevPos[1]) 
					processDead();
				else
					processPass(player_pos);
			}
		}
	}
}