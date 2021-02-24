#include <string>
#include "character.h"
#include "object.h"
using namespace std;

Character::Character(string n, string d, int h, int s){
    name = n;
    description = d;
    health = h; 
    strength = s;
    Object* empty = new Object("-1");
    for(int i =0; i < 5; i++){
        inventory.push_back(empty);
    }
}

