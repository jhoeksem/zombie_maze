#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string.h>
#include "map.h"
#include "parser.h"
using namespace std;

Map* chunks [MAX_CHUNK_NUM];
Map::Map(string mapId){
    id = mapId;
    string line;
    ifstream myfile ("./chunks/"+mapId+".map");
    isVisited = false;
    description = "";
    postDescription="";
    isCompleted=false;
    if (myfile.is_open()){
        //read in name
        if ( getline (myfile, line)) {
                name = line;
            } else {
                cerr << "File: " << mapId << " is incorrectly formatted\n";
                exit(1);
            } 
            //read in description
        while ( getline (myfile, line) && line != "POST") {
            description += line + '\n';
        }
            //read in description
        while ( getline (myfile, line) && line != "DIRECTIONS") {
            postDescription += line + '\n';
        }
        //read in the adjancent chunks
        for (int i =0; i < 4; i++){
            if ( getline (myfile, line)) {
                if (line[0] == 'b'){
                    isBlocked[i] = true;
                    line = line.substr(8);
                } else {
                    isBlocked[i] = false;
                }
                direction[i] = line;
            } else {
                cerr << "File: " << mapId << " is incorrectly formatted\n";
                exit(1);
            } 
        }
        myfile.close();
    } else{
        cerr << "Error trying to open: " << mapId << endl;
        exit(1);
    }
}
Map* BuildMap(string mapId){
    size_t idLength = mapId.length();
    int chunkNumber = stoi(mapId, &idLength);
    if(chunks[chunkNumber]){
        cerr << "Creating chunk that already exists\n";
        return chunks[chunkNumber];
    }
    Map* mapAddress = new Map(mapId);
    chunks[chunkNumber] = mapAddress;
    for ( int i = 0; i < 4; i++){
        if (mapAddress->direction[i] != "NULL"){
            size_t chunkLength = mapAddress->direction[i].length();
            int adjacentChunkNumber = stoi(mapAddress->direction[i], &chunkLength);
            if( chunks[adjacentChunkNumber]){
                mapAddress->adjacentChunks[i] = chunks[adjacentChunkNumber];
            } else {
                Map* adjacentChunk = BuildMap(mapAddress->direction[i]);
                mapAddress->adjacentChunks[i] = adjacentChunk;
            }
        } else {
            mapAddress -> adjacentChunks[i] = 0;
        }
    }

    return mapAddress;
}

void PopulateMap(){
    //create objects
    // I assume the object files will be named as consecutive integers
    int objectNum = 0;
    Object* object = NULL;
    do{
        object = new Object(to_string(objectNum));
        if(object->id != "-1"){
            size_t stringLen = object->whichRoom.length();
            int roomId = stoi(object->whichRoom, &stringLen);
            if (roomId >=0 && roomId <MAX_CHUNK_NUM && chunks[roomId]){
                chunks[roomId]->objects.push_back(object);
            } else{
                cerr << "Recieved an invalid roomId " << roomId << "For object "<< objectNum << endl;
                exit(1);
            }
        } else{
            break;
        }
    }while(++objectNum);
    int npcNum =0;
    NPC* npc = NULL;
    // create NPCS
    // I assume the npc files will be named as consecutive integers
    do{
        npc = new NPC(to_string(npcNum));
        if(npc->id != "-1"){
            size_t stringLen = npc->whichRoom.length();
            int roomId = stoi(npc->whichRoom, &stringLen);
            if (roomId >=0 && roomId <MAX_CHUNK_NUM && chunks[roomId]){
                chunks[roomId]->npcs.push_back(npc);
            } else{
                cerr << "Recieved an invalid roomId " << roomId << "For object "<< npcNum << endl;
                exit(1);
            }
        } else{
            break;
        }
    }while(++npcNum);
}

NPC* NPCSelector(Map* currentChunk){
    vector <NPC*> aliveNPC;
    for (auto  i = currentChunk->npcs.begin(); i != currentChunk->npcs.end(); i++){
        if((*i) ->health >0){
            aliveNPC.push_back((*i));
        }
    }
    int numNPC = aliveNPC.size();
		if (numNPC > 0){
			cout << "The creature";
			if(numNPC == 1){
				cout <<" you can select is " << aliveNPC[0]->name;
			} else{
				cout << "s you can select are ";
				int count = 0;
				for (auto  i = aliveNPC.begin(); i != aliveNPC.end(); i++){
					if (count < numNPC-1){
	        			cout << (*i)->name << ", ";
					} else{
						cout << "and " << (*i)->name << endl;
					}
					count++;
    			}
			}
			cout << endl;
			string creature = getInput();
			for (auto i = aliveNPC.begin(); i != aliveNPC.end(); i++){
				if ((*i)->name == creature){
					return (*i);
				}
			}
            cout << "There is no one by that name\n";
            return NULL;
		
        } else{
            cout << "There is no one else in the room\n";
            return NULL;
        }
}

Directions getDirection(string input){
    if (input == "north" || input == "n"){
        return NORTH;
    } else if (input == "south" || input == "s"){
        return SOUTH;
    } else if (input == "east" || input == "e") {
        return EAST;
    } else if (input == "west" || input == "w"){
        return WEST;
    } else{
        return DIRECTION_ERROR;
    }
}
string getStringFromDirection(int direction){
    if(direction == EAST){
        return "east";
    } else if(direction == NORTH){
        return "north";
    } else if(direction == WEST){
        return "west";
    } else if(direction == SOUTH){
        return "south";
    } else {
        return "";
    }
}
void Map::printAll(){
        if (isCompleted){
            cout << postDescription << endl;
        }else {
            cout << description << endl;
        }
        printObjectVector(false, objects);
	cout << endl;
        
	// count NPCs
	vector <NPC*> aliveNPC;
	for (auto  i = npcs.begin(); i != npcs.end(); i++){
		if((*i)->health >0){
			aliveNPC.push_back((*i));
		}
	}
	// disp NPCs
	if (aliveNPC.size() <= 0) {
		cout << "You cannot see any signs of life in the clearing." << endl;
	} else {
		cout << "You spot the following characters in the clearing:" << endl;
		for (auto  i = aliveNPC.begin(); i != aliveNPC.end(); i++){
			cout << "A " << (*i)->name << endl;
		}
	}
}
void Map::print(){
    cout << "\e[1m" << name << "\e[0m" << endl;
    if(!isVisited){
        printAll();
    } 
}


void Map::DebugPrintChunk(){
 cout << "Id: " << id <<endl;
 cout << "Name: " << name << endl;
 cout << "Description: " << description<< endl;
 cout << "Post Descrition: " << postDescription << endl;
 cout << "East: " << direction[EAST]<< endl;
 cout << "North: " << direction[NORTH]<< endl;
 cout << "West: " << direction[WEST]<< endl;
 cout << "South: " << direction[SOUTH]<< "\n\n";
    
}
void printMap(Map* map, bool* visited){
    if(!map){
        return;
    }
    size_t length = map->id.length();
    int number = stoi(map->id, &length);
    if ( number >=0 && number < MAX_CHUNK_NUM){
        if (!visited[number]){
            visited[number] = true;
            map->DebugPrintChunk();
            for (int i =0; i< 4; i++){
                printMap(map->adjacentChunks[i], visited);
            }
        }

    } else {
        cerr << "Invalid chunk name found: " << map->id << endl;
        exit(1);
    }
}
int testMap (){
    memset((void*)&chunks, 0, sizeof(chunks));
    Map* map = BuildMap("0");
    bool visited[MAX_CHUNK_NUM];
    memset((void*)&visited, 0, sizeof(visited));
    printMap(map, visited);
    return 0;
}
