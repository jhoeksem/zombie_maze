#include "object.h"
#include "parser.h"
using namespace std;

int main() {
	string input;
	Object pebble;
	pebble.description = "A small, round pebble. It sits nicely in the palm of your hand.";

	intro();
	input = getInput();

	while (input != "quit") {
		parseInput(input);
		input = getInput();
	}
	
	quit();

	return 0;
}
