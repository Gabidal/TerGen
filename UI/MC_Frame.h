#include "../MC/dualmc.h"
#include "../Node/Node.h"
#include "../Node/Cube.h"

#include <iostream>

using namespace std;
using namespace dualmc;

extern class Core* Core;

class MC_Frame {
private:
	vector<Node*> Input;

	double Width = Start_Point->X - End_point->X + 1;
	double Height = Start_Point->Y - End_point->Y + 1;
	double Depth = Start_Point->Z - End_point->Z + 1;

	vector<char> Space;

	vector<char> Transform_Node_To_Space();
	vector<Node*> Transform_Vertex_To_Node(vector<Vertex> Output);
	vector<Cube*> Transform_Quad_To_Cube(vector<Quad> Output);
public:
	vector<Node*> Output_Node;
	vector<Cube*> Output_Cube;

	MC_Frame(vector<Node*> In);
};