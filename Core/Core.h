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
				Chunks[X, Z] = new Chunk();
			}
		}
	}

	unsigned char Allocate_Color() {
		if (Patterns.size() == 0)
			return 0;
		return Patterns.back().Color + 1;
	}

	vector<Pattern*> Pack_Patterns() {

	}
};

namespace Smart_Counter {
	map<int, siv::BasicPerlinNoise<float>*> Counters;

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