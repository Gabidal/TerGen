#include "UI/Args.h"
#include "UI/Producer.h"
#include "Node/Node.h"
#include "Core/Core.h"
#include "Node/Chunk.h"
#include "Functions/Functions.h"

#include <iostream>
#include <vector>

using namespace std;

Args* CMD = nullptr;
Core* core = nullptr;

int main(int argc, const char* argv[]) {
	//if no parameters are passed, give user help
	if (argc == 1) {
		cout << "[file name to output the point map]" << endl;
		cout << "-out [file name to output the point map]" << endl;
		cout << "-res [how much points shall there be?]" << endl;
	}

	vector<Node*> Master;

	CMD = new Args(argv, argc);

	core = new Core(CMD->Resolution, {
		FUNCTIONS::Mountain
	});

	Master = core->Master;

	Producer producer(Master);
}