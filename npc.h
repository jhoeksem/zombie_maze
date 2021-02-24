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
	string talk;
	string deadDescription;
	string whichRoom;
	// combat stats
	int health;
	int strength;
	bool friendly;

	bool isThreat();
	void print();
	NPC(string npcId);
	void talkTo();
};
#endif // NPC_H
