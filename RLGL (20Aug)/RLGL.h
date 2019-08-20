#ifndef _RLGL_PUZZLE_H_
#define _RLGL_PUZZLE_H_

float YLight[3] = { 2.0f, 1.50f, 1.0f };


struct Game2
{
	std::string line;
	char Layout[90][35] = { ' ' , };
	float TimeLimit, Timer;
	int Lives;
	bool Win = false;
	bool MoveRed = false;
	Location start, check, win;
};

struct Location
{
	int x;
	int y;
};

struct Lights
{
	float r_timing, c_timing; // random, current
	Location position[12];
};

#endif