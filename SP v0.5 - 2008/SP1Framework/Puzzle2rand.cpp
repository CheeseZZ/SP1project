#include <ctime>
#include <iostream>

using namespace std;

int floors;
int randchoice;
int RLGLpuzzleID = 10;

int RLGLrand()
{
	srand(time(0));

	switch (floors)
	{
	case 1:
		RLGLpuzzleID *= 1;
		break;
	case 2:
		RLGLpuzzleID *= 2;
		break;
	case 3:
		RLGLpuzzleID *= 3;
		break;
	}

	if (floors == 1)
	{
		randchoice = rand() % 4 + 1;
		RLGLpuzzleID += randchoice;
	}

	if (floors == 2 || floors == 3)
	{
		randchoice = rand() % 8 + 1;
		RLGLpuzzleID += randchoice;
	}

	cout << "Your level ID is " << RLGLpuzzleID << endl;
	return 0;
}