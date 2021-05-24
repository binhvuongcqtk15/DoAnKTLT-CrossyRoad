// variables and libraries
#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <conio.h>
#include <string>
using namespace std;

const int MAX_CAR = 21;
const int MIN_CAR_LENGTH = 20;
const int MAX_CAR_LENGTH = 50;
const int MAX_SPEED = 3;
const int PLAYGROUND_SECTION_HEIGHT = 24, INFO_SECTION_HEIGHT = 4;
const int WIDTH_CONSOLE = 118, HEIGHT_CONSOLE = 28;
const POINT DEFAULT_CHARACTER_POS = { 58,24 };
const string DEFAULT_PLAYER_NAME = "Anonymous";

struct CAR {
	int direction;
	int length;
};

CAR* carInfo;
int** carArray;
POINT player_pos;
int speedUP = 0;
int direction, speed, step; //direction = W, A, S, D; speed = level = 1, 2, 3;
bool state; // Dead = 0, Alive = 1;
int prevPos[5];
string player_name;

