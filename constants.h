#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <time.h>

using namespace std;

//chunk constants
const int HEIGHT = 40;
const int WIDTH = 150;
const int CHUNKLIM = 20;

//inventory constants
const int NUMBOXESX = 5;
const int NUMBOXESY = 6;
const int BOXWIDTH = 12;	
const int BOXHEIGHT = 6;

//player constants
const int YSTART = HEIGHT-2;
const int chunkX = 50;
const int JUMPINGHEIGHT = 12;
const int DEFHP = 20;
const int DEFAT = 1;
const int DEFDE = 1;
const int DEFAC = 1;
const int DEFEV = 1;
const int DEFRA = 1;

//misc constants
const int NUMSPECIES = 50;
const int SEED = time(0);

#endif
