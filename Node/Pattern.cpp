#include "Pattern.h"
#include "../Core/Core.h"

extern Core* core;

Pattern::Pattern(FUNCTION func) {
	Function = func;

	Color = core->Allocate_Color();
}

Pattern::Pattern(int x, int z, Pattern& p)
{
	*this = p;
	X = x;
	Z = z;
}

void Pattern::Calculate(int x, int z, Node* nodes) {
	Nodes = nodes;
	X = x;
	Z = z;

	Function(this);
}