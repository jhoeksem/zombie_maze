#include <iostream>
using namespace std;

int intro() {
	system("clear");
	cout << "Welcome to the ZOMBIE MAZE." << endl;
	return 0;
}

string getInput() {
	string input;
	cout << "> ";
	getline(cin, input);
	return input;
}

int help() {

	cout << endl;
	cout << "Even the strongest sometimes require aid." << endl;
	cout << endl;
	cout << "These are the commands you may use:" << endl;
	cout << "help" << endl;
	cout << "\treturns help screen with list of commands." << endl;
	cout << "quit" << endl;
	cout << "\texit the game." << endl;
	cout << "move" << endl;
	cout << "\tallows user to navigate the rooms of the maze." << endl;
	cout << "\tcommand will prompt user to state direction of movement." << endl;
	cout << "\tthe set of choices is [EAST|NORTH|WEST|SOUTH]." << endl;
	return 0;
}

int parseInput(string input) {
	if (input == "help") {
		help();
	}
	else {
		cout << "command recognized" << endl;	
	}
	return 0;
}

int main() {
	string input;

	intro();
	input = getInput();

	while (input != "quit") {
		parseInput(input);
		input = getInput();
	}
	
	cout << endl << "Until next time." << endl << endl;

	return 0;
}
