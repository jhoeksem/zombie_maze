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
        vector <Object*> inventory; // vector of object pointers
        Character(string name, string description, int health ,int strength);

};



#endif // CHARACTER_H
