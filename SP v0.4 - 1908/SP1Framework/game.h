#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
	K_F1,
	K_INT,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
	S_MENU,
	S_SUBMENU,
    S_GAME,
    S_COUNT,
	S_PAUSE,
	S_SHOP,
	S_PUZZLE,
	S_TESTING
};

// Enumeration for different Menu choices
enum EMENU
{
	S_NEW,
	S_CONTINUE
};

// Enumeration for different levels
enum GMAP
{
	M_LEVEL1,
	M_LEVEL2,
	M_LEVEL3
};

// Enumeration for different Puzzles
enum GPUZZLES
{	
	P_EMPTY,
	P_TRIAL_N_ERROR,
	P_64,
	P_RED_LIGHT_GREEN_LIGHT,
	P_RIDDLES
};
// Enumeration for Shop Items
enum items
{
	Flash,
	Heart,
	Present,
	Battery,
	Compass,
	Radar,
	Trap,
	Exit
};
// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};
struct moveChar
{
	COORD m_cLocation2;
	bool m_bActive2;
};


void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderPauseScreen();	// renders the pause screen
void renderShop();			//render the Shop screen
void renderMenu();			// renders the pre-game Menu
void renderstats();			// renders player statistics
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void saveFile();			// saves game into savefile
void loadFile();			// loads savefile into game.
void moveSelectors();		// Moves Selector during Shop interface / specific puzzles

// Puzzles functions 
void puzzleRandomize();		// Randomizes puzzles

// Trial and error puzzle
void movepuzzle0();
void movePuzzle0();
void puzzle0();				//renders the puzzle1

// 64 (2048-style) puzzle
int Puzzle64(int keyPressed, int PuzzleMap[4][4]);			// main logic function for puzzle 64
void renderPuzzle1();					// Renders puzzle to screen
void updatePuzzle(int keyPressed, int PuzzleMap[4][4]);		// updates tile coordinates 
void randomTileGenerator(bool newGame, int PuzzleMap[4][4]); // generates new tiles
void puzzle1Move();						// detects key presses and updates puzzle
void Puzzle1Reset();					// Resets puzzle

#endif // _GAME_H