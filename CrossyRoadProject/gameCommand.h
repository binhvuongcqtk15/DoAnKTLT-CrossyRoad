#pragma once
#include "varsANDlibs.h"
#include "consoleControl.h"
#include "gameControl.h"
using namespace std;

void deleteCarArray() {
	for (int i = 0; i < MAX_CAR; i++)
		delete[] carArray[i];
	delete[] carArray;
	delete[] carInfo;
}

bool isFileExist(string fileName) {
	fstream fileInput(fileName + ".txt");
	return fileInput.good();
}

void startGame() {
	system("cls");
	resetData();
	drawPlayGround(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
	drawPlayGround(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
	state = true;
}

void exitGame(HANDLE t) {
	system("cls"); 
	TerminateThread(t, 0);
	deleteCarArray();
	exit(1);
}

void pauseGame(HANDLE t) {
	SuspendThread(t);
}

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
void loadGame(string player_name, POINT &player_pos) {
	system("cls");
	drawPlayGround(0, 0, WIDTH_CONSOLE, PLAYGROUND_SECTION_HEIGHT);
	drawPlayGround(0, PLAYGROUND_SECTION_HEIGHT + 1, WIDTH_CONSOLE, INFO_SECTION_HEIGHT);
	string fileName = player_name + ".txt";
	fstream fileInput(fileName);
	fileInput >> speed >> step;
	for (int i = 0; i < MAX_CAR; i++) {
		fileInput >> carInfo[i].length >> carInfo[i].direction;
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
	//system("pause");
	drawCars("=");
	drawCharacter(player_pos, "Y");
	drawInfo();
}