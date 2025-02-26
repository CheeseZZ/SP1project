// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "levels.h"
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
COORD player;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EMENU		g_eMenuState = S_NEW;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(90, 35, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = 2;
    g_sChar.m_cLocation.Y = 1;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_F1]     = isKeyPressed(VK_F1);
	g_abKeyPressed[K_Interact] = isKeyPressed('E');
	g_abKeyPressed[K_Inv] = isKeyPressed('I');
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
		case S_MENU: processUserInput(); // game logic for menu screen
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_PAUSE: processUserInput(); // game logic for pause screen
			break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
		case S_MENU: renderMenu();
			break;
        case S_GAME: renderGame();
            break;
		case S_PAUSE: renderPauseScreen();
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_MENU;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;
    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 1 && aCurrentLevel[player.Y - 1][player.X] == 0)
    {
        Beep(1440, 30);
        g_sChar.m_cLocation.Y -= 2;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 2 && aCurrentLevel[player.Y][player.X - 1] == 0)
    {
        Beep(1440, 30);
        g_sChar.m_cLocation.X -= 2;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < 19 && aCurrentLevel[player.Y + 1][player.X] == 0)
    {
        Beep(1440, 30);
        g_sChar.m_cLocation.Y += 2;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < 60 && aCurrentLevel[player.Y][player.X + 1] == 0)
    {
        Beep(1440, 30);
        g_sChar.m_cLocation.X += 2;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }
    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}
void processUserInput()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	// Changes menu state accordingly
	if (g_abKeyPressed[K_DOWN] && g_eGameState == S_MENU) // press down for continue game state
		g_eMenuState = S_CONTINUE;
	if (g_abKeyPressed[K_UP] && g_eGameState == S_MENU) // press up for New game state
		g_eMenuState = S_NEW;
	// Load or start new game according to state
	if (g_abKeyPressed[K_SPACE]) {
		switch (g_eMenuState) {
		case S_NEW: g_eGameState = S_GAME;
			break;
		case S_CONTINUE: loadFile();
			g_eGameState = S_GAME;
			break;
		}
	}
	// pauses/unpauses the game if player hits the F1 key
	if (g_abKeyPressed[K_F1] & g_eGameState == S_PAUSE)
		g_eGameState = S_GAME;
	else if (g_abKeyPressed[K_F1])
		g_eGameState = S_PAUSE;
    // quits the game if player hits the escape key
    else if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;
	
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.25; // 250ms should be enough
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
	renderStats();		// renders statistics to screen
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };
    COORD c;
	player.X = (g_sChar.m_cLocation.X / 2) - 1;
	player.Y = (g_sChar.m_cLocation.Y / 2);
	c.Y = 1;
	// Render frames for game, inventory, etc.
	for (int y = 0; y < 10; y++, c.Y+= 2) {
		c.X = 2;
		for (int x = 0; x < 30; x++, c.X+= 2) {
			if (((x == player.X) && (y == player.Y)) || ((x == player.X) && (y == player.Y - 1 || y == player.Y + 1)) || ((y == player.Y) && (x == player.X - 1 || x == player.X + 1)) || aLevelProgress[y][x]) {
				aLevelProgress[y][x] = 1;
				// for loop to scale map size by 2
				for (int i = 0; i < 4; i++) {
					// switch to ensure smooth scaling
					switch (i) {
					case 0:
						break;
					case 1:
						c.X++;
						break;
					case 2:
						c.Y++;
						break;
					case 3:
						c.X--;
						break;
					}
					switch (aCurrentLevel[y][x]) {
					case 0: // empty tile
						g_Console.writeToBuffer(c, " ", 0xFF);
						break;
					case 1: // wall
						g_Console.writeToBuffer(c, " ", 0x00);
						break;
					case 2: // enemy
						g_Console.writeToBuffer(c, " ", 0xE0);
						break;
					case 3: // chests
						g_Console.writeToBuffer(c, " ", 0xAA);
						break;
					case 4: // shop
						g_Console.writeToBuffer(c, " ", 0xBB);
						break;
					case 5: // final
						g_Console.writeToBuffer(c, " ", 0xD0);
						break;
					default:
						g_Console.writeToBuffer(c, " ", 0x00);
						break;
					}
				}
			}
			else
				continue;
			c.Y--;
		}
	}
	c.Y = 25;
	c.X = 2;
	g_Console.writeToBuffer(c, player.X, 0x0a);
	c.X = 4;
	g_Console.writeToBuffer(c, player.Y, 0x0a);
	c.Y = 26;
	c.X = 2;
	g_Console.writeToBuffer(c, aCurrentLevel[player.Y][player.X], 0x0a);
}

void renderCharacter()
{
	// value of character
	char charImage = 218;
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
	// loop to scale the character size by 2
	for (int i = 0;i < 4;i++) {
		switch (i) {
		case 0:
			break;
		case 1:
			g_sChar.m_cLocation.X++;
			charImage = 191;
			break;
		case 2:
			g_sChar.m_cLocation.Y++;
			charImage = 217;
			break;
		case 3:
			g_sChar.m_cLocation.X--;
			charImage = 192;
			break;
		}
		g_Console.writeToBuffer(g_sChar.m_cLocation, charImage, charColor);
	}
	g_sChar.m_cLocation.Y--;
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
void renderPauseScreen() // Renders pause screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 4;
	c.X = 6;
	g_Console.writeToBuffer(c, "Paused", 0x01);
	c.Y++;
	c.X = 4;
	g_Console.writeToBuffer(c, "Press F1 to contiue", 0x03);
}
void renderMenu() // Renders Menu
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 4;
	c.X = 6;
	g_Console.writeToBuffer(c, "Welcome to ", 0x0A);
	c.Y += 2;
	g_Console.writeToBuffer(c, "New Game", 0x0A);
	c.Y++;
	g_Console.writeToBuffer(c, "Continue", 0x0A);
	c.Y = 6 + g_eMenuState;
	c.X = 5;
	g_Console.writeToBuffer(c, ">", 0x0A);
}
void renderStats()
{	//display health
	COORD c;
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	int health = 3;
	ss.str("");
	ss << "Life: ";
	for (int i = 0;i<health;i++)
	{
		ss << (char)3;
	}
	c.X = 2;
	c.Y = 22;
	g_Console.writeToBuffer(c, ss.str(), 0x59);

	//display cash
	int money = 5;
	ss.str("");
	ss << "Cash: " << money;
	c.X = 2;
	c.Y = 23;
	g_Console.writeToBuffer(c, ss.str(), 0x59);

}