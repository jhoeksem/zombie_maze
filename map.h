#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>
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
        string name;
        string id; // An id number from 0-127
        string description; // Description of chunk in text
        string postDescription; // Description of the chunk, after it has been completed
        bool isCompleted; // Tells if the chunk has been completed
        string direction[4]; // Stores the ids of the neighbooring nodes. Not used after build time
        Map* adjacentChunks[4]; // Stores a pointer to the neighbooring nodes
        Map(string mapId);
        void PrintChunk();
};
Map* BuildMap(string mapId);
int testMap ();

#endif // PARSER_H