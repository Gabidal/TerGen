#ifndef _CORE_H_
#define _CORE_H_
#include "../Node/Chunk.h"
#include "../Node/Pattern.h"
#include "../Node/Perlin_Noise.hpp"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Core {
public:
	int Resolution; //1x resolution == native resolution
	int World_Size;

	vector<Chunk*> Chunks;
	vector<Pattern> Patterns;

	Core(int Res = 1, int W = 100) {
		Resolution = Res;
		World_Size = W;

		Chunks.resize(World_Size * World_Size);

		for (int X = 0; X < World_Size; X++) {
			for (int Z = 0; Z < World_Size; Z++) {
				Chunks[X, Z] = new Chunk(Pack_Patterns(X, Z));
			}
		}
	}

	unsigned char Allocate_Color() {
		if (Patterns.size() == 0)
			return 0;
		return Patterns.back().Color + 1;
	}

	/// <summary>
	/// Depending on the X & Z, this function will populate a list
	/// With amount of function patterns, depending on the population density-
	/// that Smart_Counter gives
	/// </summary>
	vector<Pattern*> Pack_Patterns(int X, int Z) {
		int Range = Patterns.size();

		int Population = Smart_Counter::Count(X, Z, Range);

		vector<Pattern*> Result;
		Result.resize(Population);
		
		for (int i = 0; i < Patterns.size(); i++) {
			Result[i] = &Patterns[i];
		}
	}
};


namespace Smart_Counter {
	// Save information of all other counters, for different ranges.
	map<int, siv::BasicPerlinNoise<float>*> Counters;

	//this is to keep the pattern population natural in paralell X & Z
	int Count(int X, int Z, int Range) {
		siv::BasicPerlinNoise<float>* Counter = Counters[Range];
		if (Counter == nullptr) {
			Counters[Range] = new siv::BasicPerlinNoise<float>();
			Counter = Counters[Range];
		}

		return (int)floor(Counter->noise2D(X, Z) * 100.0) % Range;
	}
}

#endif