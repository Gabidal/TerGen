#include "../MC/dualmc.h"
#include "../Node/Cube.h"
#include "../Core/Core.h"
#include "../Node/Node.h"

#include <iostream>

using namespace std;
using namespace dualmc;

class MC_Frame {
private:
	vector<Chunk*> Input;

	vector<char> Space;

	vector<char> Transform_Chunks_To_Space();
	Node* Transform_Vertex_To_Node(vector<Vertex> Output);
	vector<Cube*> Transform_Quad_To_Cube(vector<Quad> Output);
public:
	vector<Vertex> Output_Node;
	vector<Cube*> Output_Cube;

	MC_Frame(vector<Chunk*> In);
};