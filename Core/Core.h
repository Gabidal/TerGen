#include "../Node/Node.h"

#include <iostream>
#include <vector>

using namespace std;

class Core {
public:
	Node* Start_Point = new Node(0, 0, 0);
	Node* End_Point = new Node(100, 100, 100);

	vector<Node*> Output;

	Core();
};