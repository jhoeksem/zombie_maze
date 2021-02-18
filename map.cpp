#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string.h>
#include "map.h"
using namespace std;

Map* chunks [128];
Map::Map(string mapId){
    id = mapId;
    string line;
    ifstream myfile ("./chunks/"+mapId+".map");
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
                direction[i] = line;
            } else {
                cerr << "File: " << mapId << " is incorrectly formatted\n";
                exit(1);
            } 
        }
        myfile.close();
    } else{
        cerr << "Error trying to open: " << mapId << '\n';
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
void Map::PrintChunk(){
 cout << "Id: " << id <<'\n';
 cout << "Name: " << name << '\n';
 cout << "Description: " << description<< '\n';
 cout << "Post Descrition: " << postDescription << '\n';
 cout << "East: " << direction[EAST]<< '\n';
 cout << "North: " << direction[NORTH]<< '\n';
 cout << "West: " << direction[WEST]<< '\n';
 cout << "South: " << direction[SOUTH]<< "\n\n";
    
}
void printMap(Map* map, bool* visited){
    if(!map){
        return;
    }
    size_t length = map->id.length();
    int number = stoi(map->id, &length);
    if ( number >=0 && number < 128){
        if (!visited[number]){
            visited[number] = true;
            map->PrintChunk();
            for (int i =0; i< 4; i++){
                printMap(map->adjacentChunks[i], visited);
            }
        }

    } else {
        cerr << "Invalid chunk name found: " << map->id << '\n';
        exit(1);
    }
}
int testMap (){
    memset((void*)&chunks, 0, sizeof(chunks));
    Map* map = BuildMap("0");
    bool visited[128];
    memset((void*)&visited, 0, sizeof(visited));
    printMap(map, visited);
    return 0;
}