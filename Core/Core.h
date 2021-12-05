#ifndef _CORE_H_
#define _CORE_H_
#include "../Node/Chunk.h"

#include <iostream>
#include <vector>

using namespace std;


typedef Pattern* (*Pattern_Generator)(Chunk*);
typedef void (*Behaviour_Generator)(vector<Chunk*>& Chunks, int X, int Y, int Z);

class Core {
public:
	int Resolution;
	int Chunk_Count;

	vector<Chunk*> Chunks;

	vector<Pattern*> Patterns;

	vector<pair<char, Pattern_Generator>> Pattern_Functions;

	vector<Behaviour_Generator> Behaviour_Functions;

	vector<pair<int, Pattern*>> Colors;

	Core(int Chunk_Count, int resolution);

	void Factory();
	void Populize();

	void Calculate_All_Chunk_Height();

	void Integrate();

	int Allocate_Color(Pattern* pattern);
};

#endif