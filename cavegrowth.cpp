//cavegrowth.cpp
//Name: Cave Growth
//Author: Luke Devenney
//Date: 10/13/2021

#include <string>

#include "constants.h"
#include "cavegrowth.h"

using namespace std;

bool isBound(int i, int lowerBound, int upperBound) {
	return ((i>=lowerBound) & (i<=upperBound))? 1 : 0;
}

void transfer(block transfer[],int height,  int width, block parent[][WIDTH], int x, int y, char term) {
	int i = 0;
	for (int y2 = height-1; y2 >= 0; y2--) {
		for (int x2 = 0; x2 < width; x2++) {
			if (isBound(x, 0, WIDTH-1) & isBound(y+y2, 0, HEIGHT-1)) { 		
				block transferBlock = parent[y+y2][x+x2];
				switch (term) {
                                	case 'C':
                                	        transferBlock.collision = transfer[i].collision;
                                        	break;
                                	case 'O':
                                        	transferBlock.oreColor = transfer[i].oreColor;
                                        	break;
                               		case 'c':
                                        	transferBlock.oreCharacter = transfer[i].oreCharacter;
                                        	break;
                                	case 'D':
                                        	transferBlock.damage = transfer[i].damage;
                                        	break;
                                	case 'E':
                                        	transferBlock.evasion = transfer[i].evasion;
                                        	break;
                                	case 'F':
                                        	transferBlock.fore = transfer[i].fore;
                                        	break;
                                	case 'B':
                                        	transferBlock.back = transfer[i].back;
                                        	break;
                                	case 'd':
                                        	transferBlock.display = transfer[i].display;
                                        	break;
                                	default:
                                        	transferBlock.collision = transfer[i].collision;
						transferBlock.oreColor = transfer[i].oreColor;
						transferBlock.oreCharacter = transfer[i].oreCharacter;
						transferBlock.damage = transfer[i].damage;
						transferBlock.evasion = transfer[i].evasion;
						transferBlock.fore = transfer[i].fore;
						transferBlock.back = transfer[i].back;
						transferBlock.display = transfer[i].display;
     				}
				parent[y+y2][x+x2] = transferBlock;
			}
			i++;
		}
	}



}

void empty(block chunk[][WIDTH], char term) {
	for (int y = HEIGHT-1; y>=0; y--) {
		for (int x = 0; x < WIDTH; x++) {
			switch (term) {
				case 'C':
					chunk[y][x].collision = 0;
					break;
				case 'O':
					chunk[y][x].oreColor = Color(0, 0, 0);
					break;
				case 'c':
					chunk[y][x].oreCharacter = ' ';
					break;
				case 'D':
					chunk[y][x].damage = 0;
					break;
				case 'E':
					chunk[y][x].evasion = 0;
					break;
				case 'F':
					chunk[y][x].fore = Color(255, 255, 255);
					break;
				case 'B':
					chunk[y][x].displayBack = Color(0, 0, 0);
					break;
				case 'd':
					chunk[y][x].display = ' ';
					break;
				default:
					chunk[y][x].collision = 0;
					chunk[y][x].oreColor = Color(0, 0, 0);
					chunk[y][x].oreCharacter = ' ';
					chunk[y][x].damage = 0;
					chunk[y][x].evasion = 0;
					chunk[y][x].fore = Color(255, 255, 255);
					chunk[y][x].back = Color(0, 0, 0);
					chunk[y][x].display = ' ';
					break;
			}
		}
	}
}

void reset(block* Block) {
	block test;
	test.collision = 0;
	test.back = Color(0, 0, 0);
	*Block = test;
	/*
	*Block.oreColor = "reset";
        *Block.oreCharacter = ' ';
        *Block.damage = 0;
        *Block.evasion = 0;
        *Block.displayFore = "reset";
	*Block.displayBack = "black";
        *Block.display = ' ';
	*/
}

void grow(block chunk[][WIDTH], int seed1, int seed2, int chunkNum) {
	srand(seed1);
	int boreStart = rand()%((HEIGHT-6)-5)+5;
	srand(seed2);
	int boreGoal = rand()%((HEIGHT-6)-5)+5;

	empty(chunk);

	int tempRan = rand();
	for(int y=HEIGHT-1; y>=0; y--) { //this puts random growths
		for(int x=0; x<WIDTH; x++) {
			if ((y==HEIGHT-1) | (((x==0) & (chunkNum==1)) | ((x==WIDTH-1) & ((chunkNum==0) | (chunkNum==CHUNKLIM-1))))) {//ceiling and left wall if its the first chunk
				chunk[y][x].collision = rand()%4+2;
			} else if (y==0) {//floor
				chunk[y][x].collision =  chunk[HEIGHT-1][x].collision;
			} else {
				tempRan = rand()%750;
				if (tempRan==0) {//random growths in the world
					chunk[y][x].collision = rand()%2+2;
				} else {
					chunk[y][x].collision = 0;
				}
			}
			if (chunk[y][x].collision != 0) {
				if (rand()%5==0){
					chunk[y][x].oreColor = randColor();
					char c = ' ';
					switch(rand()%6) {
						case 0:
							c = '*';
							break;
						case 1:
							c = ':';
							break;
						case 2:
							c = '~';
							break;
						case 3:
							c = '+';
							break;
						case 4:
							c = '%';
							break;
						case 5:
							c = '#';
							break;
					}
					chunk[y][x].oreCharacter = c;
				} else if ((x>0) & (rand()%2==0)) {
					chunk[y][x].oreCharacter = chunk[y][x-1].oreCharacter;
					chunk[y][x].oreColor = chunk[y][x-1].oreColor;
				}
			}
		}
	}

	bool working = 1; //growth of the cave patterns
	while(working) {
		block holdingChunk[HEIGHT][WIDTH];
		working = 0;
		for(int y=HEIGHT-1; y>=0; y--) {
        		for(int x=0; x<WIDTH; x++) {
        	        	if (chunk[y][x].collision>1) {
					working = 1;
					tempRan = rand()%(chunk[y][x].collision);
					if (x<WIDTH-2) {
						if (chunk[y][x+1].collision<1) {
							holdingChunk[y][x+1].collision = chunk[y][x].collision - tempRan;
							holdingChunk[y][x+1].oreColor = chunk[y][x].oreColor;
							holdingChunk[y][x+1].oreCharacter = chunk[y][x].oreCharacter;
						}
					}
					if (x>1) {
						if (chunk[y][x-1].collision<1) {
               	                        		holdingChunk[y][x-1].collision = chunk[y][x].collision - tempRan;
							holdingChunk[y][x-1].oreColor = chunk[y][x].oreColor;
							holdingChunk[y][x-1].oreCharacter = chunk[y][x].oreCharacter;
						}
					}
               	           		tempRan = rand()%(chunk[y][x].collision);

					if (y<HEIGHT-2) {
						if (chunk[y+1][x].collision<1) {
        	                           	     	holdingChunk[y+1][x].collision = chunk[y][x].collision - tempRan;
							holdingChunk[y+1][x].oreColor = chunk[y][x].oreColor;
							holdingChunk[y+1][x].oreCharacter = chunk[y][x].oreCharacter;
						}
					}
					if (y>1) {
                				if (chunk[y-1][x].collision<1) {
                	                	        holdingChunk[y-1][x].collision = chunk[y][x].collision - tempRan;
							holdingChunk[y-1][x].oreColor = chunk[y][x].oreColor;
							holdingChunk[y-1][x].oreCharacter = chunk[y][x].oreCharacter;
						}
					}
       					chunk[y][x].collision = 1;
					holdingChunk[y][x].collision = 1;
				}
				if (holdingChunk[y][x].collision < chunk[y][x].collision)
					holdingChunk[y][x].collision = chunk[y][x].collision;
				if (holdingChunk[y][x].oreColor.r == 0 && holdingChunk[y][x].oreColor.g == 0 && holdingChunk[y][x].oreColor.b == 0) {
					holdingChunk[y][x].oreColor = chunk[y][x].oreColor;
					holdingChunk[y][x].oreCharacter = chunk[y][x].oreCharacter;
				}
        		}
		}
		for(int v=HEIGHT-1;v>=0;v--) {
          		for(int u=0;u<WIDTH;u++) {
              	         	chunk[v][u].collision = holdingChunk[v][u].collision;
				chunk[v][u].oreColor = holdingChunk[v][u].oreColor;
				chunk[v][u].oreCharacter = holdingChunk[v][u].oreCharacter;
				if (chunk[v][u].collision == 1) chunk[v][u].back = (rand()%5==0)? Color(128, 128, 128) : Color(255, 255, 255);
			}
		}		
	}
	
	//sand fill-in 
	tempRan = rand()%8+8;
	for (int x = 0; x<WIDTH; x++) {
		if (chunkNum==CHUNKLIM-1) x = WIDTH;
        	if (x%(WIDTH/8)==0)
         	       tempRan += rand()%5-2;
		while (tempRan < 5)
			tempRan += rand()%2+1;
		while (tempRan > (HEIGHT/3))
			tempRan += rand()%2-2;
       		for (int y = tempRan; y>=0; y--) {
                	if (chunk[y][x].collision == 0) {
                        	chunk[y][x].collision = 1;
				chunk[y][x].back = Color(242, 209, 107);
                	} else {
                        	y = -1;
                	}
        	}
	}
	
	//stalagmites and stalacites
	if (rand()%5==0) {
		int numSpikes = rand()%(10)+1;
		int spikeX = 0;
		for (int i = 0; i < numSpikes; ++i) {
			if ((WIDTH-spikeX)<numSpikes) break;
			int x = spikeX + (rand()%((WIDTH-spikeX)/numSpikes)) +1;
			spikeX = x;
			if (x+2 > WIDTH)
				break;
			int y1 = HEIGHT-1;
			while ((chunk[y1][x].collision==1) & (y1>10))//finds roof
				y1--;
			int y2 = y1;
			while ((chunk[y2][x].collision==0) & (y2>10))//finds floor
				y2--;
			y2++;
			if (((y1>11) & (y2>11)) & (y1!=y2)) {
			int height = rand()%(y1-y2)+((y1-y2)/5);
			for (int s = 0; s < height/2; ++s) {
				chunk[y1][x].collision=1;
				chunk[y1][x].back = Color(255, 255, 255);
				chunk[y2][x].collision=1;
				chunk[y2][x].back = Color(255, 255, 255);
				if (s < (height/4)) {
					chunk[y1][x+1].collision=1;
					chunk[y1][x-1].collision=1;
					chunk[y2][x+1].collision=1;
					chunk[y2][x-1].collision=1;
				}	
				y1--;
				y2++;
			}
			}
		}
	}

	//tunnel borer
	int boreY = (chunkNum==1)? YSTART : boreStart;
	for (int boreX = ((chunkNum==1)? chunkX : 0); boreX < (((chunkNum==0) | (chunkNum==CHUNKLIM-1))? WIDTH-30 : WIDTH); boreX++) {
		boreY = (boreY<5)? 5 : (boreY>HEIGHT-6)? HEIGHT-6 : boreY;
		tempRan = rand()%4 - ((boreY > boreGoal)? 2 : 1);
		
		chunk[boreY][boreX].collision=0;
		reset(&chunk[boreY][boreX]);
		if (boreX>0) reset(&chunk[boreY][boreX-1]);
		if (boreX<WIDTH-1) reset(&chunk[boreY][boreX+1]);
		reset(&chunk[boreY-1][boreX]);
		reset(&chunk[boreY+1][boreX]);

		boreY += tempRan;
	}

	while (boreY < boreGoal) {//in case bore doesnt end at goal
		reset(&chunk[boreY][WIDTH-2]);
		reset(&chunk[boreY][WIDTH-1]);
		reset(&chunk[boreY-1][WIDTH-1]);
		reset(&chunk[boreY+1][WIDTH-1]);
		boreY++;
	}

	while (boreY > boreGoal) {//in case bore doesnt end at goal
		reset(&chunk[boreY][WIDTH-2]);
		reset(&chunk[boreY][WIDTH-1]);
		reset(&chunk[boreY-1][WIDTH-1]);
		reset(&chunk[boreY+1][WIDTH-1]);
		boreY--;
	}

	

	/*
	//cave paintings
	if (1) {//in future rand()%10
		int paintWidth = rand()%4+5;
		int paintHeight = rand()%3+5;
		for (int y = (HEIGHT-1); y >= paintHeight; y--) {
			for (int x = 0; x < WIDTH-paintWidth; x++) {
				if ((chunk[y][x].collision==1) & (rand()%20==0)) {
					y -= paintHeight/2;
					for (int u = x; u < paintWidth; u++) {
						chunk[y][x].displayBack = "red";
						if ((u==0) | (u==paintWidth*(2.0/3.0))) {
							for (int v = y; v < (paintHeight/2); v--) {
								chunk[y-v][x].displayBack = "red";
							}
						}
					}
				}
			}
		}
	}
	*/

	//holes for first and last chunks
	if (chunkNum==1) {
		block deleted[(HEIGHT/2)*(WIDTH/2)];
		transfer(deleted, HEIGHT/2, WIDTH/2, chunk, WIDTH/4, HEIGHT/2, 'A');
	}
	
	if (chunkNum==CHUNKLIM-1) {
		block deleted[(HEIGHT/2)*(WIDTH/2)];
                transfer(deleted, HEIGHT/2, WIDTH/2, chunk, WIDTH/4, 0, 'A');
	}
	

	//final checker for holes, pits, and pebbles
	for (int y = HEIGHT-1; y >= 0; y--) {
		for (int x = 0; x < WIDTH; x++) {
			int border[10] = {0, ((y==0) | (x==0))? 1 : chunk[y-1][x-1].collision, (y==0)? 1 :chunk[y-1][x].collision, ((y==0) | (x==WIDTH-1))? 1 :chunk[y-1][x+1].collision, (x==0)? 1 :chunk[y][x-1].collision, chunk[y][x].collision, (x==WIDTH-1)? 1 :chunk[y][x+1].collision, ((y==HEIGHT-1) | (x==0))? 1 :chunk[y+1][x-1].collision, (y==HEIGHT-1)? 1 :chunk[y+1][x].collision, ((y==HEIGHT-1) | (x==WIDTH-1))? 1 :chunk[y+1][x+1].collision};
			int cardinalSum = border[2]+border[4]+border[6]+border[8];
			switch (cardinalSum) {
				case 0:
					reset(&chunk[y][x]);
					break;
				case 3:
				case 4:
					if (chunk[y][x].collision==0) {
						chunk[y][x].collision = 1;
						chunk[y][x].back = Color(128, 128, 128);
					}
					break;
			}
		}
	}

}
	
