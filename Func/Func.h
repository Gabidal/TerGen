#ifndef _FUNC_H_
#define _FUNC_H_

#include "../Components/Tile.h"

class Func {
public:
	Func(){}
	//the parameter type MUST be same as the returning type!!!
	double (*Function)(Dot dot);
};

#endif