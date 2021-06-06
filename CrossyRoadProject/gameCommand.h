#pragma once
#include "varsANDlibs.h"
#include "consoleControl.h"
#include "gameControl.h"
using namespace std;

// start a new Game
void startGame() {
	system("cls");
	resetData();
	drawGameMenu();
	drawBox(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
	drawBox(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
	state = 1;
}

// kill thread then clear memory and exit
void exitGame(HANDLE t) {
	system("cls"); 
	TerminateThread(t, 0);
	deleteCarData();
	exit(1);
}

// pause thread -> pause game
void pauseGame(HANDLE t) {
	SuspendThread(t);
}

// resume thrad -> game continue
void resumeGame(HANDLE t) {
	ResumeThread(t); 
}

// save game to player_name.txt file, if file already exist, clear it first
void saveGame(string player_name, POINT player_pos) {
	string fileName = player_name + ".txt";
	fstream fileOutput;
	fileOutput.open(fileName, ios::out | ios::trunc); // erase exist data
	fileOutput << speed << "\n" << step << "\n";
	for (int i = 0; i < MAX_CAR; i++) {
		fileOutput << carInfo[i].length << "\n" << carInfo[i].direction << "\n";
		for (int j = 0; j < carInfo[i].length; j++)
			fileOutput << carArray[i][j] << "\n";
	}
	for (int i = 0; i < speed; ++i) {
		fileOutput << prevPos[i] << "\n";
	}
	fileOutput << player_pos.x << "\n" << player_pos.y;
	fileOutput.close();
}

// load game from player_name.txt file
void loadGame(string player_name, POINT &player_pos) {
	system("cls");
	drawBox(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
	drawBox(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
	string fileName = player_name + ".txt";
	fstream fileInput(fileName);
	fileInput >> speed >> step;
	for (int i = 0; i < MAX_CAR; i++) {
		fileInput >> carInfo[i].length >> carInfo[i].direction;
		carArray[i] = new int[carInfo[i].length];
		for (int j = 0; j < carInfo[i].length; j++)
			fileInput >> carArray[i][j];
	}
	setTextColor(6);
	for (int i = 0; i < speed; ++i) {
		fileInput >> prevPos[i];
		drawCharacter({ prevPos[i], 2 }, "Y");

		//cout << "Y";
	}
	fileInput >> player_pos.x >> player_pos.y;
	fileInput.close();
	drawCharacter(player_pos, "Y");
	drawCars();
	drawInfo();
	drawGameMenu();
	drawBox(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
	drawBox(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
}