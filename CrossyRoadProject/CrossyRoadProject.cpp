#include "varsANDlibs.h"
#include "gameCommand.h"
#include "gameControl.h"
#include "gameMovement.h"
#include "consoleControl.h"
using namespace std;

int main() {
	int temp, interrupt = 0;
	FixConsoleWindow();
	thread t1(subThread);
	while (1) {
		startMenu();
		while (1) {
			temp = toupper(_getch()); // wait for input from user, make it capitalize
			if (temp == 'L') {
				resetData();
				GotoXY(0, PLAYGROUND_SECTION_HEIGHT + 2);
				printf("Enter your name to continue playing: ");
				while (1) {
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
				state = 1;
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
				drawAbout();
				_getch();
				system("cls");
				startMenu();
			}
			else {
				GotoXY(5, 25);
				cout << "It's not an option. Please choose again.";
			}
		}
		while (1) {
			if (interrupt == 1) {
				system("cls");
				interrupt = 0;
				break;
			}
			temp = toupper(_getch());
			if (state) {
				if (temp == 27) {
					state = 0;
					//eraseCars();
					//system("cls");
					//fillBox(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE, " ");
					//break;
					//continue;
					interrupt = 1;
				}
				else if (temp == 'P')
					pauseGame(t1.native_handle());
				else if (temp == 'R')
					resumeGame(t1.native_handle());
				else if (temp == 'K') {
					state = 0;
					fillBox(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE + 1, "*");
					fillBox(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE + 1, " ");
					if (player_name == DEFAULT_PLAYER_NAME) {
						GotoXY(50, 14);
						cout << "Enter your name : ";
						getline(cin, player_name);
					}
					else {
						GotoXY(50, 14);
						cout << "Enter your new name or press Enter to save to the file " << player_name << ".txt";
						string new_name;
						getline(cin, new_name);
						if (new_name != "")
							player_name = new_name;
					}
					saveGame(player_name, player_pos);
					GotoXY(50, 15);
					cout << "Your game have been saved to the file " << player_name << ".txt";
					continue;
				}
				else if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S') {
					resumeGame(t1.native_handle());
					direction = temp;
				}
			}
			else {
				//system("pause");
				// when player lose
				/*if (temp == 0 && interrupt == 1) {
					//cout << temp;
					//system("pause");
					eraseCars();
					system("cls");
					break;
				}*/
				if (temp == 'R') {
					startGame();
				}
				else {
					system("cls");
					break;
				}
			}
		}
	}
}
