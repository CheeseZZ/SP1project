#ifndef _PLAYER_STATS_
#define _PLAYER_STATS_

int options;
struct Inventory {
	bool Flash = false;
	bool Heart = false;
	bool Present = false;
	bool Battery = false;
	bool Trap = false;
};
struct Player {
	int health = 3;
	int money = 5;
	Inventory Inv;
};
#endif // !_PLAYER_STATS_