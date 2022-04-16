#ifndef _UTILS_H_
#define _UTILS_H_

#include <functional>

#include "../Node/Pattern.h"

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

    bool operator==(TerGen_Node_Coordinates other) {
        if (other.X == X && other.Z == Z) {
            return true;
        }
        return false;
    }
};

namespace UTILS
{
    using namespace std;

    extern unsigned char Get_Free_Color();
    extern TerGen_Chunk* Get_Chunk(TerGen_Chunk_Coordinates coordinates);
    extern TerGen_Chunk* Get_Chunk(TerGen_Node_Coordinates coordinates);
    extern Node* Get_Node(int x, int z);
    extern void For_All_Nodes(vector<Node*> nodes, function<void(Node*, double, double, double, double)> lambda);
    extern void For_All_Nodes(function<void(Node*, double, double, double, double)> lambda);


    extern unsigned long Rand();

    extern vector<pair<TerGen_Node_Coordinates, pair<float, float>>> Path_Find(vector<Node>& nodes, TerGen_Node_Coordinates A, TerGen_Node_Coordinates B, float budget, int Width = CHUNK_SIZE);
    extern vector<pair<TerGen_Node_Coordinates, pair<float, float>>> Path_Find(vector<Node*>& nodes, TerGen_Node_Coordinates A, TerGen_Node_Coordinates B, float budget, int Width = CHUNK_SIZE);

    extern unsigned char Get_Color(FUNCTION func);
    extern FUNCTION Get_Function(unsigned char color);

    template<typename T>
    void Append(vector<T>& a, vector<T> b) {
        for (auto i : b) {
            a.push_back(i);
        }
    }
}


#endif