#include "MC_Frame.h"
#include "../Node/Node.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Producer {
	vector<Chunk*> Input;

	vector<Node*> Output_Node;
	vector<Cube*> Output_Cube;

	void Factory();
	void Write_Output_As_Obj();
public:
	Producer(vector<Chunk*> out);
};