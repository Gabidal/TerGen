#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "Tile.h"
#include <map>
#include <vector>

using namespace std;

class Chunk{
	public:
	  map<Dot, vector<Tile>> Tiles;
	
};

#endif