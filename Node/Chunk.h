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

	Node* At(int X, int Z) {

		int Node_X = X % CHUNK_SIZE;
		int Node_Z = Z % CHUNK_SIZE;

		return &Nodes[CHUNK_SIZE * Node_X + Node_Z];
	}
};

#endif