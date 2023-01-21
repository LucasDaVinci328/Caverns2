// caverns.cpp
// Name: Caverns Game
// Author: Luke Devenney
// OG Date:9/10/21 New version start: 10/11/2021 Updated this backup: 10/11/2021

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "constants.h"
#include "debug.h"
#include "cavegrowth.h"
#include "box.h"
#include "screenPrint.h"
#include "entityNitems.h"
#include "colors.h"
#include "inventory.h"

using namespace std;

int main() {

srand(SEED);

int seeds[CHUNKLIM];

for (int i = 0; i < CHUNKLIM; i++) {
        seeds[i] = rand();
}

set setList[6];
generate_sets(setList);

species speciesList[NUMSPECIES];
generate_species_list(speciesList);

item inventory[31];
vector<item> itemList;
vector<entity> enemies;

entity player;

player.change_base_stats('H', DEFHP);
player.change_base_stats('A', DEFAT);
player.change_base_stats('D', DEFDE);
player.change_base_stats('C', DEFAC);
player.change_base_stats('E', DEFEV);
player.change_base_stats('R', DEFRA);
player.health = DEFHP;

player.x = chunkX;
player.y = YSTART;
player.jumpMax = JUMPINGHEIGHT;
player.climbing = 1;

block chunk1[HEIGHT][WIDTH];
block chunk2[HEIGHT][WIDTH];

int chunk1Holding = 1;
int chunk2Holding = 2;

grow(chunk1, seeds[chunk1Holding-1], seeds[chunk1Holding], chunk1Holding);
grow(chunk2, seeds[chunk2Holding-1], seeds[chunk2Holding], chunk2Holding);

bool paused = 0;
bool playing = 1;
bool bestiary = 0;
string display;

int depth = 1;

while (playing) {//start of game while loop
	srand(time(0)+rand());	

	if (player.y<=0) {

		srand(seeds[CHUNKLIM]);

		for (int i = 0; i < CHUNKLIM; i++) {
        		seeds[i] = rand();
		}
		player.x = chunkX;
		player.y = YSTART;
		player.jumping = 0;
		chunk1Holding = 1;
		chunk2Holding = 2;

		grow(chunk1, seeds[chunk1Holding-1], seeds[chunk1Holding], chunk1Holding);
		grow(chunk2, seeds[chunk2Holding-1], seeds[chunk2Holding], chunk2Holding);
		depth++;
	}

	block screen[HEIGHT][WIDTH];
	int changeX = 0;
	int changeY = 0;
	int camX = (player.x-chunkX);

	//chunk growth logic
	if (chunk1Holding != (camX/WIDTH)+1) {
		chunk1Holding = (camX/WIDTH)+1;
                chunk2Holding = chunk1Holding+1;
		if (camX%WIDTH==0) {
			for(int y = HEIGHT-1; y>=0; y--) {
				for (int x = 0; x < WIDTH; x++) {
					chunk1[y][x] = chunk2[y][x];
				}
			}
			grow(chunk2, seeds[chunk2Holding-1], seeds[chunk2Holding], chunk2Holding);
		} else
		if ((camX+1)%WIDTH==0) {
			for(int y = HEIGHT-1; y>=0; y--) {
				for (int x = 0; x < WIDTH; x++) {
					chunk2[y][x] = chunk1[y][x];
				}
			}	
			grow(chunk1, seeds[chunk1Holding-1], seeds[chunk1Holding], chunk1Holding);
		}
	}

		//stitch the screen
		for(int y = HEIGHT-1; y>=0; y--) {
			for (int x = 0; x < WIDTH; x++) {
				if ((camX)%WIDTH + x < WIDTH) screen[y][x] = chunk1[y][(camX)%WIDTH+x];
				else screen[y][x] = chunk2[y][((camX)%WIDTH+x)%WIDTH];
			}
		}

		setscrn(screen);

		//sets collision for the player
		screen[player.y][chunkX].collision = 2;

		//put items on screen
		for (int i = 0; i < itemList.size(); i++) {
			display+= to_string(itemList[i].x) + " " + to_string(itemList[i].y) + " ";
			if ((itemList[i].x<camX) | (itemList[i].x>camX+WIDTH)) {
				itemList.erase (itemList.begin()+i);
			} else {
				if (screen[itemList.at(i).y-1][itemList.at(i).x-camX].collision == 0) itemList[i].y--;
				screen[itemList.at(i).y][itemList.at(i).x-camX].display = '!';
				screen[itemList.at(i).y][itemList.at(i).x-camX].displayFore = "yellow";
			}
		}
		itemList.shrink_to_fit();		
		
		//put enemies on screen
		for (int i = 0; i < enemies.size(); i++) {
			display+= enemies[i].name + " ";
			if ((enemies[i].x<camX) | (enemies[i].x>camX+WIDTH-1)) {
				enemies.erase (enemies.begin()+i);
			} else if (enemies[i].health<=0) {
				if (speciesList[enemies[i].speciesId].equipment) {
					for (int j = 1; j <= 8; j++) itemList.push_back(enemies[i].equipment[j]);
				}
				enemies.erase (enemies.begin()+i);
			} else {
				enemies[i].ai(screen, player, speciesList, camX);
				screen[enemies[i].y][enemies[i].x-camX].display = speciesList[enemies[i].speciesId].name[0];
				screen[enemies[i].y][enemies[i].x-camX].displayFore = "red";
				speciesList[enemies[i].speciesId].discovered = 1;
			}
		}
		enemies.shrink_to_fit();	

		//put player on the screen
                screen[player.y][chunkX].display = -3;
                screen[player.y][chunkX].displayFore = "green";


		printscrn(screen);

	player.update_stats();

	//Health Display
	cout<< "Health: ";
	for(int i = 0; i < player.maxHealth; i++) {
		if (i<player.health) setColor("green", 1, 1);
		else setColor("red", 1);	
		cout<<' ';
		setColor("reset");
		cout<<' ';
	}
	cout<<"\n";
	
	cout<< camX<< " "<<chunk1Holding<< " "<< chunk2Holding<<"\n";
	
	cout<<display<<"\n";
	display = "";

	//inputer
	cout<<"Make a move: "<<flush;
	char response;
	system("stty raw");
	response = getchar();
	system("stty cooked");
	switch(response) {
		case 'S':
			playing = 0;
			break;
		case 'd':
			changeX++;
			break;
		case 'D':
			player.direction = 1;
			break;
		case 'a':
			changeX--;
			break;
		case 'A':
			player.direction = -1;
			break;
		case 'w':
			if ((screen[player.y-1][chunkX].collision==1) | ((screen[player.y][chunkX-1].collision==1) | (screen[player.y][chunkX+1].collision==1))) player.jumping=1;
			break;
		case 's':
			player.jumping = 0;
			break;
		case 'i':
			manage_inventory(inventory, player.equipment, &player, itemList);
			paused = 1;
			break;
		case 'm':
			itemList.push_back(generateItem(setList));
			itemList.back().x = player.x;
			itemList.back().y = player.y;
			break;
		case 'p':
			for (int i = 0; i < itemList.size(); i++) {
				if ((itemList[i].x==player.x) & (itemList[i].y==player.y)) {
					for (int j = 1; j <= 30; j++) {
						if (inventory[j].type==0) {
							inventory[j] = itemList[i];
							itemList.erase (itemList.begin()+i);
							display += "You picked up the " + inventory[j].name;
							j = 31;
						}
					}
					i = itemList.size();
				}
			}
			break;
		case 'q':
			generate_enemy(enemies, screen, speciesList, camX, setList);
			break;
		case 'b':
			bestiary = 1;
			break;
		case 'E':
			if (enemies.size()>0) enemies.erase(enemies.begin());
			break;
		case 'k':
			player.standard_attack(screen, camX, player, enemies);
			break;
	}

	int speciesOn = 0;
	while (bestiary) {
		system("clear");
		downwards(1);
		for (int i = speciesOn-4; i <= speciesOn+4; i++) {
			int u = (i<0)? NUMSPECIES+i : (i>=NUMSPECIES)? i-NUMSPECIES : i;
			rightwards(1);
			if (u+1<10) cout<<0;
			cout<<u+1;
			if (u == speciesOn)  cout<<"\033[7m";
			box(BOXWIDTH*3, 3);
			cout<<"\033[0m";
			box_display(((speciesList[u].discovered)? speciesList[u].name : "NOT ENCOUNTERED"), BOXWIDTH*3, 3);
			cout<<"\n";
			downwards(1);
		}
		if (speciesList[speciesOn].discovered) {
			rightwards(BOXWIDTH*3+5);
			upwards(27);
			box(BOXWIDTH*5, BOXHEIGHT*3-1);
			box_display(speciesList[speciesOn].description, BOXWIDTH*5, BOXHEIGHT*3-1);
			downwards(10);
			cout<<"\n";
		}
		char response;
		system("stty raw");
		cin>>response;
		system("stty cooked");
		switch (response) {
			case 'b':
				bestiary = 0;
				break;
			case 'w':
				speciesOn--;
				break;
			case 's':
				speciesOn++;
				break;
		}
		speciesOn = speciesOn%NUMSPECIES;
		if (speciesOn<0) speciesOn = NUMSPECIES+speciesOn;
	}	
		

	player.move(screen, chunkX, changeX);     

}//end of game while loop
cout<<"\n"<<SEED<<"\n";
return 0;
}
