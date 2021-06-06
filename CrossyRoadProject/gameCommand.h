#pragma once
#include "varsANDlibs.h"
#include "consoleControl.h"
#include "gameControl.h"
using namespace std;

// erase memory in hard drive
void deleteCarData() {
	if (carArray == NULL || carInfo == NULL)
		return;
	for (int i = 0; i < MAX_CAR; i++)
		delete[] carArray[i];
	delete[] carArray;
	delete[] carInfo;
}

// check if file exist or not
bool isFileExist(string fileName) {
	fstream fileInput(fileName + ".txt");
	return fileInput.good();
}

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
	if (speed != 1)
		fileOutput << prevPos[speed - 1] << "\n";
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
	if (speed != 1) {
		fileInput >> prevPos[speed - 1];
		GotoXY(prevPos[speed - 1], 2);
		cout << "Y";
	}
	fileInput >> player_pos.x >> player_pos.y;
	fileInput.close();
	drawCars("=");
	drawCharacter(player_pos, "Y");
	drawInfo();
	drawGameMenu();
	drawBox(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
	drawBox(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);

}