#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "../Node/Node.h"
#include "../Node/Chunk.h"

#include <iostream>
#include <vector>

using namespace std;

extern Core* core;

namespace FUNCTIONS {
	//for amount of response rate this function is given one chunk to asses.
	//this function can only output one or more clusters into the Clusters list
	char Parabola_Frequency = 255; // 100% response rate
	Pattern* Parabola(Chunk* Chunk) {
		//make a virtual space to calculate the inherite of the points
		//use Node* as a vector to determine the influencing direction.
		Pattern* Space = new Pattern();

		//We can use the Master list of nodes, that represents the whole world.
		//From it we can behaive differently based on what is already generated on the Master node list.
		//for example if there is a cliff a house generator would generate a mountain cliff staris instead of a house.
		
	}


}

#endif