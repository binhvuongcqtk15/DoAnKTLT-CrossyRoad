#pragma once
#include "varsANDlibs.h"
#include "gameControl.h"
using namespace std;

void moveRight() {
	step++;
	if (player.x < WIDTH_CONSOLE - 1) {
		drawCharacter(player, " ");
		player.x++;
		drawCharacter(player, "Y");
	}
}
void moveLeft() {
	if (player.x > 1) {
		step++;
		drawCharacter(player, " ");
		player.x--;
		drawCharacter(player, "Y");
	}
}
void moveDown() {
	if (player.y < PLAYGROUND_SECTION_HEIGHT - 1) {
		step++;
		drawCharacter(player, " ");
		player.y++;
		drawCharacter(player, "Y");
	}
}
void moveUp() {
	if (player.y > 1) {
		step++;
		drawCharacter(player, " ");
		player.y--;
		drawCharacter(player, "Y");
	}
}