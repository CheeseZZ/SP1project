#include "game.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream inFile;
string line;
string MapLayout1[30][10];

void MapLayout()
{
	
	inFile.open("Map Layouts\\MapLayoutLv1.txt");

	if (!inFile)
	{
		cout << "File Error" << endl;
	}

	if (inFile.is_open())
	{
		for (int y = 0; y < 10; y++)
		{
			getline(inFile, line);
			line += '\n';

			for (int x = 0; x < 30; x++)
			{
				MapLayout1[x][y] = line[x];
			}

		}

		inFile.close();

		for (int x = 0; x < 10; x++)
		{

			for (int y = 0; y < 30; y++)
			{

				cout << MapLayout1[y][x];

			}

			cout << endl;
		}

	}

	cout << endl;

	inFile.open("Map Layouts\\MapLayoutLv2.txt");

	if (!inFile)
	{
		cout << "File Error" << endl;
	}

	if (inFile.is_open())
	{
		for (int y = 0; y < 10; y++)
		{
			getline(inFile, line);
			line += '\n';

			for (int x = 0; x < 30; x++)
			{
				MapLayout1[x][y] = line[x];
			}

		}

		inFile.close();

		for (int x = 0; x < 10; x++)
		{

			for (int y = 0; y < 30; y++)
			{

				cout << MapLayout1[y][x];

			}

			cout << endl;
		}

	}

	cout << endl;

	inFile.open("Map Layouts\\MapLayoutLv3.txt");

	if (!inFile)
	{
		cout << "File Error" << endl;
	}

	if (inFile.is_open())
	{
		for (int y = 0; y < 10; y++)
		{
			getline(inFile, line);
			line += '\n';

			for (int x = 0; x < 30; x++)
			{
				MapLayout1[x][y] = line[x];
			}

		}

		inFile.close();

		for (int x = 0; x < 10; x++)
		{

			for (int y = 0; y < 30; y++)
			{

				cout << MapLayout1[y][x];

			}

			cout << endl;
		}

	}


}