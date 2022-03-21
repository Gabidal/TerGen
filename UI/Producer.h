#include "MC_Frame.h"
#include "../Node/Node.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Producer {
	vector<TerGen_Chunk*> Input;

	vector<Vertex> Output_Node;
	vector<Cube*> Output_Cube;

	void Factory();
	void Write_Output_As_Obj();
	void Write_Output_As_Raw();
public:
	Producer(vector<TerGen_Chunk*> out);
};