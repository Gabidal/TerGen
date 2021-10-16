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

	vector<Node*> Output;

	double Width = End_Point->X - Start_Point->X + 1;
	double Height = End_Point->Y - Start_Point->Y + 1;
	double Depth = End_Point->Z - Start_Point->Z + 1;

	Core(vector<Node*> Out);
	Core(vector<Node*> Out, Node* SP, Node* EP);

	void Factory();
	void Populize();
	void Noise();
};

#endif