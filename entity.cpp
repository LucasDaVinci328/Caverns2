// entity.cpp
// Name: Entity Class Library
// Author: Luke Devenney
// Date: 10/11/2021

#include <string>
#include <math.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>

#include "entityNitems.h"
#include "cavegrowth.h"
#include "colors.h"
#include "box.h"

using namespace std;

void entity::standard_attack(block screen[][WIDTH], int camX, entity player, vector<entity> &enemyList) {
	int chunkX = x - camX;
	cout<<"\n";
	upwards(y+6);
	rightwards(chunkX+1+direction);
	setColor("green");
	for (int i = 0; i < range; i++) {
		screen[y][chunkX + (i*direction)].damage = attack;
		screen[y][chunkX + (i*direction)].evasion =  accuracy;
		if ((screen[y][chunkX+(i*direction)].collision != 1) & (((chunkX+(i*direction))<=WIDTH) & (chunkX+(i*direction)>=0))) {
        		cout<< '-' <<flush;
			this_thread::sleep_for(std::chrono::milliseconds(50));
			leftwards(1);
			if (equipment[4].type==2) cout<<" "<<flush;
			else rightwards(1);

        	        if (direction<0)
        	        	leftwards(2);
       		} else {
        		i +=range;
        	}
	}
	for (int i = 0; i < enemyList.size(); i++) {
		if (screen[enemyList[i].y][chunkX].damage!=0) 
			enemyList[i].damage(screen[enemyList[i].y][chunkX].damage, screen[enemyList[i].y][chunkX].evasion);
	}
	setColor("reset");
}

void entity::move(block screen[][WIDTH], int chunkX, int changeX, int changeY) {
	int offsetX = x - chunkX;

	int colID[10];
        colID[1] = screen[y-1][chunkX-1].collision;
        colID[2] = screen[y-1][chunkX].collision;
        colID[3] = screen[y-1][chunkX+1].collision;
        colID[4] = screen[y][chunkX-1].collision;
        colID[5] = screen[y][chunkX].collision;
        colID[6] = screen[y][chunkX+1].collision;
        colID[7] = screen[y+1][chunkX-1].collision;
        colID[8] = screen[y+1][chunkX].collision;
        colID[9] = screen[y+1][chunkX+1].collision;

	//collision detection for X
	if (changeX!=0) {
		direction = 1;
        	if (changeX>0) {
        	        if (colID[6]==0) {
        	                x++;
				changeX = 0;
           		} else if (colID[9]==0) {
               		       	x++;
                	       	changeX = 0;
                	       	changeY = 2;
                	} else if ((flying | climbing) & (colID[8]==0)) {
                	        changeX = 0;
                	        changeY = 2;
      			} else {
				direction = -1;
			}
        	} else if (changeX<0) {
			direction = -1;
                	if (colID[4]==0) {
                	        x--;
                	        changeX = 0;
			} else if (colID[7]==0) {
                		x--;
                	        changeX = 0;
                	        changeY = 2;
                	} else if ((flying | climbing) & (colID[8]==0)) {
                        	changeX = 0;
				changeY = 2;
    			} else {
				direction = 1;
			}
        	}
	}

	chunkX = x - offsetX;

	colID[1] = screen[y-1][chunkX-1].collision;
        colID[2] = screen[y-1][chunkX].collision;
        colID[3] = screen[y-1][chunkX+1].collision;
        colID[4] = screen[y][chunkX-1].collision;
        colID[5] = screen[y][chunkX].collision;
        colID[6] = screen[y][chunkX+1].collision;
        colID[7] = screen[y+1][chunkX-1].collision;
        colID[8] = screen[y+1][chunkX].collision;
        colID[9] = screen[y+1][chunkX+1].collision;

	//jumping & falling
	if (!flying) {
		if (jumping>0) {
        		jumping++;
        		changeY++;
		} else if (colID[2]==0) {
			changeY--;
		}
		jumping = jumping%jumpMax;
	} else {
		changeY = 1;
	}

	//collission detection for Y
        if (changeY!=0) {
        	if (changeY>0) {
        	        if (colID[8]==0) {
        	                y++;
        	        } else {
        	                jumping = 0;
               		 }
        	} else if (changeY<0) {
        	        if (colID[2]==0) {
        	                y--;
        	        }
        	}
		changeY = 0;
	}

}

void entity::ai(block screen[][WIDTH], entity player, species speciesList[NUMSPECIES], int camX) {
	bool idling = 0;
	
	screen[y][chunkX].collision = 2;
	
	int xDesire = 0;
	int yDesire = 0;
	
	switch (speciesList[speciesId].aiType) {
		case 1:
		case 2:
			if (((player.y<y+10) & (player.y>y-11)) & ((player.x<x+10) & (player.x>x-11))) {
				if (player.x-range>x) {
					xDesire = 1;
					direction = 1;
				} else if (player.x+range<x) {
					xDesire = -1;
					direction = -1;
				}
				if (flying | (xDesire==0)) {
					if (player.y>y) yDesire = 1;
					else if (player.y<y) yDesire = -1;
				}
				if (player.y>y) jumping = 1;	
				move(screen, x-camX, xDesire, yDesire);
			} else {
				idling =1;
			}
			break;
		case 0:
		default:
			idling = 1;
			break;
	}
	if (idling) {
		move(screen, x-camX, direction, 0);
	}
}

void entity::change_base_stats(char stat, int newAmount) {
	switch (stat) {
		case 'H':
			DEFAULT_HEALTH = newAmount;
			break;
		case 'A':
			DEFAULT_ATTACK = newAmount;
			break;
		case 'D':
			DEFAULT_DEFENSE = newAmount;
			break;
		case 'C':
			DEFAULT_ACC = newAmount;
			break;
		case 'E':
			DEFAULT_EVADE = newAmount;
			break;
		case 'R':
			DEFAULT_RANGE = newAmount;
			break;
	}
}

void entity::update_stats() {
	setBonus = 1.0;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if ((j!=i) & (equipment[j].itemSet.setID!=0)) setBonus += ((equipment[i].itemSet.setID == equipment[j].itemSet.setID)? 0.1 : 0.0);
		}
	}
	maxHealth = DEFAULT_HEALTH;
	attack = DEFAULT_ATTACK;
	defense = DEFAULT_DEFENSE;
	accuracy = DEFAULT_ACC;
	evasion = DEFAULT_EVADE;
	range = DEFAULT_RANGE;
	for (int i = 1; i <= 8; i++) {
		maxHealth += equipment[i].Hp(setBonus);
		attack += equipment[i].At(setBonus);
		defense += equipment[i].De(setBonus);
		accuracy += equipment[i].Ac(setBonus);
		evasion += equipment[i].Ev(setBonus);
		range += equipment[i].Ra(setBonus);
	}
}

void entity::damage(int damage, int accuracy) {
	if (rand()%accuracy > rand()%evasion) {
		damage = rand()%damage - rand()%defense;
		health = (health>=damage)? health-damage : 0;
	}
}
