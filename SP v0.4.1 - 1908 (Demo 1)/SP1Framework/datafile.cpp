#include <fstream>
#include <iostream>
#include "datafile.h"
#include "game.h"
#include <sstream>

void saveFile() {
	SGameChar Character;
	std::ifstream Datafile("save.sav");
	std::stringstream ss;
	ss << sLevel;
	Datafile.close();
}

void loadFile() {
	
}