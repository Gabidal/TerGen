#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "Layer.h"
#include <vector>

using namespace std;

class Chunk {
public:
	//3D vector of the chunk
	//the kayers can be on top of eachother or side by side
	vector<Layer> Chunk;
};

#endif