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

	bool isThreat() {
		if(health > 0 and friendly == false){
			return true;
		}
		else {
			return false;
		}
	}
};
