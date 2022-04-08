#include "Chunk.h"
#include "../Core/Core.h"
#include "Pattern.h"

extern TerGen_Core* core;

TerGen_Chunk::TerGen_Chunk(vector<Pattern*> p, SimplexNoise* Ground, SimplexNoise* Moist, SimplexNoise* Temp, int X, int Z) {
	Nodes = new Node[CHUNK_SIZE * CHUNK_SIZE * core->Resolution * core->Resolution];
	Patterns = p;

	//first seed this chunk with the basic given ground noise
	for (int x = 0; x < CHUNK_SIZE * core->Resolution; x++) {
		for (int z = 0; z < CHUNK_SIZE * core->Resolution; z++) {

			int Real_X = x + X * CHUNK_SIZE;
			int Real_Z = z + Z * CHUNK_SIZE;

			Node* node = At(Real_X, Real_Z);

			node->Y = Ground->fractal(2, Real_X, Real_Z);
			node->Moisture = Moist->fractal(2, Real_X, Real_Z);
			node->Tempature = Temp->fractal(2, Real_X, Real_Z);
		}
	}

	for (auto* P : Patterns) {
		P->Calculate(P->X, P->Z, Nodes);
	}
}