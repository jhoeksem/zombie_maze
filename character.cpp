#include <string>
#include "character.h"
using namespace std;

Character::Character(string n, string d, int h, int s){
    name = n;
    description = d;
    health = h; 
    strength = s;
    for(int i =0; i < 5; i++){
        inventory[i] = "empty";
    }
}


