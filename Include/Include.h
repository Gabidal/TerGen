#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <vector>
#include <string>
#include <functional>

constexpr int CHUNK_SIZE = 16;
constexpr int MAX_HEIGHT = CHUNK_SIZE / 2;

class Node {
public:
	float Y;
	unsigned char Color;

	Node(float y = 0, char c = 0) {
		Y = y;
		Color = c;
	}
};

class Pattern;
typedef void (*FUNCTION)(Pattern*);

class Pattern {
public:
	unsigned char Color;  //Colors represent node ground types.
	Node* Nodes; //Points back to the chunk.
	int X;	//starting address X
	int Z;	//starting address Y
	FUNCTION Function; //modifier

	//First in main we create these patterns, and later on
	//we give them the target node list.
	Pattern(FUNCTION func);

	Pattern(int x, int y, Pattern& p);

	void Calculate(int x, int z, Node* nodes);
};

//-res [how much points shall there be?]
//Note the default chunk size is 16x16
[[nodiscard]]
extern std::vector<Node*> TerGen(std::string args, std::vector<FUNCTION> functions);

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
    extern void For_All_Nodes(std::vector<Node*> nodes, std::function<void(Node*, double, double)> lambda);
    extern void For_All_Nodes(std::function<void(Node*, double, double)> lambda);
}

#endif