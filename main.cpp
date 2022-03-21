#include "UI/Args.h"
#include "UI/Producer.h"
#include "Core/Core.h"
#include "Node/Chunk.h"
#include "Node/Pattern.h"
#include "Node/Node.h"

#include "Functions/Functions.h"

#include "Utils/Utils.h"

#include <iostream>
#include <vector>
#include <sstream>


using namespace std;

Args* CMD = nullptr;
Core* core = nullptr;

#ifndef LIB
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

	vector<Chunk*> World;

	//chancge the const char* into char**
	CMD = new Args(argv, argc);

	core = new Core(1, 10);

	//Init all functions
	PERLIN::Init_Perlin_Noise();
	
	core->Factory();

	Producer producer(World);
}
#endif

vector<string> Split(const string& s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

vector<Node*> TerGen(string args, vector<FUNCTION> functions) {
	vector<TerGen_Chunk*> World;

	vector<const char*> Arguments;

	vector<string> Medium = Split(args, ' ');

	for (auto& i : Medium) {
		Arguments.push_back(i.c_str());
	}

	CMD = new Args(Arguments.data(), Arguments.size());

	core = new Core(CMD->Resolution, CMD->World_Size);

	//Init all functions
	//PERLIN::Init_Perlin_Noise();

	for (auto& i : functions) {
		core->Patterns.push_back(Pattern(i));
	}

	core->Factory();

	vector<Node*> Output;

	Output.resize(core->World_Size * core->World_Size * CHUNK_SIZE * CHUNK_SIZE);

	UTILS::For_All_Nodes([&Output](Node* node, int x, int y) {
		Output[CHUNK_SIZE * x + y] = node;
	});

	/*for (int c_x = 0; c_x < core->World_Size; c_x++) {
		for (int c_y = 0; c_y < core->World_Size; c_y++) {

			Chunk* chunk = &core->At(c_x, c_y);

			int Chunk_Index = (core->World_Size * c_x + c_y) * CHUNK_SIZE * CHUNK_SIZE;

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					int Node_index = CHUNK_SIZE * x + y;

					Output[Chunk_Index + Node_index] = new Node(chunk->At(x, y));
				}
			}

		}
	}*/

	return Output;
}