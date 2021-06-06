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

// run sub thread side-by-side main thread
void subThread() {
	// make game stop for a while, depend on current level
	int delay = 0;
	int time2stop = speed * 10 + 1;
	while (1) {
		if (state) {
			switch (direction) {
			case 'A': moveLeft(); break;
			case 'D': moveRight(); break;
			case 'W': moveUp(); break;
			case 'S': moveDown(); break;
			}
			direction = ' ';
			//check player lose or not
			if (isImpact(player_pos)) {
				processDead();
				delay = 1;
				time2stop = 0;
			}
			//start a loop to choose when to stop all car
			delay == 1 ? time2stop++ : time2stop--;
			if (time2stop == 0)
				delay = 1;
			else if (time2stop == speed * 10 + 1)
				delay = 0;
			if (delay == 0) {
				eraseCars();
				moveCars();
				drawCars();
				drawInfo();
			}
			//check if player pass the level
			if (player_pos.y == 2) {
				if (player_pos.x == prevPos[0] || player_pos.x == prevPos[1]) {
					processDead();
					delay = 1;
					time2stop = 0;
				}
				else {
					processPass(player_pos);
					delay = 0;
					time2stop = speed * 10 + 1;
				}
			}
			// sleep with time that clock has already calculated
			Sleep(time2stop);
		}
	}
}