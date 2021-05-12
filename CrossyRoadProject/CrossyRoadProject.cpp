#include "varsANDlibs.h"
#include "gameCommand.h"
#include "gameControl.h"
#include "gameMovement.h"
#include "consoleControl.h"
using namespace std;

int main() {
	int temp;
	FixConsoleWindow();
	srand(time(NULL));
	thread t1(subThread);
	startMenu();
	temp=toupper(_getch());
	while (1) {
		if (temp == 'L') {
			resetData();
			pauseGame(t1.native_handle());
			GotoXY(0, PLAYGROUND_SECTION_HEIGHT + 2);
			printf("Type name: ");
			getline(cin, player_name);
			loadGame(player_name, player_pos);
			state = true;
			break;
		}
		else if (temp == 'N') {
			startGame();
			break;
		}
		else if (temp == 27)
			exit(1);
		else if (temp == 'O') {

		}
		else {
			clearBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
			break;
		}
	}

	while (1) {
		temp = toupper(_getch());
		if (state) {
			if (temp == 27) {
				exitGame(t1.native_handle());
				return 0;
			}
			else if (temp == 'P') {
			 	pauseGame(t1.native_handle());
			}
			else if (temp == 'K') {
				pauseGame(t1.native_handle());
				if (player_name == DEFAULT_PLAYER_NAME) {
					clearBoard(1, PLAYGROUND_SECTION_HEIGHT + 2, WIDTH_CONSOLE - 2, INFO_SECTION_HEIGHT - 2);
					GotoXY(54, PLAYGROUND_SECTION_HEIGHT + 3);
					printf("Type name: ");
					getline(cin, player_name);
				}
				saveGame(player_name, player_pos);
				exitGame(t1.native_handle());
			}
			else {
				ResumeThread((HANDLE)t1.native_handle());
				if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')
					direction = temp;
			}
		}
		else {
			if (temp == 'R') startGame();
			else {
				exitGame(t1.native_handle());
				return 0;
			}
		}
	}
}
