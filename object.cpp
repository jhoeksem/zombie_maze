#include <string>
#include "object.h"
using namespace std;
void Object::print(){
	cout << description << endl;
}

Object::Object(string objectId){
    ifstream myfile ("./objects/"+objectId+".obj");
    if (myfile.is_open()){
		struct Object* object = (struct Object*)malloc(sizeof(struct Object));
		if(!object){
			cerr << "Error in malloc\n";
			exit(1);
		}
		id = objectId;
	    description = "";
		string line;

        //read in id
		if ( getline (myfile, line)) {
			id = line;
		} else {
			cerr << "File: " << objectId << " is incorrectly formatted\n";
			exit(1);
		}
        //read in name
		if ( getline (myfile, line)) {
			name = line;
		} else {
			cerr << "File: " << objectId << " is incorrectly formatted\n";
			exit(1);
		}
        //read in room
		if ( getline (myfile, line)) {
			whichRoom = line;
		} else {
			cerr << "File: " << objectId << " is incorrectly formatted\n";
			exit(1);
		}
        //read in description
		if ( getline (myfile, line)) {
			description = line;
		} else {
			cerr << "File: " << objectId << " is incorrectly formatted\n";
			exit(1);
		}
	//read in damage
		if ( getline (myfile, line)) {
			size_t stringLen = line.length();
		 	damage = stoi(line, &stringLen);
		} else {
			cerr << "File: " << objectId << " is incorrectly formatted\n";
			exit(1);
		}
		myfile.close();
		//return object;
	} else{
		id = "-1";
	}
}

void printObjectVector(bool isInventory, vector <Object*> objects){
	if(isInventory){
		cout << "Your inventory is currently:\n";
		int index = 0;
		for (auto i = objects.begin(); i != objects.end(); i++){
			cout << "Slot " << index <<": " << (*i)->name << endl;
			index++;
		}
	} else {
		if (objects.size() <=0){
			cout << "You cannot see any objects in the clearing." << endl;
		} else{
			cout << "You spot the following objects in the clearing:" << endl;
			for (auto i = objects.begin(); i!= objects.end(); i++){
				cout << (*i)->name << endl;
			}
		}
	}
}
