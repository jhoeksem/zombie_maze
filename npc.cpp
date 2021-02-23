#include <string>
#include "npc.h"
using namespace std;


	bool NPC::isThreat() {
		if(health > 0 and friendly == false){
			return true;
		}
		else {
			return false;
		}
	}

	void NPC::print(){
		//TODO add logic to print different things depending on state (dead, passified, agressive etc)
		cout << description << endl;
	}

	NPC::NPC(string npcId){
	ifstream myfile ("./npcs/"+npcId+".npc");
    if (myfile.is_open()){
		struct NPC* npc = (struct NPC*)malloc(sizeof(struct NPC));
		if(!npc){
			cerr << "Error in malloc\n";
			exit(1);
		}
		id = npcId;
	    description = "";
		string line;
        //read in id
		if ( getline (myfile, line)) {
			id = line;
		} else {
			cerr << "File: " << npcId << " is incorrectly formatted\n";
			exit(1);
		}
        //read in name
		if ( getline (myfile, line)) {
			name = line;
		} else {
			cerr << "File: " << npcId << " is incorrectly formatted\n";
			exit(1);
		}
        //read in room
		if ( getline (myfile, line)) {
			whichRoom = line;
		} else {
			cerr << "File: " << npcId << " is incorrectly formatted\n";
			exit(1);
		}
        //read in description
		if ( getline (myfile, line)) {
			description = line;
		} else {
			cerr << "File: " << npcId << " is incorrectly formatted\n";
			exit(1);
		}
        //read in health
		if ( getline (myfile, line)) {
			size_t stringLen = line.length();
            		health = stoi(line, &stringLen);
		} else {
			cerr << "File: " << npcId << " is incorrectly formatted\n";
			exit(1);
		}
        //read in strength
		if ( getline (myfile, line)) {
			size_t stringLen = line.length();
            strength = stoi(line, &stringLen);
		} else {
			cerr << "File: " << npcId << " is incorrectly formatted\n";
			exit(1);
		}
		friendly = false;
		myfile.close();
	} else{
		id = "-1";
	}
}
