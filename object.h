#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Object {
	string id;
	string name;
	string whichRoom;
	string description;
	void print();
	Object(string objectId);
};
Object* objectCreate(string objectId);
#endif // OBJECT_H
