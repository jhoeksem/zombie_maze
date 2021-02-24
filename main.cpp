#include "parser.h"
#include "object.h"
#include "npc.h"
#include "map.h"
using namespace std;

int main() {
	string input;
	
	intro();
	input = getInput();

	while (input != "quit") {
		npc_turn();
		parseInput(input);
		input = getInput();
	}
	
	quit();

	return 0;
}
