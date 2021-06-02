#include "varsANDlibs.h"
#include "gameCommand.h"
#include "gameControl.h"
#include "gameMovement.h"
#include "consoleControl.h"
using namespace std;

int main() {
	int temp;
	FixConsoleWindow();
	srand((unsigned)time(NULL));
	thread t1(subThread);
	startMenu();

	while (1) {
		temp = toupper(_getch()); // wait for input from user, make it capitalize
		if (temp == 'L') {
			resetData();
			pauseGame(t1.native_handle());
			GotoXY(0, PLAYGROUND_SECTION_HEIGHT + 2);
			printf("Enter your name to continue playing: ");
			while(1) {
				getline(cin, player_name);
				// check if file exist or not, if not, ask again
				if (!isFileExist(player_name)) {
					fillBox(0, PLAYGROUND_SECTION_HEIGHT + 2, WIDTH_CONSOLE, 0, " ");
					GotoXY(0, PLAYGROUND_SECTION_HEIGHT + 2);
					cout << "Can't find " << player_name << "'s data. Please re-enter: ";
				}
				else
					break;
			}
			loadGame(player_name, player_pos);
			state = true;
			break;
		}
		else if (temp == 'N') {
			startGame();
			break;
		}
		else if (temp == 27) {
			exitGame(t1.native_handle());
			return 0;
		}
		else if (temp == 'O') {
			system("cls");
		}
		else {
			GotoXY(5, 25);
			cout << "It's not an option. Please choose again.";
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
				// if game is pausing, resume it
				//	or if game is running, pause it
			 	if(pausing == false)
					pauseGame(t1.native_handle());
				else
					resumeGame(t1.native_handle());
			}
			else if (temp == 'K') {
				/*
					Do not use SuspendThread, or pauseGame at this place.
					Because if we do that, thread t1 will stop, and it don't allow
				us to enter player name.
					Solution: use variable "pausing = true" to make sure computer understand
				that game is pausing (theoretically), so it will stop print new car and player position
				in thread without SuspendThread, then we could enter player name.
					Disadvandtage: since we use variable to stop print new car position, some magic way,
				it keep print some mesh, so we have to clear console with " ". It partially affects the aesthetic
				*/
				pausing = !pausing;
				fillBox(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE + 1, "*");
				fillBox(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE + 1, " ");
				if (player_name == DEFAULT_PLAYER_NAME) {
					GotoXY(50, 14);
					cout << "Enter your name : ";
					getline(cin, player_name);
				}
				else {

				}
				saveGame(player_name, player_pos);
				exitGame(t1.native_handle());
			}
			else {
				if (pausing == true)
					resumeGame(t1.native_handle());
				if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')
					direction = temp;
			}

		}
		else {
			// when player lose
			if (temp == 'R') {
				startGame();
			}
			else {
				exitGame(t1.native_handle());
				return 0;
			}
		}
	}
}
