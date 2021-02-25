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

void endgame(string endingType){
	ifstream f("endings/"+endingType+".txt");
	if(f.is_open()){
		cout << f.rdbuf() << endl;
		f.close();
	} else{
		ifstream f2("endings/good.txt");
		if(f2.is_open()){
			cout << f2.rdbuf() << endl;
			f.close();
		}
	}
	exit(0);
}

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
	cout << "Even the strongest sometimes require aid." << endl;
	cout << endl;
	cout << "\e[1mCommon commands:\e[0m" << endl;
	cout << "help\t(h)" << endl;
	cout << "\tprints help screen with list of commands." << endl;
	cout << "quit\t(q)" << endl;
	cout << "\texit the game." << endl;
	cout << "move\t(m)" << endl;
	cout << "\tallows user to navigate the rooms of the maze." << endl;
	cout << "\tcommand will prompt user to state direction of movement." << endl;
	cout << "\tthe possible direction are north (n), south (s), east (e), or west (w)" << endl;
	cout << "hit\t(x)" << endl;
	cout << "\tallows user to attack a NPC with an item." << endl;
	cout << "\tcommand will prompt user to state target from list." << endl;
	cout << "\tcommand will then prompt user to give the index of the item they want to use. <see inventory for options>" <<endl;
	cout << "grab\t(g)" << endl;
	cout << "\tpicks up the first item on the ground." << endl;
	cout << "drop\t(d)" << endl;
	cout << "\tallows user to drop an item from the inventory onto ground." << endl;
	cout << "\tcommand will prompt user to select the index of the item they wish to drop." << endl;
	cout << "examine\t(e)" << endl;
	cout << "\tallows user to see a description of any npc or item on the ground or inventory." << endl;
	cout << "\tcommand will prompt user for the name of the item they wish to examine." << endl;
	cout << "look\t(l)" << endl;
	cout << "\tallows the user to see all of the information of the current room." << endl;
	cout << "talk\t(t)" <<endl;
	cout << "\tallows the user to talk to an NPC and receive some text." << endl;
	cout << "\tcommand will prompt user for the name of the npc they wish to talk to." << endl;
	cout << "inventory (i)" <<endl;
	cout << "\tallows user to see the names of items in the inventory." << endl;
	cout << "paths\t(p)" << endl;
	cout << "\tprints out the current paths in the room." << endl;
	cout << "use\t(u)" << endl;
	cout << "\tallows user to use item for a purpose." << endl;
	cout << "\tcertain items do something in the right situation." << endl;
	return 0;
}

int hit() {
	NPC* npc = NPCSelector(currentChunk);
	if(npc == NULL){
		return 0;
	} else {
		cout << "Which object would you like to hit them with? (specify index of object in inventory, or -1 for fists)" << endl;
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
	if (character.health <=0){
		endgame("dead");
	}
	return 0;
}

int move() {
	cout << "Which cardinal direction would you like to move?" << endl;
	string input = getInput();
	int suggestedDirection = getDirection(input);
	if (suggestedDirection == DIRECTION_ERROR){
		cout << "That  is not a valid direction\n";
	} else {
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
		} else {
			cout << "That way is blocked. I wonder if there's a way to open it?\n";
		}
	}
	return 0;
}

int grab() {
	Object empty("-1");
	int n= 0;
	for(int i = 0; i< 5; i++){
		 if(character.inventory[i]->id == empty.id){
			 if(!currentChunk->objects.empty()){
				 character.inventory[i] = currentChunk->objects[0];
				 currentChunk->objects.erase(currentChunk->objects.begin()+ 0);
				 cout << "You have grabbed the " << character.inventory[i]->name << "." << endl;
				 break;
			 }
			 cout<< "There are no objects to grab here." << endl;
			 break;
		 }
		 n++;

		 if(n == 5){
			 cout << "Your inventory is full.\n Drop an item if you wish to pick up another." << endl;
		 }
	}
	return 0;
}

int drop() {
	cout << "What's the index of the item you want to drop?" << endl;
	int input = stoi(getInput());
	if(input < 5 && input >= 0 && character.inventory[input]->id != "-1"){
		currentChunk->objects.push_back(character.inventory[input]);
		character.inventory.erase(character.inventory.begin() + input);
		Object* empty = new Object("-1");
		character.inventory.push_back(empty);
		cout << "You have dropped the "<< currentChunk->objects.back()->name << "." << endl;
	} else {
		cout << "This is not a valid index" << endl;
	}
	return 0;
}

int talk() {
	cout << "Who would you like to talk to?\n";
	NPC* npc = NPCSelector(currentChunk);
	if(npc != NULL){
		npc->talkTo();
	}
	return 0;
}

int fire() {
	if (currentChunk->id == "2" && currentChunk->isBlocked[1]){
		cout << "You light a fire by the fog, and it immediately disapates, opening up the path to the north\n";
		currentChunk->isBlocked[1] = false;
		currentChunk->isCompleted = true;
	} else {
		cout << "You start gathering kindling and tinder to start a fire, but question why you need one in the first place, and stop.\n";
	}
	return 0;
}

void paths(){
	int count = 0;
	for (int i = 0; i < 4; i ++){
		if (currentChunk->adjacentChunks[i] != NULL){
			count++;
				cout << "The " << getStringFromDirection(i) << " path";
			if (currentChunk->isBlocked[i]){
				cout << " is currently blocked." << endl;
			} else{
				cout << " is open." << endl;
			}
		}
	}
	if(count <= 0){
		cout << "You are trapped in the room with no paths out of it." << endl;
	}
}

int examine() {
		cout << "Which item or npc would you like to examine?\n";
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
		for (auto i = currentChunk->npcs.begin(); i != currentChunk->npcs.end(); i++){
			if (input == (*i)->name){
				cout << "You examine the " << (*i) ->name << ".\n";
				cout << (*i)->description << endl;
				return 0;
			}
		}
		cout << "You could not find " << input << " to examine.\n";
	return 0;
}

int use() {
                if((currentChunk->id == "6" && currentChunk->isBlocked[1]) || (currentChunk->id == "7" && currentChunk->isBlocked[0])){
                    cout << "Which item would you like to use?"<< endl;
                    string input = getInput();
                    if(currentChunk->id =="6" && (input == "rock")){
                        currentChunk->isBlocked[NORTH] = false;
                        currentChunk->isCompleted = true;
                        cout << "You used the rock to break the glass\nThe window is now open for you" <<endl;
                        return 0;
                    }else if(currentChunk->id == "7" && (input == "key")){
                        currentChunk->isBlocked[EAST] = false;
                        currentChunk->isCompleted = true;
                        cout << "You used the key to open the basement door\nThe door is now open for you" <<endl;
                        return 0;
                        

                    }
                
                    cout << "Nothing by that name here" << endl;
                }else{
                    cout << "Nothing to use here. Perhaps try grabbing it" << endl;

                }
	return 0;
}

int wish() {
		if (currentChunk->id != "5"){
			cout << "You look up at the sky and see a shooting star. You state your deepest wish in your heart and hope it comes true." << endl;
		} else if (currentChunk->npcs[0]->health <= 0){
			endgame("worst");
		} else if (currentChunk->npcs[0]->relationship_status == "enemy"){
			cout << "You try to ask the fairy to grant your wish, but she is too busy trying to kill you to listen." << endl;
		} else{
			cout << "Tell me brave child, what do you wish for more than anything else?" << endl;
			string input = getInput();
			if(input == "money"){
				cout << "The fairy reaches into her pocket and hands you her loose change, and says \"dont spend it all in one place.\"" << endl;
			}else if (input == "power"){
				cout << "The fairy proclaims that you are now the leader of the official Great Fairy Fan Club™, with over 10 members. You have the power over running the whole club." << endl;
			} else if (input == "fame"){
				cout << "The fairy gives you an Official Zombie Maze™ Conquerer Certificate to show off at pubs for fame. It even comes complete with a coupon to a local tavern for a free meal and drink, though it expired over 600 years ago." << endl;
			} else if (input == "kill the lich"){
				endgame("best");
			} else{
				cout << "The fairy nods and grants your wish." << endl;
			}
		}
		endgame("good");
	return 0;
}

int parseInput(string input) {
	if (input == "help" || input == "h") {
		help();
	} else if (input == "hit" || input == "x"){
		hit();
	} else if (input == "move" || input == "m"){
		move();
	} else if (input == "look" || input == "l"){
		cout << "\e[1m" << currentChunk->name << "\e[0m" << endl; 
		currentChunk->printAll();
	} else if(input == "grab" || input == "g"){
		grab();
        }else if(input =="drop" || input == "d"){
		drop();
	}else if(input == "talk" || input == "t") {
		talk();
	}  else if (input == "fire"){
		fire();
	} else if (input == "examine" || input == "e"){
		examine();
	}else if (input == "inventory" || input == "i"){
		printObjectVector(true, character.inventory);
	}else if(input == "use" || input == "u"){
		use();
	} else if (input == "paths" || input == "p"){
		paths();
	} else if (input == "wish"){
		wish();
	} 
	else {
		cout << "That's not a command I'm familiar with" << endl;	
	}
	return 0;
}
