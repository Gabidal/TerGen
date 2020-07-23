#ifndef _LAYER_H_
#define _LAYER_H_

#include "Tile.h"
#include <vector>

using namespace std;

class Layer : public Dot{
public:
	vector<vector<Tile>> Layer;
};

#endif