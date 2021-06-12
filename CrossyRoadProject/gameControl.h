#pragma once
#include "varsANDlibs.h"
using namespace std;

// check if player impact with car
bool isImpact(const POINT& p) {
	if (player_pos.y == 2 || player_pos.y == 24)
		return false;
	for (int i = 0; i < carInfo[player_pos.y - 3].length; i++)
		if (p.x == carArray[player_pos.y - 3][i])
			return true;
	return false;
}

// fill rectangle area start at (x, y) to (x+width, y+height) with string s 
void fillBox(int x, int y, int width, int height, string s) {

	setTextColor(3);
	for (int i = x; i <= x + width; i += int(s.length())) {
		for (int j = y; j <= y + height; ++j) {
			GotoXY(i, j);
			cout << s;
		}
	}
}

// decide what to do when player lose
void processDead() {
	ghost_pos.y = max(player_pos.y, 8);
	ghost_pos.x = min(player_pos.x, WIDTH_CONSOLE - 8);

	setTextColor(8);
	for (int i = PLAYGROUND_SECTION_HEIGHT; i > ghost_pos.y; --i) {
		fillBox(1, i, 4, 0, "X_X");
		fillBox(4, i, WIDTH_CONSOLE - 7, 0, "   X_X");
	}
	while (ghost_pos.y > 5) {
		fillBox(1, ghost_pos.y + 1, 4, 0, "X_X");
		fillBox(4, ghost_pos.y + 1, WIDTH_CONSOLE - 7, 0, "   X_X");
		for (int i = ghost_height - 1; i >= 0; i--) {
			fillBox(1, ghost_pos.y - i, WIDTH_CONSOLE - 2, 0, " ");
			GotoXY(ghost_pos.x, ghost_pos.y - i); 
			setTextColor(6);
			cout << ghost_shape[ghost_height - i - 1];
		}
		ghost_pos.y--;
		Sleep(75);
	}
	while (ghost_pos.y > 0) {
		fillBox(1, ghost_pos.y + 1, 4, 0, "X_X");
		fillBox(4, ghost_pos.y + 1, WIDTH_CONSOLE - 7, 0, "   X_X");
		for (int i = ghost_pos.y - 2; i >= 0; i--) {
			fillBox(1, ghost_pos.y - i, WIDTH_CONSOLE - 2, 0, " ");
			GotoXY(ghost_pos.x, ghost_pos.y - i);
			setTextColor(6);
			cout << ghost_shape[ghost_height - i - 1];
		}
		ghost_pos.y--;
		Sleep(100);
	}
	fillBox(1, 1, WIDTH_CONSOLE - 2, HEIGHT_CONSOLE - 3, " ");
	Sleep(250);
	endGameMenu();
	setTextColor(7);
}

// decide what to do when player win a level
void processPass(POINT& p) {
	prevPos[speed - 1] = p.x;
	if (speed == MAX_SPEED) {
		for (int i = 0; i < 3; ++i) {
			GotoXY(prevPos[i], 2);
			cout << " ";
		}
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

// draw character s at position p a.k.a (p.x, p.y)
void drawCharacter(const POINT& p, string s) {
	setTextColor(6);
	GotoXY(p.x, p.y);
	cout << s;
	setTextColor(7);
}

// draw car in console
void drawCars() {
	setTextColor(8);
	for (int i = 0; i < MAX_CAR; i++) {
		string curCar(carInfo[i].length, char(223));
		curCar[1] = char(15);
		curCar[curCar.length() - 2] = char(15);
		if (carInfo[i].direction == 1) {
			curCar[0] = char(96);
			curCar[curCar.length() - 1] = char(62);
		}
		else {
			curCar[0] = char(60);
			curCar[curCar.length() - 1] = char(39);
		}
		for (int j = 0; j < carInfo[i].length; j++) {
			GotoXY(carArray[i][j], i + 3);
			cout << curCar[j];
		}
	}
	setTextColor(7);
}

// make car move around
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

// erase car, also use to change car position
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
				cout << " ";
				speedUP++;
			} while (speedUP < speed);
		}
	}
}

// draw select box in Menu for user to choose action at (x, y)
void drawSelectBox(int x, int y, int width, int height) {
	setTextColor(3);
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
	setTextColor(7);
}

//draw about
void drawAbout() {
	setTextColor(6);
	GotoXY(40, 7); cout << "DO AN KY THUAT LAP TRINH: GAME BANG QUA DUONG";
	setTextColor(14);
	GotoXY(65, 9); cout << "Giao vien huong dan: TRUONG TOAN THINH";
	setTextColor(6);
	GotoXY(25, 11); cout << "Thuc hien boi: Nhom 15 - 20CTT1 - FIT - HCMUS";
	setTextColor(14);
	GotoXY(40, 12); cout << "+ Nguyen Minh An\t\t20120029";
	GotoXY(40, 13); cout << "+ Vo Hoai An\t\t\t20120033";
	GotoXY(40, 14); cout << "+ Vuong Le Duc Binh \t\t20120043";
	GotoXY(40, 15); cout << "+ Tran Hoang Phuong Nam\t\t20120141";

	setTextColor(3);
	GotoXY(20, 17); cout << "Source Code: https://tinyurl.com/Team15KTLT";

	GotoXY(20, 19); cout << "Just use W, A, S, D to move and you'll figure it out how to play. Have fun!!!";
	setTextColor(7);
}

// draw a box start at (x, y) 
void drawBox(int x, int y, int width, int height) {
	setTextColor(3);
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
	setTextColor(7);
}

// draw Speed, score, level
void drawInfo() {
	setTextColor(6);
	GotoXY(12, HEIGHT_CONSOLE - 3); cout << "     ";
	GotoXY(12, HEIGHT_CONSOLE - 2); cout << "     ";
	GotoXY(12, HEIGHT_CONSOLE - 3); cout << speed;
	GotoXY(12, HEIGHT_CONSOLE - 2); cout << 150 * speed - step;
	setTextColor(7);
}

// draw game menu, how to play....
void drawGameMenu() {
	setTextColor(3);
	fillBox(1, HEIGHT_CONSOLE - 2, 50, 0, " ");
	GotoXY(5, HEIGHT_CONSOLE - 4); cout << "Player Name: " << player_name;
	GotoXY(5, HEIGHT_CONSOLE - 3); cout << "Level: " << speed;
	GotoXY(5, HEIGHT_CONSOLE - 2); cout << "Score: " << 150 * speed - step;

	for (int i = 2; i < INFO_SECTION_HEIGHT + 1; ++i) {
		GotoXY(40, HEIGHT_CONSOLE - i);
		cout << char(179);
		GotoXY(64, HEIGHT_CONSOLE - i);
		cout << char(179);
		GotoXY(86, HEIGHT_CONSOLE - i);
		cout << char(179);
	}

	GotoXY(41, HEIGHT_CONSOLE - 3); cout << " Move   " << char(16) << "   W, A, S, D ";
	
	GotoXY(65, HEIGHT_CONSOLE - 4); cout << " Pause Game    " << char(16) << "   P";
	GotoXY(65, HEIGHT_CONSOLE - 3); cout << " Resume Game   " << char(16) << "   R"; 
	GotoXY(65, HEIGHT_CONSOLE - 2); cout << " Save Game     " << char(16) << "   K";

	GotoXY(87, HEIGHT_CONSOLE - 3); cout << " Return to Main Menu   " << char(16) << "   Esc ";
	setTextColor(7);
}

//draw effect when player hit the car
void endGameMenu() {
	setTextColor(6);
	GotoXY(45, 2);  cout << "_";
	GotoXY(42, 3);  cout << "_ooOoo_";
	GotoXY(41, 4);  cout << "o8888888o";
	GotoXY(41, 5);  cout << "88\" . \"88";
	GotoXY(41, 6);  cout << "(| -_- |)";
	GotoXY(41, 7);  cout << "O\\  =  /O";
	GotoXY(38, 8);  cout << "____/`---'\\____";
	GotoXY(36, 9);  cout << ".'  \\\\|     |//  `.";
	GotoXY(35, 10); cout << "/  \\\\|||  :  |||//  \\";
	GotoXY(34, 11); cout << "/  _||||| -:- |||||_  \\";
	GotoXY(34, 12); cout << "|   | \\\\\\  -  /'| |   |";
	GotoXY(34, 13); cout << "| \\_|  `\\`---'//  |_/ |";
	GotoXY(34, 14); cout << "\\  .-\\__ `-. -'__/-.  /";
	GotoXY(32, 15); cout << "___`. .'  /--.--\\  `. .'___";
	GotoXY(29, 16); cout << ".\"\" '<  `.___\\_<|>_/___.' _> \\\"\".";
	GotoXY(28, 17); cout << "| | :  `- \\`. ;`. _/; .'/ /  .' ; |";
	GotoXY(28, 18); cout << "\\  \\ `-.   \\_\\_`. _.'_/_/  -' _.' /";
	GotoXY(13, 19); cout << "================`-.`___`-.__\\ \\___  /__.-'_.'_.-'================";
	GotoXY(42, 20); cout << "`=--=-'";

	GotoXY(9, 21); cout << " ___   __  ________   _______   _       _   _______    ___   __   _______";
	GotoXY(9, 22); cout << "|| \\\\  ||     ||     ||_____))  \\\\     //  ||_____||  || \\\\  ||  ||_____||";
	GotoXY(9, 23); cout << "||  \\\\_||  ___||___  ||     \\\\   \\\\___//   ||     ||  ||  \\\\_||  ||     ||";
	
	ghost_pos.y = HEIGHT_CONSOLE - 3;
	for(int i = 0; i < 5; ++i) {
		fillBox(1, ghost_pos.y + 1, WIDTH_CONSOLE - 2, 0, " ");
		for (int j = i; j >= 0; j--) {
			GotoXY(WIDTH_CONSOLE - i - ghost_width - 10, ghost_pos.y - j);
			setTextColor(6);
			cout << ghost_shape[i - j];
		}
		Sleep(150);
	}

	setTextColor(3);
	GotoXY(60, 4); cout << " You died in a car crash ";
	GotoXY(60, 5); cout << "because of your carelessness while crossing the street.";
	Sleep(500);
	GotoXY(60, 7); cout << " If you want me to revive you back to the path,";
	GotoXY(60, 8); cout << "press the \"R\" key.";
	GotoXY(60, 10); cout << " If you like to escape this world and come with me, ";
	GotoXY(60, 11); cout << "press any key you want.";
	Sleep(500);
	GotoXY(WIDTH_CONSOLE - 16, ghost_pos.y - 5); cout << "Your choice? ";
	state = 0;

	setTextColor(7);
}

// draw start menu in console (main thread)
void startMenu() {
	setTextColor(6);
	GotoXY(13, 5); cout << "OOOOOO   OOOOOO   OOOOOOO   OOOOOO   OOOOOO   OO  OO       OOOOOO   OOOOOOO   OOOOOOO   OOOOO";
	GotoXY(13, 6); cout << "OO       OO  OO   OO   OO   OO       OO       OO  OO       OO  OO   OO   OO   OO   OO   OO  OO";
	GotoXY(13, 7); cout << "OO       OO OO    OO   OO   OOOOOO   OOOOOO     OO    ===  OO OO    OO   OO   OOOOOOO   OO   OO";
	GotoXY(13, 8); cout << "OO       OO  OO   OO   OO       OO       OO     OO         OO  OO   OO   OO   OO   OO   OO  OO";
	GotoXY(13, 9); cout << "OOOOOO   OO   OO  OOOOOOO   OOOOOO   OOOOOO     OO         OO   OO  OOOOOOO   OO   OO   OOOOO";

	for (int i = 0; i <= 3; ++i)
		drawSelectBox(51, 12 + 3 * i, 16, 2);
	setTextColor(6);
	GotoXY(52, 13); cout << "New Game";
	GotoXY(65, 13); cout << "N";
	GotoXY(52, 16); cout << "Load Game";
	GotoXY(65, 16); cout << "L";
	GotoXY(52, 19); cout << "Exit";
	GotoXY(64, 19); cout << "Esc";
	GotoXY(52, 22); cout << "About";
	GotoXY(65, 22); cout << "O";
	setTextColor(7);
	GotoXY(0, 0);
}

