#include <string>
#include "character.h"
#include "object.h"
using namespace std;

Character::Character(string n, string d, int h, int s){
    name = n;
    description = d;
    max_health = h;
    health = h; 
    strength = s;
    Object* empty = new Object("-1");
    for(int i =0; i < 5; i++){
        inventory.push_back(empty);
    }
}

int Character::decrement_health( int damage ){
	if (health - damage < 0) {
		health = 0;
	} else {
		health -= damage;
	}
	return 0;
}

int Character::increment_health( int healing ){
	if (health + healing > max_health) {
		health = max_health;
	} else {
		health += healing;
	}
	return 0;
}

string Character::health_status() {
	if ( health > 3 * max_health / 4 ){
		return "You are in strong health.";
	} else if ( health > max_health / 2 ){
		return "You have visible cuts and bruises.";
	} else if ( health > max_health / 4 ){
		return "You've taken heavy damage.";
	} else {
		return "You're knocking on death's door.";
	}
}
