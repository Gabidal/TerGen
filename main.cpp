#include "UI/Args.h"
#include "UI/Producer.h"
#include "Core/Core.h"
#include "Node/Chunk.h"
#include "Node/Pattern.h"

#include "Functions/Functions.h"

#include <iostream>
#include <vector>

using namespace std;

Args* CMD = nullptr;
Core* core = nullptr;

int main(int argc, const char* argv[]) {
	//if no parameters are passed, give user help
	if (argc == 1) {
		cout << "Quick use:" << endl;
		cout << "  [file name to output the point map]" << endl;
		cout << "\nArguments:" << endl;
		cout << "  -out [file name to output the point map]" << endl;
		cout << "  -res [how much points shall there be?]" << endl;

		return 1;
	}

	vector<Chunk*> World;

	CMD = new Args(argv, argc);

	core = new Core(1, 3);

	//Init all functions
	PERLIN::Init_Perlin_Noise();
	
	core->Factory();

	Producer producer(World);
}