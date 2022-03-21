#ifndef _CORE_H_
#define _CORE_H_
#include "../Node/Chunk.h"
#include "../Node/Pattern.h"
#include "../Node/Simplex.h"
#include "Constants.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

namespace Smart_Counter {
	extern map<int, SimplexNoise*> Counters;
	extern int Count(int X, int Z, int Range);
}

class Core {
public:
	int Resolution; //1x resolution == native resolution
	int World_Size;

	vector<TerGen_Chunk*> Chunks;
	vector<Pattern> Patterns;

	Core(int Res = 1, int W = 1) {
		Resolution = Res;
		World_Size = W;

		Chunks.resize(World_Size * World_Size);
	}

	void Factory() {
		for (int X = 0; X < World_Size; X++) {
			for (int Z = 0; Z < World_Size; Z++) {
				Chunks[(World_Size * X) + Z] = new TerGen_Chunk(Pack_Patterns(X, Z));
			}
		}
	}

	unsigned char Allocate_Color() {
		if (Patterns.size() == 0)
			return 1;
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
		
		for (int i = 0; i < Population; i++) {
			Result[i] = new Pattern(X, Z, Patterns[i]);
		}

		return Result;
	}

	TerGen_Chunk& At(int x, int y) {
		return *Chunks[(World_Size * x) + y];
	}
};

#endif