#ifndef ENTITYNITEMS_DEF
#define ENTITYNITEMS_DEF

#include <string>
#include <vector>

#include "cavegrowth.h"

using namespace std;

class set {
	public:
	int setID = 0;
	string setName;
	int maxHealth = 0;
        int attack = 0;
        int defense = 0;
        int accuracy = 0;
        int evasion = 0;
        int range = 0;
};

set new_set(int setId, int quality);

void generate_sets(set setList[]);

class item {
        public:
        int x = 0;
        int y = 0;

        string name;
        string description;
	string material;

        int slot = 0;
        int type = 0;
        int quality = 0;

        int maxHealth = 0;
        int attack = 0;
        int defense = 0;
        int accuracy = 0;
        int evasion = 0;
	int range = 0;

	set itemSet;
	int Hp(float setBonus = 1) {
		return (maxHealth + (setBonus*itemSet.maxHealth));
	}
	int At(float setBonus = 1) {
		return (attack + (setBonus*itemSet.attack));
	}
	int De(float setBonus = 1) {
		return (defense + (setBonus*itemSet.defense));
	}
	int Ac(float setBonus = 1) {
		return (accuracy + (setBonus*itemSet.accuracy));
	}
	int Ev(float setBonus = 1) {
		return (evasion + (setBonus*itemSet.evasion));
	}
	int Ra(float setBonus = 1) {
		return (range + (setBonus*itemSet.range));
	}
};

const item VOIDITEM;

class attribute {
	public:
	int maxHealth = 0;
	int attack = 0;
	int defense = 0;
	int accuracy = 0;
	int evasion = 0;
	int range = 0;
	int jumping = 0;

	bool flying = 0;
	bool climbing = 0;

	string limb;

	string name;
};	

string randAdject(string type);

attribute generate_attribute();

class species {
	public:
	int DEFAULT_HEALTH = 0;
	int DEFAULT_ATTACK = 0;
	int DEFAULT_DEFENSE = 0;
	int DEFAULT_ACC = 0;
	int DEFAULT_EVADE = 0;
	int DEFAULT_RANGE = 0;
	int JUMPMAX = 0;

	int aiType = 0;

	bool flying = 0;
	bool climbing = 0;
	bool equipment = 0;

	bool discovered = 0;

	string name;
	string description;

	attribute speciesAttr[20];	

	int difficulty = 0;

	bool allegiance[NUMSPECIES] = {0};
};

species generate_species(int difficulty = 0);

void generate_species_list(species speciesList[]);

class entity {
	int DEFAULT_HEALTH = 0;
	int DEFAULT_ATTACK = 0;
	int DEFAULT_DEFENSE = 0;
	int DEFAULT_ACC = 0;
	int DEFAULT_EVADE = 0;
	int DEFAULT_RANGE = 0;

	public:
	int x = 0;
	int y = 0;
	string name;
	
	int health = 0;
	int maxHealth = 0;
	int attack = 0;
	int defense = 0;
	int accuracy = 0;
	int evasion = 0;
	int range = 0;
	int jumping = 0;
	
	int direction = 1;

	int jumpMax = 1;

	bool flying = 0;
	bool climbing = 0;

	int speciesId = 0;

	item equipment[9];
	float setBonus = 1;

	void standard_attack(block screen[][WIDTH], int camX, entity player, vector<entity> &enemyList);
	void move(block screen[][WIDTH], int chunkX, int changeX, int changeY = 0);
	void change_base_stats(char stat, int newAmount);
	void update_stats();
	void damage(int damage, int accuracy);
	void ai(block screen[][WIDTH], entity player, species speciesList[NUMSPECIES], int camX);
};

void generate_enemy(vector<entity> &enemies, block screen[HEIGHT][WIDTH], species speciesList[], int camX, set setList[6]);

item generateItem(set setList[6], int slot = 0, int quality = 0);

#endif
