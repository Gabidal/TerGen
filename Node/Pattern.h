#ifndef _PATTERN_H_
#define _PATTERN_H_

#include <iostream>
#include <vector>

using namespace std;

#include "Chunk.h"
#include "Node.h"

class Pattern;
typedef void (*FUNCTION)(Pattern*);

class Pattern {
public:
	unsigned char Color;  //Colors represent node ground types.
	Node* Nodes; //Points back to the chunk.
	FUNCTION Function; //modifier

	//First in main we create these patterns, and later on
	//we give them the target node list.
	Pattern(FUNCTION func);

	void Calculate(Node* nodes);
};

#endif