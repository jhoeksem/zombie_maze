#include <iostream>
#include <string>
#include "map.h"
#include "character.h"
#include "object.h"

using namespace std;
Map* currentChunk;
string desc = "This character is basically hercules. Super strong and will fight to death";
Character character = Character("John", desc, 100,100);
//Character character
int intro() {
	system("clear"); // creates error at the moment 
	currentChunk = BuildMap("0");
        PopulateMap();
	cout << "Welcome to the ZOMBIE MAZE." << endl;
	PopulateMap();
	ifstream f("intro.txt");
	if(f.is_open()){
		cout << f.rdbuf() << endl;
		f.close();
		string input;
		getline(cin, input);
		system("clear");
	} else{
		cerr << "intro.txt not found. exiting.\n";
		exit(1);
	}
	currentChunk->print();
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

int npc_turn() {
	for (auto i = currentChunk->npcs.begin(); i != currentChunk->npcs.end(); i++){
		cout << "There is an enemy in the room" << endl;
		(*i) -> print();
	}
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
				currentChunk->print();
			} else{
				cout << "That way is blocked.\n";
			}
		}
		else if (input == "north"){
			if (currentChunk->adjacentChunks[NORTH] !=NULL){
				currentChunk = currentChunk->adjacentChunks[NORTH];
				currentChunk->print();
			} else{
				cout << "That way is blocked.\n";
			}
		}
		else if (input == "west"){
			if (currentChunk->adjacentChunks[WEST] !=NULL){
				currentChunk = currentChunk->adjacentChunks[WEST];
				currentChunk->print();
			} else{
				cout << "That way is blocked.\n";
			}
		}
		else if (input == "south"){
			if (currentChunk->adjacentChunks[SOUTH] !=NULL){
				 currentChunk = currentChunk->adjacentChunks[SOUTH];
				currentChunk->print();
			} else{
				cout << "That way is blocked.\n";
			}
		} else{
			cout << "that  is not a valid direction\n";
		}
	} else if(input == "grab"){
                cout << "going to grab the object"<< endl;


                Object empty("empty");
                cout << "passes creation" << endl;
                for(int i = 0; i< 5; i++){
                    string n = empty.id; 
                    string m =  character.inventory[i]->id;
                    cout << m << endl;

                    if(character.inventory[i]->id == empty.id){
                        cout << "passes check" << endl;
                        if(!currentChunk->objects.empty()){
                            character.inventory[i] = currentChunk->objects[0];
                            currentChunk->objects.erase(currentChunk->objects.begin()+ 0);
                            break;
                        }
                    }
                }  
        
	}else if(input == "talk") {
			cout << "Who would you like to talk to?\n";
		
	}
	else {
		cout << "That's not a phrase I'm familiar with" << endl;	
	}
	return 0;
}
