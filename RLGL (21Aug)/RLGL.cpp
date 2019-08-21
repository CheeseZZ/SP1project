#include <Windows.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "RLGL.h"
#include "game.h"

using namespace std;

int P2rand();
Lights Red, Yellow, Green;
Game2 RLGL;
ifstream MapLayout;
GMAP Floor;
CStopWatch tlimit;
SGameChar g_sChar;

void LoadLayout()
//one function to get the randomised ID from the randomiser and load in the map
{
	int Layout = P2rand();
	switch (Layout)
	{
	case 11:
		MapLayout.open("RLGL Layouts\\Floor1_1");
		break;
	case 12:
		MapLayout.open("RLGL Layouts\\Floor1_2");
		break;
	case 13:
		MapLayout.open("RLGL Layouts\\Floor1_3");
		break;
	case 14:
		MapLayout.open("RLGL Layouts\\Floor1_4");
		break;
	case 21:
		MapLayout.open("RLGL Layouts\\Floor2_1a");
		break;
	case 22:
		MapLayout.open("RLGL Layouts\\Floor2_1b");
		break;
	case 23:
		MapLayout.open("RLGL Layouts\\Floor2_2a");
		break;
	case 24:
		MapLayout.open("RLGL Layouts\\Floor2_2b");
		break;
	case 25:
		MapLayout.open("RLGL Layouts\\Floor2_3a");
		break;
	case 26:
		MapLayout.open("RLGL Layouts\\Floor2_3b");
		break;
	case 27:
		MapLayout.open("RLGL Layouts\\Floor2_4a");
		break;
	case 28:
		MapLayout.open("RLGL Layouts\\Floor2_4b");
		break;
	case 31:
		MapLayout.open("RLGL Layouts\\Floor3_1a");
		break;
	case 32:
		MapLayout.open("RLGL Layouts\\Floor3_1b");
		break;
	case 33:
		MapLayout.open("RLGL Layouts\\Floor3_2a");
		break;
	case 34:
		MapLayout.open("RLGL Layouts\\Floor3_2b");
		break;
	case 35:
		MapLayout.open("RLGL Layouts\\Floor3_3a");
		break;
	case 36:
		MapLayout.open("RLGL Layouts\\Floor3_3b");
		break;
	case 37:
		MapLayout.open("RLGL Layouts\\Floor3_4a");
		break;
	case 38:
		MapLayout.open("RLGL Layouts\\Floor3_4b");
		break;
	}

	if (MapLayout.is_open())
	{
		for (int y = 0; y < 35; y++)
		{
			getline(MapLayout, RLGL.line);
			RLGL.line += '\n';

			for (int x = 0; x < 90; x++)
			{
				int z = 0;
				RLGL.Layout[x][y] = RLGL.line[x];

				if (RLGL.line[x] = 'P')
					// locate the position of player spawn
				{
					g_sChar.m_cLocation.X = x;
					RLGL.start.x = x;

					g_sChar.m_cLocation.Y = y;
					RLGL.start.y = y;
				}

				for (z < 12; z++;)
					// locate the position of the lights
				{
					switch (RLGL.line[x])
					{
					case 'R':
						Red.position[z].x = x;
						Red.position[z].y = y;
						break;
					case 'Y':
						Yellow.position[z].x = x;
						Yellow.position[z].y = y;
						break;
					case 'G':
						Green.position[z].x = x;
						Green.position[z].y = y;
						break;
					}

				}
			}
		}
		MapLayout.close();
	}
}

void LightTiming()
//one function to randomise the timings on red light and green light
{

	switch (Floor)// the countdown for yellow light gets faster as the game progress to a new floor
	{
	case M_LEVEL1:
		Yellow.r_timing = YLight[0];
		break;
	case M_LEVEL2:
		Yellow.r_timing = YLight[1];
		break;
	case M_LEVEL3:
		Yellow.r_timing = YLight[2];
	}

	Red.r_timing = rand() % 5 + 3;
	Green.r_timing = rand() % 6 + 1;

}

void TimeLimit() // Sets a 30 second timer and time limits for Lights
{
	//Time limit for level
	RLGL.Timer = tlimit.getElapsedTime;
	RLGL.TimeLimit = 30.0f - RLGL.Timer;

	//Time limits for lights
	while (RLGL.Lives != 0 || RLGL.TimeLimit != 0)
	{
		Green.c_timing = tlimit.getElapsedTime;

		if (Green.c_timing >= Green.r_timing)
		{
			Yellow.c_timing = 0;
		}

		Yellow.c_timing = tlimit.getElapsedTime;

		if (Yellow.c_timing >= Yellow.r_timing)
		{
			Red.c_timing = 0;

			for (int y = 0; y < 35; y++)
			{
				for (int x = 0; x < 90; x++)
				{
					if (RLGL.Layout[x][y] == 'P')
					{
						RLGL.check.x = x;
						RLGL.check.y = y;
					}
				}
			}

		}

		Red.c_timing = tlimit.getElapsedTime;

		void MoveCondition();

		if (Red.c_timing >= Red.r_timing)
		{
			Green.c_timing = 0;
		}

	}
	
}

void MoveCondition()
{
	if (RLGL.Layout[RLGL.check.x][RLGL.check.y] != 'P' && Red.c_timing != Red.r_timing)
		// sets player back to starting location if they moved when the red light is active
	{
		RLGL.MoveRed = true;
		g_sChar.m_cLocation.X = RLGL.start.x;
		g_sChar.m_cLocation.Y = RLGL.start.y;
	}

	if (RLGL.Lives > 0 && RLGL.MoveRed == true)
		//deducts a life from the player if they have to restart their progress
	{
		RLGL.Lives -= 1;
		RLGL.MoveRed = false;

		if (RLGL.Lives == 0 || RLGL.TimeLimit == 0)
		{
			//lose condition met; exits the game and lose an actual life
		}
	}

}

