#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <iostream>
#include <vector>

#include "Node.h"
#include "Chunk.h"
#include "../Core/Constants.h"
#include "Simplex.h"

using namespace std;

class Pattern;

class TerGen_Chunk {
public:
	//The generated map part.
	Node* Nodes;
	vector<Pattern*> Patterns;

	TerGen_Chunk(vector<Pattern*> p, SimplexNoise* Ground, SimplexNoise* Moist, SimplexNoise* Temp, int X, int Z);

	Node* At(int X, int Z) {

		int Node_X = X % CHUNK_SIZE;
		int Node_Z = Z % CHUNK_SIZE;

		return &Nodes[CHUNK_SIZE * Node_X + Node_Z];
	}
};

#endif