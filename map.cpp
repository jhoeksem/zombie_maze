#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// For directions I went with East=0, North=1, West=2, South=3
enum Directions{
    EAST,
    NORTH,
    WEST,
    SOUTH,
};
class Map{
    public:
        string id; // An id number from 0-127
        string description; // Description of chunk in text
        string direction[4]; // Stores the ids of the neighbooring nodes. Not used after build time
        Map* adjacentChunks[4]; // Stores a pointer to the neighbooring nodes
        Map(string mapId);
        void PrintChunk();
};

Map* chunks [128];
Map::Map(string mapId){
    id = mapId;
    string line;
    ifstream myfile ("./chunks/"+mapId+".map");
    description = "";
    if (myfile.is_open()){
        while ( getline (myfile, line) && line != "DIRECTIONS") {
            description += line + '\n';
        }
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
        if (mapAddress->direction[i] != ""){
            size_t chunkLength = mapAddress->direction[i].length();
            int adjacentChunkNumber = stoi(mapAddress->direction[i], &chunkLength);
            if( chunks[adjacentChunkNumber]){
                mapAddress->adjacentChunks[i] = chunks[adjacentChunkNumber];
            } else {
                Map* adjacentChunk = BuildMap(mapAddress->direction[i]);
                mapAddress->adjacentChunks[i] = adjacentChunk;
            }
        }
    }
    return mapAddress;
}
void Map::PrintChunk(){
 cout << "Id: " << id <<'\n';
 cout << "Description: " << description<< '\n';
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
int main (){
    Map* map = BuildMap("0");
    bool visited[128];
    printMap(map, visited);
    return 0;
}