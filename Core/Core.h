#ifndef _CORE_H_
#define _CORE_H_
#include "../Node/Node.h"
#include "../Node/Chunk.h"

#include <iostream>
#include <vector>

using namespace std;

class Core {
public:
	Node* Start_Point = new Node(0, 0, 0);
	Node* End_Point = new Node(100, 100, 100);

	long Resolution = 0;

	vector<Node*> Master;

	vector<Chunk*> Cluster;
	vector<void (*)(vector<Node*>, vector<Chunk*>)> Functions;

	double Width;
	double Depth;
	double Height;

	Core(int resolution, vector<void (*)(vector<Node*>, vector<Chunk*>&)> functions);
	Core(Node* SP, Node* EP, int resolution, vector<void (*)(vector<Node*>, vector<Chunk*>&)> functions);

	void Factory();
	void Populize();

	int Index(int X, int Z);
	void Calculate_World_Size();
};

#endif