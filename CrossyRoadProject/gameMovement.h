#pragma once
#include "varsANDlibs.h"
#include "gameControl.h"
using namespace std;

void moveRight() {
	step++;
	drawCharacter(player_pos, " ");
	if (player_pos.x > WIDTH_CONSOLE - 2)
		player_pos.x = 0;
	player_pos.x++;
	drawCharacter(player_pos, "Y");
}
void moveLeft() {
	step++;
	drawCharacter(player_pos, " ");
	if (player_pos.x < 2)
		player_pos.x = WIDTH_CONSOLE;
	player_pos.x--;
	drawCharacter(player_pos, "Y");
}
void moveDown() {
	if (player_pos.y < PLAYGROUND_SECTION_HEIGHT) {
		step++;
		drawCharacter(player_pos, " ");
		player_pos.y++;
		drawCharacter(player_pos, "Y");
	}
}
void moveUp() {
	if (player_pos.y > 2) {
		step++;
		drawCharacter(player_pos, " ");
		player_pos.y--;
		drawCharacter(player_pos, "Y");
	}
}