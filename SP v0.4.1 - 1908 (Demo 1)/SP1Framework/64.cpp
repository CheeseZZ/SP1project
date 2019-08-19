#include <iostream>
#include <ctime>
#include <Windows.h>
#include "64.h"
#include "game.h"

// Logic for puzzle 
// *combination of adjacent, identical tile when key is pressed
// input  = Key pressed
// output = Void
int Puzzle64(int keyPressed, int PuzzleMap[4][4]) {
	switch (keyPressed) {
	case 0: // up
		// checks each tile
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				updatePuzzle(0, PuzzleMap);
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
				updatePuzzle(1, PuzzleMap);
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
				updatePuzzle(2, PuzzleMap);
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
				updatePuzzle(3, PuzzleMap);
				// checks if tile to the right of current tile is identical, if so, merge
				if (PuzzleMap[y][x] == PuzzleMap[y][x - 1] && PuzzleMap[y][x] != 0) {
					PuzzleMap[y][x]++;
					PuzzleMap[y][x - 1] = 0;
				}
			}
		}
		break;
	}
	randomTileGenerator(false, PuzzleMap);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (PuzzleMap[y][x] == 7)
				return 1;
		}
	}
	if (mapFull) {
		PuzzleMap;
		return -1;
	}
	else
		return 0;
}

// function to update the puzzle state i.e. move all tiles to wall dependant on key press.
// input  = Key Pressed
// output = Void
void updatePuzzle(int keyPressed, int PuzzleMap[4][4]) {
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
void randomTileGenerator(bool newGame, int PuzzleMap[4][4]) {
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
		int highestvalue = 1;
		int tilevalue = 0;
		COORD newTile;
		// to find current highest value on board
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (PuzzleMap[y][x] >= highestvalue)
					highestvalue = PuzzleMap[y][x];
			}
		}
		int y = 0;
		int x = 0;
		do {
			mapFull = false;
			if (PuzzleMap[y][x] != 0) {
				mapFull = true;
			}
			y++; x++;
		} while (mapFull && y < 4 && x < 4);
		if (!mapFull) { // if map is full, dont replace
			// find vacant tile to input a tile value
			do {
				newTile.X = rand() % 4;
				newTile.Y = rand() % 4;
			} while (PuzzleMap[newTile.Y][newTile.X] != 0);
			tilevalue = rand() % highestvalue + 1;
			if (tilevalue == highestvalue)
				tilevalue--;
			PuzzleMap[newTile.Y][newTile.X] = tilevalue;
		}
	}
}