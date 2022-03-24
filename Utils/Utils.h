#ifndef _UTILS_H_
#define _UTILS_H_

#include <functional>

#include <vector>

using namespace std;

class TerGen_Chunk;
class Node;

class TerGen_Chunk_Coordinates {
public:
    int X;
    int Z;

    TerGen_Chunk_Coordinates(int x, int z) {
        X = x;
        Z = z;
    }
};

class TerGen_Node_Coordinates {
public:
    int X;
    int Z;

    TerGen_Node_Coordinates(int x, int z) {
        X = x;
        Z = z;
    }
};

namespace UTILS
{
    extern unsigned char Get_Free_Color();
    extern TerGen_Chunk* Get_Chunk(TerGen_Chunk_Coordinates coordinates);
    extern TerGen_Chunk* Get_Chunk(TerGen_Node_Coordinates coordinates);
    extern Node* Get_Node(int x, int z);
    extern void For_All_Nodes(std::vector<Node*> nodes, std::function<void(Node*, double, double, double, double)> lambda);
    extern void For_All_Nodes(std::function<void(Node*, double, double, double, double)> lambda);
    extern unsigned long Rand();
}


#endif