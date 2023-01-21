// enemyRand.cpp
// Name: Item Randomizer
// Author: Luke Devenney
// Date: 10/17/2021

#include <string>
#include <math.h>
#include <fstream>
#include <iostream>

#include "cavegrowth.h"
#include "entityNitems.h"
#include "constants.h"

using namespace std;

string randAdject(string type) {
	string adject = "cave";
	ifstream fin;
	fin.open("enemies/adjectives.txt");
	if (fin.fail()) return adject;
	
	bool typeFound = 0;
	if (type=="size") typeFound = 1;
	if (type=="color") typeFound = 1;
	if (type=="shape") typeFound = 1;
	if (type=="texture") typeFound = 1;
	if (type=="look") typeFound = 1;
	if (type=="personality") typeFound = 1;
	if (type=="sound") typeFound = 1;

	if (!typeFound) return adject;
	typeFound = 0;
	while (!typeFound) {
		fin.ignore(1048576, ':');
		string typeTest;
		fin>>typeTest;
		if (typeTest == type) typeFound = 1;
	}
	fin.ignore(256, ':');
	int index;
	fin>>index;
	index = rand()%index+1;
	for(int i = 0; i<index; i++)
		fin>>adject;
	return adject;
}

string randName() {
	string name = "critter";
	ifstream fin;
	fin.open("enemies/names.txt");
	if (fin.fail()) return name;
	int index;
	fin>>index;
	index = rand()%index+1;
	for(int i =0; i<index; i++)
		fin>>name;
	int nameModSelect = rand()%7;
	string nameMod;
	switch (nameModSelect) {
		case 0:
			nameMod = randAdject("color");
			break;
		case 1:
			nameMod = randAdject("personality");
			break;
		case 2:
			nameMod = randAdject("size");
			break;
		case 3:
			nameMod = randAdject("sound");
			break;
		case 4:
			if(name.length()<10) nameMod = randName();
			break;
	}
	string emptyStr;
	if (nameMod!=emptyStr) name = nameMod + " " + name;
	return name;
}

attribute generate_attribute() {
	attribute newAttr;
	ifstream fin;
	fin.open("enemies/attributes.txt");
	if (fin.fail()) return newAttr;
	int numRows = 0;
	fin>>numRows;
	int index = rand()%numRows+1;
	
	for(int i = 0; i < index; i++) {
		fin.ignore(1024, '~');
	}

	fin.ignore(256, ':');
	getline(fin, newAttr.name, '\n');
	int typeAdject = rand()%4;
	string typeAdjectStr;
	switch (typeAdject) {
		case 0:
			typeAdjectStr = "color";
			break;
		case 1:
			typeAdjectStr = "shape";
			break;
		case 2:
			typeAdjectStr = "texture";
			break;
		default:
			typeAdjectStr = "color";
	}
	if (rand()%5==0) newAttr.name = randAdject(typeAdjectStr) + " " + newAttr.name;

	fin.ignore(256, ':');
	getline(fin, newAttr.limb, '\n');

	int quality = rand()%5+1;
	for (int i = 1; i <= 7; i++) {
		int mod = 0;
		int offset = 0;
		int low = 0;
		int high = 0;

		fin.ignore(256, ':');
		fin >> low;
		fin.ignore(256, ':');
		fin >> high;
		mod = (high-low)+1;
		offset = low;
		int stat = (mod <= 1)? offset : rand()%mod + offset;
		stat = (stat>0)? stat * ((7-quality) / 4.0) : (stat<0)? stat * ((1+quality) / 4.0) : stat;

		switch (i) {
			case 1:
				newAttr.maxHealth = stat;
				break;
			case 2:
				newAttr.attack = stat;
				break;
			case 3:
				newAttr.defense = stat;
				break;
			case 4:
				newAttr.accuracy = stat;
				break;
			case 5:
				newAttr.evasion = stat;
				break;
			case 6:
				newAttr.range = stat;
				break;
			case 7:
				newAttr.jumping = stat;
				break;
		}
	}

	fin.ignore(256, '?');
	int climbing = 0;
	fin>>climbing;
	newAttr.climbing = (climbing==1)? 1 : 0;

	fin.ignore(256, '?');
	int flying = 0;
	fin>>flying;
	newAttr.flying = (flying==1)? 1 : 0;

	fin.close();
	return newAttr;
}

species generate_species(int difficulty) {
	species newSpecies;
	if (difficulty == 0) difficulty = rand()%5 + rand()%6 + 1;
	if (difficulty == 1) {
		newSpecies.aiType = 1;
		newSpecies.DEFAULT_HEALTH = rand()%10+10;
		for (int j = 0; j < NUMSPECIES; j++)
			newSpecies.allegiance[j] = 1;
	} else if (difficulty == 10) {
		newSpecies.aiType = 3;
		for (int j = 0; j < NUMSPECIES; j++)
			newSpecies.allegiance[j] = 0;
	} else {
		newSpecies.aiType = rand()%3+1;
		for (int j = 0; j < NUMSPECIES; j++)
			newSpecies.allegiance[j] = rand()%2;
	}
	
	newSpecies.DEFAULT_HEALTH+=rand()%difficulty+difficulty;
	newSpecies.DEFAULT_ATTACK+=rand()%difficulty+difficulty;
	newSpecies.DEFAULT_DEFENSE+=rand()%difficulty+difficulty;
	newSpecies.DEFAULT_ACC+=rand()%difficulty+difficulty;
	newSpecies.DEFAULT_EVADE+=rand()%difficulty+difficulty;
	newSpecies.DEFAULT_RANGE+=rand()%difficulty+difficulty;

	int numAttributes = difficulty+rand()%difficulty;
	for (int j = 0; j < numAttributes; j++) {
		newSpecies.speciesAttr[j] = generate_attribute();
		newSpecies.description += "It has " + newSpecies.speciesAttr[j].name + " on its " + newSpecies.speciesAttr[j].limb + ". ";
	}
	
	newSpecies.name = randName();
	return newSpecies;
}	

void generate_species_list(species speciesList[]) {
	for (int i = 0; i < NUMSPECIES; i++) {
		if (i == 0) {
			speciesList[i] = generate_species(1);
		} else if (i == NUMSPECIES-1) {
			speciesList[i] = generate_species(10);
		} else {
			speciesList[i] = generate_species();
			speciesList[i].allegiance[i] = (rand()%15==0)?0 : 1;
		}
	}
}

void generate_enemy(vector<entity> &enemies, block screen[HEIGHT][WIDTH], species speciesList[], int camX, set setList[6]) {
	bool enemySpawned = 0;
	bool validSpawns = 1;
	entity newEnemy;
	while (!enemySpawned&validSpawns) {
		validSpawns = 0;
		for (int y = HEIGHT-1; y > 0; y--) {
			for (int x = 0; x < WIDTH-1; x++) {
				if (((screen[y][x].collision==0) && (screen[y-1][x].collision==1)) && (!enemySpawned)) {
					validSpawns = 1;
					if (rand()%10==0) {
						newEnemy.speciesId = rand()%NUMSPECIES;
						enemySpawned = 1;
						newEnemy.x = x + camX;
						newEnemy.y = y;
						string selector;
						switch(rand()%6) {
							case 0:
								selector = "size";
								break;
							case 1:
								selector = "personality";
								break;
							case 2:
								selector = "look";
								break;
							default:
								selector = "nothing";
						}
						string adject = (selector!="nothing")? randAdject(selector) + " ": "";
						newEnemy.name = adject + speciesList[newEnemy.speciesId].name;
						if (speciesList[newEnemy.speciesId].equipment) {
							for (int i = 1; i <=5; i++) {
								if (rand()%3==0) newEnemy.equipment[i] = generateItem(setList, i);
							}
						}
						newEnemy.change_base_stats('H', speciesList[newEnemy.speciesId].DEFAULT_HEALTH);
						newEnemy.change_base_stats('A', speciesList[newEnemy.speciesId].DEFAULT_ATTACK);
						newEnemy.change_base_stats('D', speciesList[newEnemy.speciesId].DEFAULT_DEFENSE);
						newEnemy.change_base_stats('C', speciesList[newEnemy.speciesId].DEFAULT_ACC);
						newEnemy.change_base_stats('E', speciesList[newEnemy.speciesId].DEFAULT_EVADE);
						newEnemy.change_base_stats('R', speciesList[newEnemy.speciesId].DEFAULT_RANGE);
						newEnemy.jumpMax += speciesList[newEnemy.speciesId].JUMPMAX;
						newEnemy.climbing = speciesList[newEnemy.speciesId].climbing;
						newEnemy.flying = speciesList[newEnemy.speciesId].flying;
					}
				}
			}
		}
	}
	newEnemy.update_stats();
	newEnemy.health = newEnemy.maxHealth;
	enemies.push_back(newEnemy);
};
	
	