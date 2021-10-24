#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "Node.h"

#include <iostream>
#include <vector>

using namespace std;

class Chunk {
public:
	vector<Node*> Data;
	Node* Alpha;
	int Color;
	Chunk(Node* alpha);
	Chunk(Node* alpha, int color);
	Chunk(Node* alpha, int color, vector<Node*> data);
};

#endif