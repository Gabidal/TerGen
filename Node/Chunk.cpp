#include "Chunk.h"

Chunk::Chunk(Node* alpha)
{
	Alpha = alpha;
}

Chunk::Chunk(Node* alpha, Node* color)
{
	Alpha = alpha;
	Color = color;
}

Chunk::Chunk(Node* alpha, Node* color, vector<Node*> data)
{
	Alpha = alpha;
	Color = color;
	Data = data;
}
