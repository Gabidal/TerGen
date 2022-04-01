#include "Chunk.h"
#include "../Core/Core.h"
#include "Pattern.h"

extern TerGen_Core* core;

TerGen_Chunk::TerGen_Chunk(vector<Pattern*> p) {
	Nodes = new Node[CHUNK_SIZE * CHUNK_SIZE * core->Resolution];
	Patterns = p;

	for (auto* P : Patterns) {
		P->Calculate(P->X, P->Z, Nodes);
	}
}