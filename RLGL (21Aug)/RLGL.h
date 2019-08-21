#ifndef _RLGL_PUZZLE_H_
#define _RLGL_PUZZLE_H_

double YLight[3] = { 2.0, 1.50, 1.0 };


struct Location
{
	int x;
	int y;
};

struct Game2
{
	std::string line;
	char Layout[90][35] = { ' ' , };
	double TimeLimit, Timer;
	int Lives;
	bool Win = false;
	bool MoveRed = false;
	Location start, check, win;
};

struct Lights
{
	double r_timing, c_timing; // random, current
	Location position[12];
};

#endif