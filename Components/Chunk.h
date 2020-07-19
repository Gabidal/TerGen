#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "Tile.h"
#include <vector>

using namespace std;

class Chunk : public Dot{
	public:
		//3D vector of the chunk
		//X, Y, Z
		vector<vector<vector<Tile>>> Tiles;
};

#endif