#include "Pattern.h"
#include "../Core/Core.h"

extern TerGen_Core* core;

Pattern::Pattern(FUNCTION func) {
	Function = func;

	Color = core->Allocate_Color();
}

Pattern::Pattern(FUNCTION func, float weight)
{
	Function = func;
	Weight = weight;
	Color = core->Allocate_Color();
}

Pattern::Pattern(int x, int y, Pattern& p)
{
	*this = p;
	X = x;
	Z = y;
}

void Pattern::Calculate(int x, int z, Node* nodes) {
	Nodes = nodes;
	X = x;
	Z = z;

	Function(this, CHUNK_SIZE, nullptr);
}