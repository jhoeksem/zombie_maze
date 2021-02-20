#ifndef NPC_H
#define NPC_H
#include <string>
#include <iostream>
#include <fstream>
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
	void print();
	NPC(string npcId);
};
#endif // NPC_H
