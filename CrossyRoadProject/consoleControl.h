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
	bool delay = false;
	int time2stop = speed * 3 + 1;
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
				continue;
			}
			GotoXY(40, 27);
			cout << delay << " " << time2stop << "\n";
			// start clock to delay
			delay == true ? time2stop++ : time2stop--;
			if (time2stop == 0 || time2stop == speed * 3 + 1)
				delay = !delay;
			if (!delay) {
				eraseCars();
				moveCars();
				drawCars("=");
				drawInfo();
				drawBox(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
				drawBox(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
			}
			//check if player pass the level
			if (player_pos.y == 2) {
				if (player_pos.x == prevPos[0] || player_pos.x == prevPos[1]) 
					processDead();
				else {
					processPass(player_pos);
					time2stop = speed * 3 + 1;
					delay = false;
				}
			}
		}
		// sleep with time that clock has already calculated
		Sleep(time2stop);
	}
}