#include "parser.h"
#include "object.h"
#include "npc.h"
using namespace std;

int main() {
	string input;
	Object pebble;
	pebble.description = "A small, round pebble. It sits nicely in the palm of your hand.";

	NPC zombie_1;
	zombie_1.friendly = false;
	zombie_1.health = 5;
	bool threat = zombie_1.isThreat();

	intro();
	input = getInput();

	while (input != "quit") {
		parseInput(input);
		input = getInput();
	}
	
	quit();

	return 0;
}
