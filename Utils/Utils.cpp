#include "Utils.h"

#include "../Core/Core.h"
#include "../Node/Node.h"
#include "../Node/Chunk.h"

extern Core* core;

unsigned char UTILS::Get_Free_Color(){
    return core->Allocate_Color();
}

//NOTE: The given chunk will be destroyed after the TerGen core is shutdown.
TerGen_Chunk* UTILS::Get_Chunk(TerGen_Chunk_Coordinates coordinates){
    return core->At(coordinates.X, coordinates.Z);
}

//NOTE: The given chunk will be destroyed after the TerGen core is shutdown.
TerGen_Chunk* UTILS::Get_Chunk(TerGen_Node_Coordinates coordinates){
    return core->At(coordinates.X / CHUNK_SIZE, coordinates.Z / CHUNK_SIZE);
}

Node* UTILS::Get_Node(int x, int z) {
    //First we need to normalize the x and y to get the chunk.
    int Chunk_X = x / CHUNK_SIZE;
    int Chunk_Z = z / CHUNK_SIZE;

    //Then we get the chunk.
    TerGen_Chunk* chunk = core->At(Chunk_X, Chunk_Z);

    //Then we get the node.
    return chunk->At(x % CHUNK_SIZE, z % CHUNK_SIZE);
}

//This function goes through all the nodes in the world and starts the given lambda function.
void UTILS::For_All_Nodes(std::vector<Node*> nodes, std::function<void(Node*, double, double, double, double)> lambda) {
    //Now that we have the list of nodes we want to convert them to chunks
	for (int c_x = 0; c_x < core->World_Size; c_x++) {
		for (int c_y = 0; c_y < core->World_Size; c_y++) {

			int Chunk_X = c_x * CHUNK_SIZE;

			int Chunk_Y = c_y * CHUNK_SIZE;

			int Chunk_Index = (core->World_Size * c_x + c_y) * CHUNK_SIZE * CHUNK_SIZE;

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					int Node_index = CHUNK_SIZE * x + y;

					lambda(nodes[Chunk_Index + Node_index], x, y, Chunk_X, Chunk_Y);
				}
			}
		}
	}
}

//This function goes through all the nodes in the world and starts the given lambda function.
void UTILS::For_All_Nodes(std::function<void(Node*, double, double, double, double)> lambda) {
	//Now that we have the list of nodes we want to convert them to chunks

	for (int c_x = 0; c_x < core->World_Size; c_x++) {
		for (int c_y = 0; c_y < core->World_Size; c_y++) {
			TerGen_Chunk* chunk = core->At(c_x, c_y);

			//int Chunk_Index = (core->World_Size * c_x + c_y) * CHUNK_SIZE * CHUNK_SIZE;

			int Chunk_X = core->World_Size * c_x * CHUNK_SIZE * CHUNK_SIZE;

			int Chunk_Y = c_y * CHUNK_SIZE * CHUNK_SIZE;

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					//int Node_index = CHUNK_SIZE * x + y;

					int X = x * CHUNK_SIZE + Chunk_X;

					int Y = y + Chunk_Y;

					lambda(chunk->At(x, y), x, y, X, Y);
				}
			}
		}
	}
}

static unsigned long x = 123456789, y = 362436069, z = 521288629;

unsigned long UTILS::Rand() {          //period 2^96-1
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}

unsigned char UTILS::Get_Color(FUNCTION func)
{
	for (auto i : core->Patterns) {
		if (i.Function == func)
			return i.Color;
	}

	return -1;
}

FUNCTION UTILS::Get_Function(unsigned char color) {
	for (auto i : core->Patterns) {
		if (i.Color == color)
			return i.Function;
	}

	return nullptr;
}
