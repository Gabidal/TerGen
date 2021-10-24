#ifndef _CORE_H_
#define _CORE_H_
#include "../Node/Node.h"
#include "../Node/Chunk.h"

#include <iostream>
#include <vector>

using namespace std;


typedef void (*Generator)(vector<Node*>, vector<Chunk*>&);

class Core {
public:
	Node* Start_Point = new Node(0, 0, 0);
	Node* End_Point = new Node(100, 100, 100);

	long Resolution = 0;

	vector<Node*> Master;

	vector<Chunk*> Cluster;

	vector<Generator> Functions;

	vector<pair<int, Generator>> Colors;

	double Width;
	double Depth;
	double Height;

	Core(int resolution, vector<Generator> functions);
	Core(Node* SP, Node* EP, int resolution, vector<Generator> functions);

	void Factory();
	void Populize();

	int Index(int X, int Z);
	void Calculate_World_Size();

	int Allocate_Color(Generator Func);
};

#endif