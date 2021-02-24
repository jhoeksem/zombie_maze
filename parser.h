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
int parseInput(string input);

#endif // PARSER_H
