#ifndef _PATTERN_H_
#define _PATTERN_H_

#include <iostream>
#include <vector>

using namespace std;

#include "Node.h"
#include "../Core/Constants.h"

class Pattern;
typedef unsigned char (*FUNCTION)(Pattern*, int Amount, Node* node);

class Packet {
public:
	FUNCTION Function;
	float Weight;

	Packet(FUNCTION f, float w) {
		Function = f;
		Weight = w;
	}
};

class Pattern {
public:
	unsigned char Color;  //Colors represent node ground types.
	Node* Nodes; //Points back to the chunk.
	int X;	//starting address X
	int Z;	//starting address Y
	FUNCTION Function; //modifier
	float Weight = 0;

	//First in main we create these patterns, and later on
	//we give them the target node list.
	Pattern(FUNCTION func);

	Pattern(FUNCTION func, float weight);

	Pattern(int x, int y, Pattern& p);

	void Calculate(int x, int z, Node* nodes);

	Node& At(int X, int Z) {
		return Nodes[(CHUNK_SIZE * X) + Z];
	}
};

#endif