#include <iostream>
#include <conio.h>

using namespace std;
int Puzzle(int keyPressed);
void renderPuzzle();
void randomTileGenerator(bool newGame);

enum KEYS {
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT
}keystate;

int main(void) {
	randomTileGenerator(true);
	renderPuzzle();
	while (1) {
		int key = _getch();
		system("cls");
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72: // up key
				keystate = K_UP;
				break;
			case 80: //down key
				keystate = K_DOWN;
				break;
			case 75: // left key
				keystate = K_LEFT;
				break;
			case 77: // right key
				keystate = K_RIGHT;
				break;
			}
		}
		int gameResult = Puzzle(keystate);
		if (gameResult == 1) {
			system("cls");
			cout << "Congrats!\n";
		}
		else if (gameResult == 0) {

		}
	}

	system("pause");
	return 0;
}