// variables and libraries
#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <conio.h>

using namespace std;

const int  MAX_CAR = 17;
const int  MAX_CAR_LENGTH = 40;
const int  MAX_SPEED = 3;
const int PLAYGROUND_SECTION_HEIGHT = 24, INFO_SECTION_HEIGHT = 4;
const int WIDTH_CONSOLE = 118;
const POINT DEFAULT_CHARACTER_POS = { 59,23 };

POINT** carArray;
POINT player;
int cnt = 0;
int direction, speed; //direction = W, A, S, D; speed = level = 1, 2, 3;
bool state; // Dead = 0, Alive = 1;
int currpos[2];
char player_name[20];
