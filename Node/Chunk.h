#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <iostream>
#include <vector>

#include "Node.h"
#include "Pattern.h"

using namespace std;

constexpr int CHUNK_SIZE = 1000;

class Chunk {
public:
	Node* Nodes;
	vector<Pattern*> Patterns;

	Chunk(vector<Pattern*> p) {
		Nodes = new Node[CHUNK_SIZE];
		Patterns = p;

		for (auto& P : Patterns) {
			P->Calculate(Nodes);
		}
	}
};

#endif