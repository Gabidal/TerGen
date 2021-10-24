#include "Chunk.h"

Chunk::Chunk(Node* alpha)
{
	Alpha = alpha;
}

Chunk::Chunk(Node* alpha, int color)
{
	Alpha = alpha;
	Color = color;
}

Chunk::Chunk(Node* alpha, int color, vector<Node*> data)
{
	Alpha = alpha;
	Color = color;
	Data = data;
}
