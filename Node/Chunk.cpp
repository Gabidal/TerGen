#include "Chunk.h"
#include "../Core/Core.h"
#include "Pattern.h"
#include "../Utils/Utils.h"

extern TerGen_Core* core;

TerGen_Chunk::TerGen_Chunk(vector<Pattern*> p, SimplexNoise* Ground, SimplexNoise* Moist, SimplexNoise* Temp, int X, int Z) {
	Nodes = new Node[CHUNK_SIZE * CHUNK_SIZE * core->Resolution * core->Resolution];
	Patterns = p;

	//first seed this chunk with the basic given ground noise
	for (int x = 0; x < CHUNK_SIZE * core->Resolution; x++) {
		for (int z = 0; z < CHUNK_SIZE * core->Resolution; z++) {

			int Real_X = x + X * CHUNK_SIZE;
			int Real_Z = z + Z * CHUNK_SIZE;

			Node* node = At(Real_X, Real_Z);

			//node->Y = Ground->fractal(core->Octaves, Real_X, Real_Z);
			node->Y = UTILS::Warp_Noise({ (float)Real_X, (float)Real_Z });
			
			//node->Moisture = ((Moist->fractal(core->FBM_Octaves, Real_X, Real_Z) + 1) * SHRT_MAX) / 2;
			//node->Tempature = ((Temp->fractal(core->FBM_Octaves, Real_X, Real_Z) + 1) * SHRT_MAX) / 2;

			/*if (node->Moisture > Max_Moisture)
				Max_Moisture = node->Moisture;

			if (node->Tempature > Max_Tempature)
				Max_Tempature = node->Tempature;*/

			if (node->Y > Highest_Point.first) {
				Highest_Point = { node->Y, {x, z} };
			}

			if (node->Y < Lowest_Point.first) {
				Lowest_Point = { node->Y, {x, z} };
			}
		}
	}

}