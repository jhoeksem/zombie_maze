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
		parseInput(input);
		npc_turn();
		
		input = getInput();
	}
	
	quit();

	return 0;
}
