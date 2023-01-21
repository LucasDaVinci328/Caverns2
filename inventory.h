#ifndef INVENTORY_H
#define INVENTORY_H

#include "entityNitems.h"
#include <vector>

using namespace std;

void manage_inventory(item inventory[], item equipment[], entity* PLAYER, vector<item> itemList);

#endif
