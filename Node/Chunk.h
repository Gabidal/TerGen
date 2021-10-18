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
	Node* Color;
	Chunk(Node* alpha);
	Chunk(Node* alpha, Node* color);
	Chunk(Node* alpha, Node* color, vector<Node*> data);
};

#endif