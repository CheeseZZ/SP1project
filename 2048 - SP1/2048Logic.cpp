#include <iostream>
#include <ctime>
#include <Windows.h>
// Mapping for puzzle
// 0 = empty tile (for updating purposes)
// 1 = vacant tile
// 2 = tile 1(2)
// 3 = tile 2(4)
// 4 = tile 3(8)
// 5 = tile 4(16)
// 6 = tile 5(32)
// 7 = tile 6(64)

int PuzzleMap[4][4] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
};
bool mapFull = false;

void renderPuzzle();					// Renders puzzle to screen
void updatePuzzle(int keyPressed);		// updates tile coordinates 
void randomTileGenerator(bool newGame); // generates new tiles

// Logic for puzzle 
// *combination of adjacent, identical tile when key is pressed
// input  = Key pressed
// output = Void
int Puzzle(int keyPressed) {
	switch (keyPressed) {
	case 0: // up
		// checks each tile
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				updatePuzzle(0);
				// checks if tile below current tile is identical, if so merge.
				if (PuzzleMap[y][x] == PuzzleMap[y + 1][x] && PuzzleMap[y][x] != 0) {
					PuzzleMap[y][x]++;
					PuzzleMap[y + 1][x] = 0;
				}
			}
		}
		break;
	case 1: // down
		// checks each tile
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				updatePuzzle(1);
				// checks if tile above current tile is identical, if so merge
				if (PuzzleMap[y][x] == PuzzleMap[y - 1][x] && PuzzleMap[y][x] != 0) {
					PuzzleMap[y][x]++;
					PuzzleMap[y - 1][x] = 0;
				}
			}
		}
		break;
	case 2: // left
		// checks each tile
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				updatePuzzle(2);
				// checks if tile to the left of current tile is identical, if so, merge
				if (PuzzleMap[y][x] == PuzzleMap[y][x + 1] && PuzzleMap[y][x] != 0) {
					PuzzleMap[y][x]++;
					PuzzleMap[y][x + 1] = 0;
				}
			}
		}
		break;
	case 3: // right
		// checks each tile
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				updatePuzzle(3);
				// checks if tile to the right of current tile is identical, if so, merge
				if (PuzzleMap[y][x] == PuzzleMap[y][x - 1] && PuzzleMap[y][x] != 0) {
					PuzzleMap[y][x]++;
					PuzzleMap[y][x - 1] = 0;
				}
			}
		}
		break;
	}
	randomTileGenerator(false);
	renderPuzzle();
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (PuzzleMap[y][x] == 7)
				return 1;
		}
	}
	if (mapFull)
		return -1;
	else
		return 0;
}

void renderPuzzle() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			std::cout << PuzzleMap[y][x];
		}
		std::cout << std::endl;
	}
	return;
}

// function to update the puzzle state i.e. move all tiles to wall dependant on key press.
// input  = Key Pressed
// output = Void
void updatePuzzle(int keyPressed) {
	switch (keyPressed) {
	case 0:
		// all tiles below move up once until blocked
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 4; x++) {
				if (PuzzleMap[y][x] == 0 && PuzzleMap[y + 1][x] != 0) {
					PuzzleMap[y][x] = PuzzleMap[y + 1][x];
					PuzzleMap[y + 1][x] = 0;
				}
			}
		}
		break;
	case 1:
		// all tiles above move down once until blocked
		for (int y = 3; y > 0; y--) {
			for (int x = 0; x < 4; x++) {
				if (PuzzleMap[y][x] == 0 && PuzzleMap[y - 1][x] != 0) {
					PuzzleMap[y][x] = PuzzleMap[y - 1][x];
					PuzzleMap[y - 1][x] = 0;
				}
			}
		}
		break;
	case 2:
		// all tiles to the right move left until blocked. 
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 4; y++) {
				if (PuzzleMap[y][x] == 0 && PuzzleMap[y][x + 1] != 0) {
					PuzzleMap[y][x] = PuzzleMap[y][x + 1];
					PuzzleMap[y][x + 1] = 0;
				}
			}
		}
		break;
	case 3:
		// all tiles to the left move right until blocked.
		for (int x = 3; x > 0; x--) {
			for (int y = 0; y < 4; y++) {
				if (PuzzleMap[y][x] == 0 && PuzzleMap[y][x - 1] != 0) {
					PuzzleMap[y][x] = PuzzleMap[y][x - 1];
					PuzzleMap[y][x - 1] = 0;
				}
			}
		}
		break;
	}
}
void randomTileGenerator(bool newGame) {
	srand(time(0)); // use time as seed for random number generator
	// upon new game, randomly set two tiles with the smallest value
	if (newGame) {
		COORD tile1, tile2;
		// to randomize location of first tile
		tile1.X = rand() % 4;
		tile1.Y = rand() % 4;
		// randomize the location of second tile with relevance to tile 1 allowing one movement clear.
		do {
			switch (rand() % 2) {
			case 0:
				tile2.X = tile1.X;
				tile2.Y = rand() % 4;
				break;
			case 1:
				tile2.Y = tile1.Y;
				tile2.X = rand() % 4;
				break;
			}
		} while (tile1.X == tile2.X && tile1.Y == tile2.Y);
		PuzzleMap[tile1.Y][tile1.X] = 1;
		PuzzleMap[tile2.Y][tile2.X] = 1;
	}
	else {
		int highestvalue = 0;
		int tilevalue = 0;
		COORD newTile;
		// to find current highest value on board
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (PuzzleMap[y][x] >= highestvalue)
					highestvalue = PuzzleMap[y][x];
				if (PuzzleMap[y][x]) 
					mapFull = true;
				else 
					mapFull = false;
			}
		}
		if (!mapFull) { // if map is full, dont replace
			// find vacant tile to input a tile value
			do {
				newTile.X = rand() % 4;
				newTile.Y = rand() % 4;
			} while (PuzzleMap[newTile.Y][newTile.X] != 0);
			tilevalue = rand() % highestvalue + 1;
			PuzzleMap[newTile.Y][newTile.X] = tilevalue;
		}
	}
}