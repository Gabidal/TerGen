#include "UI/Args.h"
#include "UI/Producer.h"
#include "Core/Core.h"
#include "Node/Pattern.h"
#include "Node/Node.h"
#include "Node/Chunk.h"

#include "Functions/Functions.h"

#include "Utils/Utils.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Args* CMD = nullptr;
TerGen_Core* core = nullptr;

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
	
	float Frequenzy = 0.1;
	float Amplitude = 1;
	float Lacuranity = 4;
	float Persictent = 0.3;
	float Seed = 1;
	float FBM_Octaves = 4;
	float WARP_Octaves = 2;

	vector<TerGen_Chunk*> World;

	////chancge the const char* into char**
	CMD = new Args(argv, argc);

	core = new TerGen_Core(Frequenzy, Amplitude, Lacuranity, Persictent, Seed, FBM_Octaves, WARP_Octaves, CMD->Resolution, CMD->World_Size);


	vector<FUNCTION> functions = {
	};

	for (auto& i : functions) {
		core->Patterns.push_back(Pattern(i));
	}

	core->Factory();
	World = core->Chunks;

	//core->Integrate();

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

vector<Node*> TerGen(
	string args, 
	vector<Packet> Packets,
	float Frequenzy,
	float Amplitude,
	float Lacuranity,
	float Persictent,
	float Seed,
	float FBM_Octaves,
	float WARP_Octaves
) {
	
	vector<TerGen_Chunk*> World;

	vector<const char*> Arguments;

	vector<string> Medium = Split(args, ' ');

	for (auto& i : Medium) {
		Arguments.push_back(i.c_str());
	}

	CMD = new Args(Arguments.data(), Arguments.size());

	core = new TerGen_Core(Frequenzy, Amplitude, Lacuranity, Persictent, Seed, FBM_Octaves, WARP_Octaves, CMD->Resolution, CMD->World_Size);

	for (auto& i : Packets) {
		core->Patterns.push_back(Pattern(i.Function, i.Weight));
	}

	core->Factory();

	//core->Integrate();

	vector<Node*> Output;

	Output.resize(core->World_Size * core->World_Size * CHUNK_SIZE * CHUNK_SIZE);

	UTILS::For_All_Nodes([&Output](Node* node, int x, int y, int Chunk_X, int Chunk_Y) {
		Output[Chunk_X + Chunk_Y] = node;
	});

	return Output;
}