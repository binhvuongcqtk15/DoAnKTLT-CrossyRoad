#pragma once
#include "varsANDlibs.h"
using namespace std;

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void resetData() {
	direction = 'D';
	speed = 1;
	step = 0;
	player_name = DEFAULT_PLAYER_NAME;
	player_pos = DEFAULT_CHARACTER_POS;
	if (carArray == NULL)
		carArray = new int* [MAX_CAR];
	if (carInfo == NULL)
		carInfo = new CAR[MAX_CAR];
	for (int i = 0; i < MAX_CAR; i++) {
		carInfo[i].direction = rand() % 2;
		carInfo[i].length = MIN_CAR_LENGTH + rand() % (MAX_CAR_LENGTH - MIN_CAR_LENGTH + 1);
		carArray[i] = new int[carInfo[i].length];
		int temp = (rand() % (WIDTH_CONSOLE - carInfo[i].length)) + 1;
		for (int j = 0; j < carInfo[i].length; j++)
			carArray[i][j] = temp + j; 
	}
	memset(prevPos, 0, sizeof(prevPos));
}

bool isImpact(const POINT& p) {
	if (player_pos.y == 2 || player_pos.y == 24)
		return false;
	for (int i = 0; i < carInfo[player_pos.y - 3].length; i++)
		if (p.x == carArray[player_pos.y - 3][i])
			return true;
	return false;
}

void clearBoard(int x, int y, int width, int height) {
	for (int i = x; i <= x + width; ++i) {
		for (int j = y; j <= y + height; ++j) {
			GotoXY(i, j);
			cout << " ";
		}
	}
}

void drawSelectBox(int x, int y, int width, int height) {
	for (int i = x; i < x + width; ++i) {
		GotoXY(i, y);
		cout << char(196);
		GotoXY(i, y + height);
		cout << char(196);
	}
	for (int i = y; i < y + height; ++i) {
		GotoXY(x, i);
		cout << char(179);
		GotoXY(x + width - 4, i);
		cout << char(179);
		GotoXY(x + width, i);
		cout << char(179);
	}

	GotoXY(x, y); cout << char(218);
	GotoXY(x + width - 4, y); cout << char(194);
	GotoXY(x, y + height); cout << char(192);
	GotoXY(x + width - 4, y + height); cout << char(193);
	GotoXY(x + width, y); cout << char(191);
	GotoXY(x + width, y + height); cout << char(217);
}

void drawPlayGround(int x, int y, int width, int height) {
	GotoXY(x, y);
	if (y == 0) {
		cout << char(218);
		for (int i = 1; i <= 52; ++i)
			cout << char(196);
		cout << " Crossy Road ";
		for (int i = 1; i <= 52; ++i)
			cout << char(196);
		cout << char(191) << "\n";
		y++;
	}
	GotoXY(x, y);
	cout << char(195);
	for (int i = x + 1; i < x + width; i++)
		cout << char(196);
	cout << char(180);
	GotoXY(x, height + y);
	cout << char(192);
	for (int i = x + 1; i < x + width; i++)
		cout << char(196);
	cout << char(217);
	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x, i);
		cout << char(179);
		GotoXY(x + width, i);
		cout << char(179);
	}
	GotoXY(0, 0);
}

void drawCars(string s) {
	for (int i = 0; i < MAX_CAR; i++) {
		for (int j = 0; j < carInfo[i].length; j++) {
			GotoXY(carArray[i][j], i + 3);
			cout << s;
		}
	}
}
void drawCharacter(const POINT& p, string s) {
	GotoXY(p.x, p.y);
	cout << s;
}

void drawInfo() {
	GotoXY(5, HEIGHT_CONSOLE - 2); cout << "Player Name: " << player_name;
	GotoXY(5, HEIGHT_CONSOLE - 1); cout << "Level: " << speed;
	GotoXY(5, HEIGHT_CONSOLE - 0); cout << "Number of steps: " << step;

	for (int i = 0; i < INFO_SECTION_HEIGHT - 1; ++i) {
		GotoXY(50, HEIGHT_CONSOLE - i);
		cout << char(179);
		GotoXY(74, HEIGHT_CONSOLE - i);
		cout << char(179);
		GotoXY(98, HEIGHT_CONSOLE - i);
		cout << char(179);
	}

	GotoXY(51, HEIGHT_CONSOLE - 1); cout << " Move   " << char(16) << "   W,A,S,D ";
	GotoXY(75, HEIGHT_CONSOLE - 2); cout << " Pause Game    " << char(16) << "   P";
	GotoXY(75, HEIGHT_CONSOLE - 1); cout << " Save Game     " << char(16) << "   K";
	GotoXY(75, HEIGHT_CONSOLE - 0); cout << " Restart Game  " << char(16) << "   R";

	GotoXY(99, HEIGHT_CONSOLE - 1); cout << " Exit   " << char(16) << "   Esc ";
}

void processDead() {
	clearBoard(1, PLAYGROUND_SECTION_HEIGHT + 2, WIDTH_CONSOLE - 2, INFO_SECTION_HEIGHT - 2);
	state = 0;
	GotoXY(46, PLAYGROUND_SECTION_HEIGHT + 2);
	cout << "You're hit by a Car (T.T)";
	GotoXY(38, PLAYGROUND_SECTION_HEIGHT + 3);
	cout << "Press R to restart or any keys to exit";
}

void processPass(POINT& p) {
	prevPos[speed - 1] = p.x;
	if (speed == MAX_SPEED) {
		speed = 1;
	}
	else {
		speed++;
		for (int i = 0; i < MAX_CAR; ++i)
			carInfo[i].direction = rand() % 2;
	}
	prevPos[speed - 1] = p.x;
	p = DEFAULT_CHARACTER_POS;
	direction = 'D';
}

void moveCars() {
	for (int i = 0; i < MAX_CAR; i++) {
		if (carInfo[i].direction == 1) {
			speedUP = 0;
			do {
				speedUP++;
				for (int j = 0; j < carInfo[i].length - 1; j++) {
					carArray[i][j] = carArray[i][j + 1];
				}
				carArray[i][carInfo[i].length - 1] + 1 == WIDTH_CONSOLE ? carArray[i][carInfo[i].length - 1] = 1 : carArray[i][carInfo[i].length - 1]++;
			} while (speedUP < speed);
		}
		if (carInfo[i].direction == 0) {
			speedUP = 0;
			do {
				speedUP++;
				for (int j = carInfo[i].length - 1; j > 0; j--) {
					carArray[i][j] = carArray[i][j - 1];
				}
				carArray[i][0] - 1 == 0 ? carArray[i][0] = WIDTH_CONSOLE - 1 : carArray[i][0]--;
			} while (speedUP < speed);
		}
	}
}

void eraseCars() {
	for (int i = 0; i < MAX_CAR; i++) {
		if (carInfo[i].direction == 0) {
			speedUP = 0;
			do {
				GotoXY(carArray[i][carInfo[i].length - 1 - speedUP], i + 3);
				cout << " ";
				speedUP++;
			} while (speedUP < speed);
		}
		if (carInfo[i].direction == 1) {
			speedUP = 0;
			do {
				GotoXY(carArray[i][0 + speedUP], i + 3);
				printf(" ");
				speedUP++;
			} while (speedUP < speed);
		}
	}
}
