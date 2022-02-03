#include "Pattern.h"
#include "../Core/Core.h"

extern Core* core;

Pattern::Pattern(FUNCTION func) {
	Function = func;

	Color = core->Allocate_Color();
}

void Pattern::Calculate(Node* nodes) {
	Nodes = nodes;

	Function(this);
}