#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "../Node/Simplex.h"
#include "../Node/Pattern.h"
#include "../Node/Chunk.h"
#include "../Core/Core.h"
#include "../Core/Constants.h"

extern TerGen_Core* core;

/// <summary>
/// Pattern inlists all the right informations for the calculations.
/// </summary>
/// <param name="p"></param>
namespace PERLIN {
	//This is so that we dont need to create other perlin instanses
	SimplexNoise* Perlin;
	unsigned Color;

	unsigned char Perlin_Noise(Pattern* p, int Amount) {
		unsigned char Result = 0;

		for (int X = 0; X < Amount; X++) {
			for (int Z = 0; Z < Amount; Z++) {

				//we need to create the real X & Y coordinates based on the chunk X & Y
				int Real_X = X + p->X * CHUNK_SIZE;
				int Real_Z = Z + p->Z * CHUNK_SIZE;

				//Get the relative Node location
				Node& n = p->At(X, Z);
				//set node height
				n.Y = abs(Perlin->noise(Real_X / 10.0, Real_Z / 10.0) * (MAX_HEIGHT -1)) + 1;
				//set node indentifier type.
				n.Color = Color;

				Result = Color;
			}
		}

		return Result;
	}

	void Init_Perlin_Noise() {
		Color = core->Allocate_Color();

		Pattern pattern(Perlin_Noise);

		core->Patterns.push_back(pattern);
	}
}

#endif