#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int intro();
string getInput();
int quit();
int help();
int hit();
int npc_turn();
int move();
int grab();
int drop();
int talk();
int fire();
int examine();
int use();
int wish();
int parseInput(string input);

#endif // PARSER_H
