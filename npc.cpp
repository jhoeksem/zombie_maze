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