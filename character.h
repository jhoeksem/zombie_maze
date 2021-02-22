#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <vector>
#include "object.h"
using namespace std;

struct Character {
	string name;
	string description;
	// health stats
	int health;
	int strength;
        Object inventory[5]; // not sure if this is actually allowed or not. might need to use a vector instead



};

#endif // CHARACTER_H
