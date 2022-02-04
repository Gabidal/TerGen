#include "Chunk.h"
#include "../Core/Core.h"
#include "Pattern.h"

extern Core* core;

Chunk::Chunk(vector<Pattern*> p) {
	Nodes = new Node[CHUNK_SIZE * CHUNK_SIZE * core->Resolution];
	Patterns = p;

	for (auto* P : Patterns) {
		P->Calculate(P->X, P->Z, Nodes);
	}
}