#include "Chunk.h"
#include "../Core/Core.h"

extern Core* core;

Chunk::Chunk() {
	Max_Height = core->Resolution;
	Nodes = new unsigned int[core->Resolution * core->Resolution * core->Resolution]{ 0 };
}

Pattern::Pattern(int color)
{
	Data = new Chunk();
	Color = color;
}

Pattern::Pattern()
{
	Data = new Chunk();
	Color = core->Allocate_Color(this);
}

Pattern::Pattern(int color, Chunk* data)
{
	Data = data;
	Color = color;
	Data = data;
}

Pattern::Pattern(Chunk* data)
{
	Data = data;
	Color = core->Allocate_Color(this);
	Data = data;
}