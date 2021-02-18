#include <iostream>
#include <string>
#include "map.h"
using namespace std;
Map* currentChunk;

int intro() {
	system("clear"); // creates error at the moment 
	currentChunk = BuildMap("0");
	cout << "Welcome to the ZOMBIE MAZE." << endl;
	cout << currentChunk->description << endl;
	return 0;
}

string getInput() {
	string input;
	cout << "> ";
	getline(cin, input);
	return input;
}

int quit() {
	cout << endl;
	cout << "Until next time." << endl;
	cout << endl;
	return 0;
}

int help() {

	cout << endl;
	cout << "Even the strongest sometimes require aid." << endl;
	cout << endl;
	cout << "These are the commands you may use:" << endl;
	cout << "help" << endl;
	cout << "\tprints help screen with list of commands." << endl;
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
	} else if (input == "move"){
		cout << "Which cardinal direction would you like to move?" << endl;
		string input = getInput();	
		if (input == "east"){
			if (currentChunk->adjacentChunks[EAST] !=NULL){
				currentChunk = currentChunk->adjacentChunks[EAST];
				cout << currentChunk->description << endl;
			} else{
				cout << "That way is blocked.\n";
			}
		}
		else if (input == "north"){
			if (currentChunk->adjacentChunks[NORTH] !=NULL){
				currentChunk = currentChunk->adjacentChunks[NORTH];
				cout << currentChunk->description << endl;
			} else{
				cout << "That way is blocked.\n";
			}
		}
		else if (input == "west"){
			if (currentChunk->adjacentChunks[WEST] !=NULL){
				currentChunk = currentChunk->adjacentChunks[WEST];
				cout << currentChunk->description << endl;
			} else{
				cout << "That way is blocked.\n";
			}
		}
		else if (input == "south"){
			if (currentChunk->adjacentChunks[SOUTH] !=NULL){
				 currentChunk = currentChunk->adjacentChunks[SOUTH];
				cout << currentChunk->description << endl;
			} else{
				cout << "That way is blocked.\n";
			}
		} else{
			cout << "that  is not a valid direction\n";
		}
	}
	else {
		cout << "That's not a phrase I'm familiar with" << endl;	
	}
	return 0;
}
