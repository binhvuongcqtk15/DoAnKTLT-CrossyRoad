#pragma once
#include "varsANDlibs.h"
#include "gameControl.h"
using namespace std;

void moveRight() {
	step++;
	if (player_pos.x < WIDTH_CONSOLE - 1) {
		drawCharacter(player_pos, " ");
		player_pos.x++;
		drawCharacter(player_pos, "Y");
	}
}
void moveLeft() {
	if (player_pos.x > 1) {
		step++;
		drawCharacter(player_pos, " ");
		player_pos.x--;
		drawCharacter(player_pos, "Y");
	}
}
void moveDown() {
	if (player_pos.y < PLAYGROUND_SECTION_HEIGHT - 1) {
		step++;
		drawCharacter(player_pos, " ");
		player_pos.y++;
		drawCharacter(player_pos, "Y");
	}
}
void moveUp() {
	if (player_pos.y > 1) {
		step++;
		drawCharacter(player_pos, " ");
		player_pos.y--;
		drawCharacter(player_pos, "Y");
	}
}