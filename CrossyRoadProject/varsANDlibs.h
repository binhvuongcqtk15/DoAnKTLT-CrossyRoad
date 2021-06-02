// variables and libraries
#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <conio.h>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_CAR = 21; // number of car in console, each car in one line
const int MIN_CAR_LENGTH = 20; // min length of a car
const int MAX_CAR_LENGTH = 50; // max length of a car
const int MAX_SPEED = 3; // max speed of a car, also max level can access

//Console parameter
const int PLAYGROUND_SECTION_HEIGHT = 24, INFO_SECTION_HEIGHT = 4;
const int WIDTH_CONSOLE = 118, HEIGHT_CONSOLE = 30;

const POINT DEFAULT_CHARACTER_POS = { 58,24 }; // default player position
const string DEFAULT_PLAYER_NAME = "Anonymous"; // default player name

// This contain car infomation about its length and direction (go left or right)
struct CAR {
	int direction;
	int length;
};

// create a 1D dynamic array of car infomation
// each element is a variable type CAR
CAR* carInfo;
// create a 2D dynamic array of car
// element [i][j] = x show that car in line i, j-th car segment located at a 
int** carArray;

POINT player_pos; // show where is player's current position
int speedUP = 0; // use to speed up car
int direction, speed, step; //direction = W, A, S, D; speed = level = 1, 2, 3;
bool state; // Dead = 0, Alive = 1;
bool pausing = false; // true: game is pausing, false: game is running
int prevPos[5]; // player position in previous level
string player_name; // player name

//End game effect
POINT ghost_pos;
int ghost_height = 5, ghost_width = 7;
string ghost_shape[5] = { " .-.   " , "(o o)  " , "| O \\  ", " \\   \\ " , "  `~~~'" };
/*
	console be like: 
	(0, 0)--------------------> x
		 |
		 |
		 |
		 |
		 |
		 |
		 |
		 v
		 y
*/

