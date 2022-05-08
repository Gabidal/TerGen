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

	Function(this, nullptr);

	//for (int x = 0; x < CHUNK_SIZE; x++) {
	//	for (int z = 0; z < CHUNK_SIZE; z++) {
	//		int index = CHUNK_SIZE * x + z;

	//		Node* n = &nodes[index];
	//		cout << n->Color + 48 << " ";


	//	}
	//	cout << endl;
	//}

	Node* n = &nodes[0];
	float a = n->Color;
	//cout << n << endl;

}