#include "varsANDlibs.h"
#include "gameCommand.h"
#include "gameControl.h"
#include "gameMovement.h"
#include "consoleControl.h"
using namespace std;

int main() {
	int temp;
	FixConsoleWindow();
	thread t1(subThread);
	while (1) {
		system("cls");
		startMenu();
		while (1) {
			temp = toupper(_getch()); // wait for input from user, make it capitalize
			if (temp == 'L') {
				resetData();
				fillBox(0, PLAYGROUND_SECTION_HEIGHT + 2, WIDTH_CONSOLE, 0, " ");
				GotoXY(5, PLAYGROUND_SECTION_HEIGHT + 2);
				setTextColor(3);
				cout << "Enter your name to continue playing: ";
				while (1) {
					setTextColor(6);
					getline(cin, player_name);
					// check if file exist or not, if not, ask again
					if (!isFileExist(player_name)) {
						fillBox(0, PLAYGROUND_SECTION_HEIGHT + 2, WIDTH_CONSOLE, 0, " ");
						GotoXY(5, PLAYGROUND_SECTION_HEIGHT + 2);
						setTextColor(3);
						cout << "Can't find ";
						setTextColor(6);
						cout << player_name << "'s";

						setTextColor(3);
						cout << " data.Please re-enter: ";
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
				temp = _getch();
				system("cls");
				startMenu();
			}
			else {
				GotoXY(5, PLAYGROUND_SECTION_HEIGHT + 2); setTextColor(6);
				cout << "It's not an option. Please choose again.";
			}
		}
		while (1) {
			temp = toupper(_getch());
			if (state) {
				if (temp == 27) {
					state = 0; // Another way to pause game
					Sleep(40); //Create a gap time for subThread to update "state" status to 0
					break;
				}
				else if (temp == 'P')
					pauseGame(t1.native_handle());
				else if (temp == 'R')
					resumeGame(t1.native_handle());
				else if (temp == 'K') {
					state = 0; // Another way to pause game
					Sleep(60); //Create a gap time for subThread to update "state" status to 0
					system("cls");
					if (player_name == DEFAULT_PLAYER_NAME) {
						GotoXY(35, 12);
						setTextColor(3);
						cout << "Enter your name : ";
						setTextColor(6);
						getline(cin, player_name);
					}
					else {
						GotoXY(28, 12);
						setTextColor(3);
						cout << "Enter your new name or press Enter to save to the file ";
						setTextColor(6);
						cout << player_name << ".txt";
						string new_name;
						setTextColor(3);
						cout << ": ";
						setTextColor(6);
						getline(cin, new_name);
						if (new_name != "")
							player_name = new_name;
					}
					saveGame(player_name, player_pos);
					GotoXY(35, 13);
					setTextColor(3);
					cout << "Your game have been saved to the file ";
					setTextColor(6);
					cout << player_name << ".txt";
					setTextColor(7);
					break;
				}
				else if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S') {
					resumeGame(t1.native_handle());
					direction = temp;
				}
				else
					continue;
			}
			else {
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
