#pragma once
#include "varsANDlibs.h"
#include "consoleControl.h"
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
	player = DEFAULT_CHARACTER_POS;
	if (carArray == NULL) {
		carArray = new POINT * [MAX_CAR];
		for (int i = 0; i < MAX_CAR; i++)
			carArray[i] = new POINT[MAX_CAR_LENGTH];
		for (int i = 0; i < MAX_CAR; i++) {
			int temp = (rand() % (WIDTH_CONSOLE - MAX_CAR_LENGTH)) + 1;
			for (int j = 0; j < MAX_CAR_LENGTH; j++){
				carArray[i][j].x = temp + j;
				carArray[i][j].y = 3 + i;
			}
		}
	}
	currpos[0] = NULL; currpos[1] = NULL;
}

bool isImpact(const POINT& p, int d) {
	if (d == 2 || d == 24)
		return false;
	for (int i = 0; i < MAX_CAR_LENGTH; i++)
		if (p.x == carArray[d - 3][i].x && p.y == carArray[d - 3][i].y) 
			return true;
	return false;
}

void processDead() {
	state = 0;
	GotoXY(46, PLAYGROUND_SECTION_HEIGHT + 2);
	cout << "You're hit by a Car (T.T)";
	GotoXY(38, PLAYGROUND_SECTION_HEIGHT + 3);
	cout << "Press R to restart or any keys to exit";
}

void processPass(POINT& p) {
	currpos[speed - 1] = p.x;
	speed == MAX_SPEED ? speed = 1 : speed++;
	p = DEFAULT_CHARACTER_POS;
	direction = 'D';
}

void drawBoard(int x, int y, int width, int height) {
	GotoXY(x, y);
	if (y == 0) {
		cout << "------------------------------------------------------Crossy Road";
		cout << "------------------------------------------------------\n";
		y++;
	}
	GotoXY(x, y);
	cout << "+";
	for (int i = 1; i < width; i++)
		cout << "-";
	cout << "+";
	GotoXY(x, height + y);
	cout << "+";
	for (int i = 1; i < width; i++)
		cout << "-";
	cout << "+";
	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x, i);
		cout << "|";
		GotoXY(x + width, i);
		cout << "|";
	}
	GotoXY(0, 0);
}

void drawCars(string s) {
	for (int i = 0; i < MAX_CAR; i++) {
		for (int j = 0; j < MAX_CAR_LENGTH; j++) {
			GotoXY(carArray[i][j].x, carArray[i][j].y);
			cout << s;
		}
	}
}
void drawCharacter(const POINT& p, string s) {
	GotoXY(p.x, p.y);
	cout << s;
}

void drawInfo() {
	GotoXY(5, HEIGHT_CONSOLE - 2);
	cout << "Player Name: " << player_name;
	GotoXY(5, HEIGHT_CONSOLE - 1);
	cout << "Level: " << speed;
	GotoXY(5, HEIGHT_CONSOLE);
	cout << "Number of steps: " << step;
}

void moveCars() {
	for (int i = 1; i < MAX_CAR; i += 2) {
		cnt = 0;
		do {
			cnt++;
			for (int j = 0; j < MAX_CAR_LENGTH - 1; j++) {
				carArray[i][j] = carArray[i][j + 1];
			}
			carArray[i][MAX_CAR_LENGTH - 1].x + 1 == WIDTH_CONSOLE ? carArray[i][MAX_CAR_LENGTH - 1].x = 1 : carArray[i][MAX_CAR_LENGTH - 1].x++;
		} while (cnt < speed);
	}
	for (int i = 0; i < MAX_CAR; i += 2) {
		cnt = 0;
		do {
			cnt++;
			for (int j = MAX_CAR_LENGTH - 1; j > 0; j--) {
				carArray[i][j] = carArray[i][j - 1];
			}
			carArray[i][0].x - 1 == 0 ? carArray[i][0].x = WIDTH_CONSOLE - 1 : carArray[i][0].x--;
		} while (cnt < speed);
	}
}

void eraseCars() {
	for (int i = 0; i < MAX_CAR; i += 2) {
		cnt = 0;
		do {
			GotoXY(carArray[i][MAX_CAR_LENGTH - 1 - cnt].x, carArray[i][MAX_CAR_LENGTH - 1 - cnt].y);
			cout << " ";
			cnt++;
		} while (cnt < speed);
	}
	for (int i = 1; i < MAX_CAR; i += 2) {
		cnt = 0;
		do {
			GotoXY(carArray[i][0 + cnt].x, carArray[i][0 + cnt].y);
			printf(" ");
			cnt++;
		} while (cnt < speed);
	}
}
