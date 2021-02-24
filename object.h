#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Object {
	string id;
	string name;
	string whichRoom;
	string description;
	int damage; 
	void print();
	Object(string objectId);
};
Object* objectCreate(string objectId);
//isInventory: true if inventory, false if on ground
void printObjectVector(bool isInventory, vector <Object*> objects);
#endif // OBJECT_H
