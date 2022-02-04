#include "Producer.h"
#include "Args.h"

extern Args* CMD;

Producer::Producer(vector<Chunk*> out)
{
	Input = out;

	MC_Frame Frame_Work(Input);

	Output_Node = Frame_Work.Output_Node;
	Output_Cube = Frame_Work.Output_Cube;

	Factory();
}

void Producer::Factory()
{
    Write_Output_As_Obj();
}

void Producer::Write_Output_As_Obj()
{
	if (CMD->Output_Format != Formats::RAW)
		return;

	ofstream file(CMD->Output + ".obj");

    // open output file
    if (!file) {
        std::cout << "Error opening output file" << std::endl;
        return;
    }

    // write vertices
    for (auto const& v : Output_Node) {
        file << "v " << v.y << ' ' << -v.x << ' ' << v.z << '\n';
    }

    // write quad indices
    for (auto const& q : Output_Cube) {
        file << "f " << (q->A + 1) << ' ' << (q->B + 1) << ' ' << (q->C + 1) << ' ' << (q->D + 1) << '\n';
    }

	file.close();
}
