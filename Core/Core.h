#ifndef _CORE_H_
#define _CORE_H_
#include "../Node/Node.h"

#include <iostream>
#include <vector>

using namespace std;

class Core {
public:
	Node* Start_Point = new Node(0, 0, 0);
	Node* End_Point = new Node(100, 100, 100);

	long Resolution = 0;

	vector<Node*> Output;

	double Width;
	double Depth;
	double Height;

	Core(vector<Node*> Out, int resolution);
	Core(vector<Node*> Out, Node* SP, Node* EP, int resolution);

	void Factory();
	void Populize();
	void Noise();

	int Index(int X, int Z);

	void Calculate_World_Size();
};

#endif