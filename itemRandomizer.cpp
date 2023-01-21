// itemRandomizer.cpp
// Name: Item Randomizer
// Author: Luke Devenney
// Date: 10/17/2021

#include <string>
#include <math.h>
#include <fstream>

#include "entityNitems.h"

using namespace std;

item generateItem(set setList[6], int slot, int quality) {
	const float LUCK = 5.0;

	ifstream inFile;
        
	item newItem;

        if (quality == 0) {
                quality = pow(LUCK, 5.0);
                quality = (log(rand()%quality)/log(LUCK))+1;
		//quality = rand()%5+1;
        }

	newItem.quality = quality;

	if (slot == 0) slot = rand()%5+1;

	string currentInput;
	
	switch (slot) {
		case 1:
			inFile.open("items/head.txt");
			break;
		case 2:
			inFile.open("items/chest.txt");
			break;
		case 3:
			inFile.open("items/offhand.txt");
			break;
		case 4:
			inFile.open("items/righthand.txt");
			break;
		case 5:
		default:
			slot = 5;
			inFile.open("items/amulet.txt");
			break;
	}
	
	if (inFile.fail()) return VOIDITEM;

	newItem.slot = slot;

	int numRows = 0;
	inFile >> numRows;

	int itemIndex = rand()%numRows+1;
	
	for(int i = 0; i < itemIndex; i++) {
		inFile.ignore(1024, '~');
	}
	
	inFile.ignore(256, ':');
	getline(inFile, newItem.name, '\n');

	inFile.ignore(256, ':');
	getline(inFile, newItem.description, '\n');

	inFile.ignore(256, ':');
	getline(inFile, newItem.material, '\n');

	inFile.ignore(256, ':');
	inFile>>newItem.type;

	for (int i = 1; i <= 6; i++) {
		int mod = 0;
		int offset = 0;
		int low = 0;
		int high = 0;

		inFile.ignore(256, ':');
		inFile >> low;
		inFile.ignore(256, ':');
		inFile >> high;
		mod = (high-low)+1;
		offset = low;
		int stat = (mod <= 1)? offset : rand()%mod + offset;
		stat = (stat>0)? stat * ((7-quality) / 4.0) : (stat<0)? stat * ((1+quality) / 4.0) : stat;

		switch (i) {
			case 1:
				newItem.maxHealth = stat;
				break;
			case 2:
				newItem.attack = stat;
				break;
			case 3:
				newItem.defense = stat;
				break;
			case 4:
				newItem.accuracy = stat;
				break;
			case 5:
				newItem.evasion = stat;
				break;
			case 6:
				newItem.range = stat;
				break;
		}
	}
	inFile.close();

	//name decider
	if (newItem.material == "cloth") {
		inFile.open("items/cloth.txt");
	} else if (newItem.material == "metal") {
		inFile.open("items/metal.txt");
	} else {
		return newItem;
	}
	if (inFile.fail()) return newItem;
	
	string nothing;

	for(int i = 0; i < 6-quality; i++)
		inFile.ignore(1024, ':');

	inFile>>itemIndex;
	itemIndex = rand()%itemIndex;

	for(int i = 0; i < itemIndex; i++)
		inFile >> nothing;

	string nameMod;
	inFile>>nameMod;

	if (quality<=3) {
		if (rand()%2==0) {
			if (quality==3) {
				newItem.itemSet = setList[rand()%3];
			} else if (quality==2) {
				newItem.itemSet = setList[rand()%2+3];
			} else if (quality==1) {
				newItem.itemSet = setList[5];
			} else {
				newItem.itemSet = new_set(0, quality);
			}
		} else {
			newItem.itemSet = new_set(0, quality);
		}
		newItem.name = nameMod + " " + newItem.name + " of " + newItem.itemSet.setName;
	} else {
		newItem.name = nameMod + " " + newItem.name;
	}
	
	inFile.close();

	if (newItem.itemSet.setID != 0) newItem.description += " This item is part of a set.";

	return newItem;
}

void generate_sets(set setList[]) {
	for(int i = 0; i < 6; i++) {
		int quality = (i<3)? 3 : (i<5)? 2 : 1;
		setList[i] = new_set(i+1, quality);
	}		

}

set new_set(int setId, int quality) {
	set newSet;
	newSet.setID = setId;
	if (setId==0) quality--;
	newSet.maxHealth = rand()%(5-quality);
	newSet.attack = rand()%(5-quality);
	newSet.defense = rand()%(5-quality);
	newSet.accuracy = rand()%(5-quality);
        newSet.evasion = rand()%(5-quality);
        newSet.range = rand()%(5-quality);
	ifstream inFile;
	inFile.open("items/setNames.txt");
	
	if (inFile.fail()) return newSet;
	
	int itemIndex = 0;
	inFile>>itemIndex;
	itemIndex = rand()%itemIndex;
	
	for(int i = 0; i < itemIndex; i++) {
                string nothing;
                inFile >> nothing;
       	}
	inFile>>newSet.setName;
	return newSet;
}
