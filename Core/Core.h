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

class TerGen_Core {
public:
	int Resolution; //1x resolution == native resolution
	int World_Size;

	SimplexNoise* Ground_Noise_Generator;
	SimplexNoise* Moisture_Generator;
	SimplexNoise* Tempature_Generator;

	vector<TerGen_Chunk*> Chunks;
	vector<Pattern> Patterns;

	TerGen_Core(float freq, float amp, float lac, float per, float sed, int Res = 1, int W = 1) {
		Resolution = Res;
		World_Size = W;

		Chunks.resize(World_Size * World_Size);

		Ground_Noise_Generator = new SimplexNoise(freq, amp, lac, per, sed);
		Moisture_Generator = new SimplexNoise(freq, amp, lac, per, sed * sed);
		Tempature_Generator = new SimplexNoise(freq, amp, lac, per, sed * sed * sed);
	}

	void Factory() {
		for (int X = 0; X < World_Size; X++) {
			for (int Z = 0; Z < World_Size; Z++) {
				Chunks[(World_Size * X) + Z] = new TerGen_Chunk(
					Pack_Patterns(X, Z),
					Ground_Noise_Generator,
					Moisture_Generator,
					Tempature_Generator,
					X, Z
				);
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

		int i = 0;
		while (i < Patterns.size() && i < Population) {

			if (Patterns[i].Weight == 0)
				i++;

			if (rand() / (float)RAND_MAX < Patterns[i].Weight) {
				Result.push_back(new Pattern(X, Z, Patterns[i]));
				i++;
			}

		}

		return Result;
	}

	void Integrate();

	TerGen_Chunk* At(int x, int y) {
		return Chunks[World_Size * x + y];
	}
};

#endif