#include "Framework\timer.h"
#include "Framework\console.h"
CStopWatch Time;
Console g_console(80,25,"xd");
int treasureChests(COORD c)
{
	srand(Time.getElapsedTime());
	int Randnum = rand() % 4 + 1;
		char output;
		switch (Randnum) {
		case 1: output = '1';
			break;
		case 2: output = '2';
			break;
		case 3: output = '3';
			break;
		case 4: output = '4';
			break;
		}
		g_console.writeToBuffer(c, output, 0x03);
	return Randnum;
}