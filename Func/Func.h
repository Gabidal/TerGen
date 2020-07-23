#ifndef _FUNC_H_
#define _FUNC_H_

#include "../Components/Tile.h"
#include <vector>

using namespace std;

class Func {
public:
	Func(){}
	//the parameter type MUST be same as the returning type!!!
	Tile (*Function)(vector<long> Inputs);
};

#endif