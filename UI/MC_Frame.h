#include "../MC/dualmc.h"
#include "../Node/Node.h"
#include "../Node/Cube.h"
#include "../Core/Core.h"

#include <iostream>

using namespace std;
using namespace dualmc;

class MC_Frame {
private:
	vector<Node*> Input;

	vector<char> Space;

	vector<char> Transform_Node_To_Space();
	vector<Node*> Transform_Vertex_To_Node(vector<Vertex> Output);
	vector<Cube*> Transform_Quad_To_Cube(vector<Quad> Output);
public:
	vector<Node*> Output_Node;
	vector<Cube*> Output_Cube;

	MC_Frame(vector<Node*> In);
};