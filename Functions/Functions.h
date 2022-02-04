#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "../Node/Perlin_Noise.hpp"
#include "../Node/Pattern.h"
#include "../Node/Chunk.h"
#include "../Core/Core.h"
#include "../Core/Constants.h"

extern Core* core;

/// <summary>
/// Pattern inlists all the right informations for the calculations.
/// </summary>
/// <param name="p"></param>
namespace PERLIN {
	//This is so that we dont need to create other perlin instanses
	siv::BasicPerlinNoise<float> Perlin;
	unsigned Color;

	void Perlin_Noise(Pattern* p) {
		for (int X = 0; X < CHUNK_SIZE; X++) {
			for (int Z = 0; Z < CHUNK_SIZE; Z++) {

				//we need to create the real X & Y coordinates based on the chunk X & Y
				int Real_X = X + p->X * CHUNK_SIZE;
				int Real_Z = Z + p->Z * CHUNK_SIZE;

				//Get the relative Node location
				Node& n = p->At(X, Z);
				//set node height
				n.Y = abs(Perlin.noise2D(Real_X / 100.0, Real_Z / 100.0)) * (MAX_HEIGHT -1)+ 1;
				//set node indentifier type.
				n.Color = Color;
			}
		}
	}

	void Init_Perlin_Noise() {
		Color = core->Allocate_Color();

		Pattern pattern(Perlin_Noise);

		core->Patterns.push_back(pattern);
	}
}




#endif