#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <iostream>
#include <vector>

#include "Node.h"
#include "Chunk.h"
#include "../Core/Constants.h"

using namespace std;

class Pattern;

class TerGen_Chunk {
public:
	Node* Nodes;
	vector<Pattern*> Patterns;

	TerGen_Chunk(vector<Pattern*> p);

	Node& At(int X, int Z) {
		return Nodes[(CHUNK_SIZE * X) + Z];
	}
};

#endif