#ifndef CAVEGROWTH_H
#define CAVEGROWTH_H

#include <string>

#include "constants.h"
#include "colors.h"

using namespace std;

class block {
	public:
	int collision = 0;
	Color oreColor;
	char oreCharacter = ' ';
	int damage = 0;
	int evasion = 0;
	Color fore;
	Color back;
	int display = ' ';
};

bool isBound(int i, int lowerBound, int upperBound);

void transfer(block transfer[],int height,  int width, block parent[][WIDTH], int x, int y, char term = 'A');

void empty(block chunk[][WIDTH], char term = 'A');

void reset(block Block);

void grow(block chunk[][WIDTH], int seed1, int seed2, int chunkNum = 2); 

#endif
