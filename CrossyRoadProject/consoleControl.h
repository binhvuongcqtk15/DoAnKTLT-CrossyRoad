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

void subThread() {
	while (1) {
		if (state) {
			//cerr << "OK";
			if(direction == int('A'))
				moveLeft();
			else if(direction == int('D'))
				moveRight();
			else if (direction == int('W')) {
				//cout << "move start";
				moveUp();
				cout << "moveOK";
			}
			else if(direction == int('S'))
				moveDown();
			direction = ' ';
			eraseCars();
			moveCars();
			drawCars('=');
			cout << "OK1";
			//drawBoard(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
			//drawBoard(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
			if (isImpact(player, player.y))
				processDead();
			cout << "OK2";
			if (player.y == 2)
				processPass(player);
			cout << "OK";
			Sleep(10);
			cout << "OKK";
		}
	}
}