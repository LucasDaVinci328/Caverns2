// inventory.cpp
// Name: Inventory Manager
// Author: Luke Devenney
// Date: 10/18/2021

#include <string>
#include <vector>
#include <iostream>

#include "constants.h"
#include "box.h"
#include "entityNitems.h"
#include "inventory.h"
#include "colors.h"

using namespace std;

void qualityColor(int quality) {
	switch(quality) {
		case 5:
			setColor("white");
			break;
		case 4:
			setColor("cyan");
			break;
		case 3:
			setColor("green");
			break;
		case 2:
			setColor("yellow");
			break;
		case 1:
			setColor("red");
			break;
		default:
			setColor("reset");
	}
}

void manage_inventory(item inventory[], item equipment[], entity* PLAYER, vector<item> itemList) {
bool onInventory = 1;
int invY = 0;
int invX = 0;
while (onInventory) {
	int currInv = (invY*NUMBOXESX)+invX+1;

	entity player = *PLAYER;
	player.update_stats();

	for (int i = 0; i <= 30; i++){
		inventory[i].x = player.x;
		inventory[i].y = player.y;
	}

	system("clear");

	//inventory boxes
	for (int y = 0; y < NUMBOXESY; y++) {
		for (int x = 0; x < NUMBOXESX; x++) {
			if ((y == invY) & (x == invX)) {
				cout<< "\033[7m";
			} else {
				cout<< "\033[0m";
			}
			box(BOXWIDTH,BOXHEIGHT);
			cout<< "\033[0m";
			qualityColor(inventory[(y*NUMBOXESX)+x+1].quality);
			box_display(inventory[(y*NUMBOXESX)+x+1].name, BOXWIDTH, BOXHEIGHT);
			setColor("reset");
			upwards(BOXHEIGHT-1);
			rightwards(2);
		}
		downwards(BOXHEIGHT);
		cout<<"\n";
	}
	
	//current stats
	upwards((BOXHEIGHT+1)*NUMBOXESY);
        downwards(3);
	rightwards((BOXWIDTH+2)*NUMBOXESX);
	rightwards(20);
	cout<< "Hp:" << player.maxHealth;
	downwards(2);
	leftwards(to_string(player.maxHealth).length() + 3);
	cout<< "At:" << player.attack;
	downwards(2);
	leftwards(to_string(player.attack).length() + 3);
	cout<< "De:" << player.defense;	
	upwards(4);
	leftwards(to_string(player.defense).length() + 3);

	rightwards(10+BOXWIDTH);

	cout<< "Ac:" << player.accuracy;
	downwards(2);
	leftwards(to_string(player.accuracy).length() + 3);
	cout<< "Ev:" << player.evasion;
	downwards(2);
	leftwards(to_string(player.evasion).length() + 3);
	cout<< "Ra:" << player.range;
	upwards(4);
	leftwards(to_string(player.range).length() + 3);

	leftwards(10+BOXWIDTH);

	//equippable slots
	//head slot
	rightwards(7);
	upwards(1);
	if (inventory[currInv].slot==1) {
		cout<< "\033[7m";
	} else {
		cout<< "\033[0m";
	}
	box(BOXWIDTH,BOXHEIGHT);
	cout<< "\033[0m";
	qualityColor(equipment[1].quality);
	box_display(equipment[1].name, BOXWIDTH, BOXHEIGHT);
	setColor("reset");
        downwards(1);
        leftwards(BOXWIDTH-((BOXWIDTH-8)/2));
        cout<< "Hd Notch";
	rightwards((BOXWIDTH-8)/2);

	//chest slot
	downwards(5);
	leftwards(BOXWIDTH);
	if (inventory[currInv].slot==2) {
		cout<< "\033[7m";
	} else {
		cout<< "\033[0m";
	}
	box(BOXWIDTH,BOXHEIGHT);
	cout<< "\033[0m";
	qualityColor(equipment[2].quality);
	box_display(equipment[2].name, BOXWIDTH, BOXHEIGHT);
	setColor("reset");
	downwards(1);
        leftwards(BOXWIDTH-((BOXWIDTH-8)/2));
        cout<< "Ch Notch";
	rightwards((BOXWIDTH-8)/2);

	//offhand/lefthand slot
	upwards(BOXHEIGHT+3);
	leftwards((2*BOXWIDTH)+2);
	if (inventory[currInv].slot==3) {
		cout<< "\033[7m";
	} else {
		cout<< "\033[0m";
	}
	box(BOXWIDTH, BOXHEIGHT);
	cout<< "\033[0m";
	qualityColor(equipment[3].quality);
	box_display(equipment[3].name, BOXWIDTH, BOXHEIGHT);
	setColor("reset");
        downwards(1);
        leftwards(BOXWIDTH-((BOXWIDTH-8)/2));
        cout<< "LH Notch";
	rightwards((BOXWIDTH-8)/2);

	//mainhand/righthand slot
	upwards(BOXHEIGHT);
	rightwards(BOXWIDTH+4);	
	if (inventory[currInv].slot==4) {
		cout<< "\033[7m";
	} else {
		cout<< "\033[0m";
	}
	box(BOXWIDTH, BOXHEIGHT);
	cout<< "\033[0m";
	qualityColor(equipment[4].quality);
	box_display(equipment[4].name, BOXWIDTH, BOXHEIGHT);
	setColor("reset");
        downwards(1);
        leftwards(BOXWIDTH-((BOXWIDTH-8)/2));
        cout<< "RH Notch";
	rightwards((BOXWIDTH-8)/2);

	downwards(8);
	leftwards((BOXWIDTH*3)+(BOXWIDTH/2)+5);
	
	for (int i = 1; i <= 4; i++) {//amulet slots
		if (inventory[currInv].slot==5) {
			cout<< "\033[7m";
		} else {
			cout<< "\033[0m";
		}
		box(BOXWIDTH, BOXHEIGHT);
		cout<< "\033[0m";
		qualityColor(equipment[4+i].quality);
		box_display(equipment[4+i].name, BOXWIDTH, BOXHEIGHT);
		setColor("reset");
		downwards(1);
		leftwards(BOXWIDTH-((BOXWIDTH-8)/2));
		cout<< "Amulet " << i;
		rightwards((BOXWIDTH-8)/2);
                upwards(BOXHEIGHT);
                rightwards(2);
	}

	downwards(BOXHEIGHT+4);
	leftwards((BOXWIDTH+2)*4);

	//description of items
	box(((BOXWIDTH+2)*4) - 2, BOXHEIGHT);
	box_display(inventory[currInv].description, ((BOXWIDTH+2)*4) - 2, BOXHEIGHT);
	rightwards(2);
	box_display("Hp:" + to_string(inventory[currInv].Hp(player.setBonus)), ((BOXWIDTH+2)*4) - 2, 3);
	rightwards(8);
	box_display("At:" + to_string(inventory[currInv].At(player.setBonus)), ((BOXWIDTH+2)*4) - 2, 3);
	rightwards(8);
	box_display("De:" + to_string(inventory[currInv].De(player.setBonus)), ((BOXWIDTH+2)*4) - 2, 3);
	rightwards(8);
	box_display("Ac:" + to_string(inventory[currInv].Ac(player.setBonus)), ((BOXWIDTH+2)*4) - 2, 3);
	rightwards(8);
	box_display("Ev:" + to_string(inventory[currInv].Ev(player.setBonus)), ((BOXWIDTH+2)*4) - 2, 3);
	rightwards(8);
	box_display("Ra:" + to_string(inventory[currInv].Ra(player.setBonus)), ((BOXWIDTH+2)*4) - 2, 3);
	downwards(2);	
	cout<<"\n";
	

	//inputer
	system("stty raw");
	char response = getchar();
	system("stty cooked");
	if (response == 'i') {
		onInventory = 0;
	} else if (response == 'd') {
		invX++;
	} else if (response == 'a') {
		invX--;
	} else if (response == 'w') {
		invY--;
	} else if (response == 's') {
		invY++;
	} else if (response == 'e') {
		int switchSlot = inventory[currInv].slot;
		if ((inventory[currInv].type == 0) & (inventory[currInv].slot==0)) {
			while ((switchSlot<1) | (switchSlot>5)) {
				leftwards(1);
				cout<< "What equipment slot do you want to unequip (1-5)? \n";
				cin>>switchSlot;
			}
		}
		if ((switchSlot > 0) & (switchSlot <= 5)) {
			int index = switchSlot;
			if (switchSlot == 5) {
				while ((index<1) | (index>4)) {
					leftwards(1);
					cout<< "What amulet slot do you want to equip this to (1-4)? \n";
					cin>>index;
				}
				index+=4;
			}
			item swapItem = equipment[index];
			equipment[index] = inventory[currInv];
			inventory[currInv] = swapItem;
		} 
	} else if (response == 'r') {
		itemList.push_back(inventory[currInv]);
		inventory[currInv] = VOIDITEM;
	}	
	
	//out of bounds
	if (invX > NUMBOXESX - 1)
		invX = NUMBOXESX - 1;
	if (invX < 0)
		invX = 0;
	if (invY > NUMBOXESY - 1)
		invY = NUMBOXESY -1;
	if (invY < 0)
		invY = 0;

}//end of inventory manager
}