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

	float Frequenzy;
	float Amplitude;
	float Lacuranity;
	float Persistance;
	float Seed;

	float FBM_Octaves;
	float Warp_Octaves;

	SimplexNoise* Ground_Noise_Generator;
	SimplexNoise* Moisture_Generator;
	SimplexNoise* Tempature_Generator;

	vector<TerGen_Chunk*> Chunks;
	vector<Pattern> Patterns;

	vector<vector<float>> Offsetters;

	TerGen_Core(float freq, float amp, float lac, float per, float sed, float fbm_octaves, float warp_octaves, int Res = 1, int W = 1) {
		Resolution = Res;
		World_Size = W;

		Chunks.resize(World_Size * World_Size);

		Ground_Noise_Generator = new SimplexNoise(freq, amp, lac, per, sed);
		Moisture_Generator = new SimplexNoise(freq, amp, lac, per, sed);
		Tempature_Generator = new SimplexNoise(freq, amp, lac, per, sed);

		Frequenzy = freq;
		Amplitude = amp;
		Lacuranity = lac;
		Persistance = per;
		Seed = sed;
		FBM_Octaves = fbm_octaves;
		Warp_Octaves = warp_octaves;

		for (int i = 0; i < Warp_Octaves; i++) {

			vector<float> Current;
			for (int j = 0; j < 4; j++) {
				Current.push_back((float)rand() / INT32_MAX * 10000);
			}

			Offsetters.push_back(Current);
		}

		/*Offsetters = {
			{0.0, 0.0, 5.2, 1.3},
			{1.7, 9.2, 8.3, 2.8}
		};*/
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

		//calculate delta for every point on map.
		Calculate_Delta();

		//Color the map by given functinos from user.
		for (int X = 0; X < World_Size; X++) {
			for (int Z = 0; Z < World_Size; Z++) {
				for (auto p : Chunks[(World_Size * X) + Z]->Patterns) {
					TerGen_Chunk* chunk = Chunks[(World_Size * X) + Z];
					p->Calculate(p->X, p->Z, chunk->Nodes);
				}
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

		int Population = Range;//Smart_Counter::Count(X, Z, Range);

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

	//void Corrode();
	//void River();

	TerGen_Chunk* At(int x, int y) {
		return Chunks[World_Size * x + y];
	}

	TerGen_Chunk* At(TerGen_Node_Coordinates coordinates) {
		int CX = coordinates.X / CHUNK_SIZE - ((unsigned)coordinates.X >> 31);
		int CZ = coordinates.Z / CHUNK_SIZE - ((unsigned)coordinates.Z >> 31);

		return Chunks[World_Size * CX + CZ];
	}

	vector<pair<int, int>> Get_Surrounding_Tiles(int X, int Z) {
		vector<pair<int, int>> Result;

		if (Z - 1 >= 0) {
			Result.push_back({ X, Z });
		}

		if (X - 1 >= 0) {
			Result.push_back({ X, Z });
		}

		if (Z + 1 < CHUNK_SIZE) {
			Result.push_back({ X, Z });
		}

		if (X + 1 < CHUNK_SIZE) {
			Result.push_back({ X, Z });
		}

		return Result;
	}

	void Calculate_Delta(){
		for (int C_X = 0; C_X < World_Size; C_X++) {
			for (int C_Z = 0; C_Z < World_Size; C_Z++) {
				TerGen_Chunk* C = Chunks[(World_Size * C_X) + C_Z];

				for (int N_X = 0; N_X < CHUNK_SIZE; N_X++) {
					for (int N_Z = 0; N_Z < CHUNK_SIZE; N_Z++) {
						Node* n = C->At(N_X, N_Z);

						vector<int> Deltas;

						//calculate all difference deltas betweent he current node and it's surrounding nodes.
						for (auto Coord : Get_Surrounding_Tiles(N_X, N_Z)) {
							Node* n2 = At(C_X, C_Z)->At(Coord.first, Coord.second);
							Deltas.push_back(n->Y - n2->Y);
						}
						
						//calculate the average delta
						int Average = 0;

						for (auto d : Deltas) {
							Average += d;
						}

						Average /= Deltas.size();

						n->Delta = Average;
					}
				}
			}
		}

	}

};

#endif