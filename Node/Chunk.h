#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <iostream>
#include <vector>

using namespace std;

class Chunk {
public:
	unsigned int Max_Height;
	unsigned int* Nodes;

	Chunk();

	~Chunk() {
		delete Nodes;
		delete this;
	}
};

class Pattern {
public:
	Chunk* Data;
	//Block type? basically yes.
	unsigned int Color;
	//0(Bottom) - UINT_MAX(Ceiling)
	unsigned int Occurance;
	//0(0%) - 255(100%)
	unsigned char Frequency;
	//from pi/2 to -pi/2 or 90 to -90 degrees of angle in which is reguired to spawn this pattern.
	char Decent;
	Pattern(int color);
	Pattern(int color, Chunk* data);
	Pattern(Chunk* data);
	Pattern();
};

#endif