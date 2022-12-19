#include "Src/Args.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

TerGen::Args* CMD = nullptr;

int main(int argc, const char* argv[]) {
	//if no parameters are passed, give user help
	if (argc == 1) {
		cout << "Quick use:" << endl;
		cout << "  [file name to output the point map]" << endl;
		cout << "\nArguments:" << endl;
		cout << "  -out [file name to output the point map]" << endl;
		cout << "  -res [how much points shall there be?]" << endl;
		cout << "  -world_size [how many chunks there will be?]" << endl;

		return 1;
	}

	////chancge the const char* into char**
	CMD = new TerGen::Args(argv, argc);
}