#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "../Node/Node.h"
#include "../Node/Chunk.h"

#include <iostream>
#include <vector>

using namespace std;

extern Core* core;

namespace FUNCTIONS {
	//every function generates it's own team of points, that are sprinkled throughout the master
	void Parabola(vector<Node*> Master, vector<Chunk*>& Cluster) {
		//allocate a new color to represent this function
		int Color = core->Allocate_Color(Parabola);

		//make a virtual space to calculate the inherite of the points
		Chunk* Space = new Chunk(new Node(0, 0, 0), Color);


	}
}

#endif