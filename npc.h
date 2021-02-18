#ifndef NPC_H
#define NPC_H
#include <string>
using namespace std;

struct NPC {
	string id;
	string name;
	string description;
	string whichRoom;
	// combat stats
	int health;
	int strength;
	bool friendly;

	bool isThreat();
};

#endif // NPC_H
