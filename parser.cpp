#include <iostream>
#include <string>
#include <cstdlib>
#include "map.h"
#include "character.h"
#include "object.h"

using namespace std;
Map* currentChunk;
string desc = "This character is basically hercules. Super strong and will fight to death";
Character character = Character("Zahm Bee", desc, 100,100);
int doorEntered = 0;
int base_damage = 3;

//Character character
int intro() {
	system("clear"); // creates error at the moment 
	currentChunk = BuildMap("0");
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
	cout << endl << "[❓]\t";
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
	cout << "hit" << endl;
	cout << "\tallows user to attack enemies in the room." << endl;
	cout << "\tcommand will prompt user to state target from list." << endl;
	cout << "\tcommand will then prompt user to give the index of the item they want to use. <see inventory for options>" <<endl;
	cout << "grab" << endl;
	cout << "\tpicks up the first item on the ground." << endl;
	cout << "drop" << endl;
	cout << "\tallows user to drop an item from the inventory onto ground." << endl;
	cout << "\tcommand will prompt user to select the index of the item they wish to drop." << endl;
	cout << "examine" << endl;
	cout << "\tallows user to see a description of any item on the ground or inventory." << endl;
	cout << "\tcommand will prompt user for the name of the item they wish to examine." << endl;
	cout << "look" << endl;
	cout << "\tallows the user to see all of the information of the current room." << endl;
	cout << "talk" <<endl;
	cout << "\tallows the user to talk to an NPC and receive some text." << endl;
	cout << "\tcommand will prompt user for the name of the npc they wish to talk to." << endl;
	cout << "inventory" <<endl;
	cout << "\tallows user to see the names of items in the inventory" << endl;
	return 0;
}

int hit() {
	NPC* npc = NPCSelector(currentChunk);
	if(npc == NULL){
		return 0;
	} else {
		cout << "Which object would you like to hit them with? (specify index of object in inventory, or -1 for fists)";
		int input = stoi(getInput());
		if ( input == -1 ){
			npc->relationship_status = "enemy";	
			npc->health -= base_damage;
			cout << "[⚔️ ]\tYou hit the " << npc->name << " with your fist for " << base_damage << " damage." << endl;
		} else if(input < 5 && input >= 0 && character.inventory[input]->id != "-1"){
			npc->relationship_status = "enemy";
			npc->health -= character.inventory[input]->damage;
			cout << "[⚔️ ]\tYou hit the " << npc->name << " with the " << character.inventory[input]->name << " for " << character.inventory[input]->damage << " damage." << endl;
		} else {
			cout << "That is not a valid object" << endl;
		}
		if (npc->health <= 0){
			cout << "[⚔️ ]\t" << npc-> name << " is now dead.\n";
		}
		return 0;
	}
}

int npc_turn() {
	for (auto i = currentChunk->npcs.begin(); i != currentChunk->npcs.end(); i++){
		// if enemy is an enemy, it attacks
		if ( (*i)->relationship_status == "enemy" && (*i)->health > 0){
			int random = rand() % 100 + 1;
			int enemy_acc = (*i)->accuracy;
			if ( enemy_acc >= random ){
				character.decrement_health((*i)->strength);
				cout << "[⚔️ ]\tThe " << (*i)->name << " attacked you and dealt " << (*i)->strength << " damage!" << endl;
			} else {
				cout << "[⚔️ ]\tThe " << (*i)->name << " attacked you, but stumbled and missed!" << endl;
			}
		}
	}
	return 0;
}

int parseInput(string input) {
	if (input == "help") {
		help();
	} else if (input == "hit"){
		hit();
	} else if (input == "move"){
		cout << "Which cardinal direction would you like to move?" << endl;
		string input = getInput();	
		int suggestedDirection = getDirection(input);
		if (suggestedDirection == DIRECTION_ERROR){
			cout << "That  is not a valid direction\n";
		} else{
			if (currentChunk->adjacentChunks[suggestedDirection] !=NULL && !(currentChunk->isBlocked[suggestedDirection])){
				if(suggestedDirection != doorEntered){
					for (auto i = currentChunk->npcs.begin(); i != currentChunk->npcs.end(); i++){
						if ((*i)->health >0 && (*i)->relationship_status != "friend"){
							cout << "There is someone blocking your path.\n";
							return 0;
						}
					}
				}
				doorEntered = (suggestedDirection +2)%4; // this notes the door entered into the new room(if you walk north you enter the south door)
				currentChunk->isVisited = true;
				currentChunk = currentChunk->adjacentChunks[suggestedDirection];
				currentChunk->print();
			} else{
				cout << "That way is blocked.\n";
			}
		}
	} else if (input == "look"){
		currentChunk->printAll();
	} else if(input == "grab"){

                Object empty("-1");
                int n= 0;
                for(int i = 0; i< 5; i++){

                    if(character.inventory[i]->id == empty.id){
                        if(!currentChunk->objects.empty()){
                            character.inventory[i] = currentChunk->objects[0];
                            currentChunk->objects.erase(currentChunk->objects.begin()+ 0);
                            cout << "You have grabbed the " << character.inventory[i]->name << endl;;
                            break;
                        }
                        cout<< "No objects to grab here" << endl;
                        break;
                    }
                    n++;
                } 
            
                if(n == 5){
                    cout << "Looks like your inventory is full\n Drop an item and try again" << endl;  
                     
                }

        }else if(input =="drop"){
	    cout << "Name the index of the item you want to drop" << endl;
	    int input = stoi(getInput());	
            if(input < 5 && input >= 0 && character.inventory[input]->id != "-1"){
                currentChunk->objects.push_back(character.inventory[input]);
                character.inventory.erase(character.inventory.begin() + input);
				Object* empty = new Object("-1");
				character.inventory.push_back(empty);
                cout << "You have dropped the "<< currentChunk->objects.back()->name << endl;

            }else{
                cout << "This is not a valid index" << endl;
            }
            


	}else if(input == "talk") {
		cout << "Who would you like to talk to?\n";
		NPC* npc = NPCSelector(currentChunk);
		if(npc != NULL){
			npc->talkTo();
		}		
	}  else if (input == "fire"){
		if (currentChunk->id == "2" && currentChunk->isBlocked[1]){
			cout << "You light a fire by the fog, and it immediately disapates, opening up the path to the north\n";
			currentChunk->isBlocked[1] = false;
			currentChunk->isCompleted = true;
		} else{
			cout << "You start to gather wood to start a fire, but quickly start thinking to yourself, if it is worth the effort.\n";
		}
	} else if (input == "examine"){
		cout << "Which item would you like to examine?\n";
		string input = getInput();
		for (auto i = currentChunk->objects.begin(); i != currentChunk->objects.end(); i++){
			if (input == (*i)->name){
				cout << "You examine the " << (*i) ->name << ".\n";
				cout << (*i)->description << endl;
				return 0;
			}
		}
		for (auto i = character.inventory.begin(); i != character.inventory.end(); i++){
			if (input == (*i)->name){
				cout << "You examine the " << (*i) ->name << ".\n";
				cout << (*i)->description << endl;
				return 0;
			}
		}
		cout << "You could not find " << input << " to examine.\n";
	}else if (input == "inventory"){
		printObjectVector(true, character.inventory);
	}
	else {
		cout << "That's not a phrase I'm familiar with" << endl;	
	}
	return 0;
}
