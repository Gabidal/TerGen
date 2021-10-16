#include "UI/Args.h"
#include "UI/Producer.h"
#include "Node/Node.h"
#include "Core/Core.h"

#include <iostream>
#include <vector>

using namespace std;

Args* CMD = nullptr;
Core* core = nullptr;

int main(int argc, const char* argv[]) {
	//if no parameters are passed, give user help
	if (argc == 1) {
		cout << "[file name to output the point map]" << endl;
	}

	vector<Node*> Nodes;

	CMD = new Args(argv, argc);

	core = new Core(Nodes);

	Nodes = core->Output;

	Producer producer(Nodes);
}