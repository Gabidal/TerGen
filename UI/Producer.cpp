#include "Producer.h"
#include "Args.h"

extern Args* CMD;

Producer::Producer(vector<Node*> out)
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

	ofstream file(CMD->Output.c_str());

    // open output file
    if (!file) {
        std::cout << "Error opening output file" << std::endl;
        return;
    }

    // write vertices
    for (auto const& v : Output_Node) {
        file << "v " << v->X << ' ' << v->Y << ' ' << v->Z << '\n';
    }

    // write quad indices
    for (auto const& q : Output_Cube) {
        file << "f " << (q->A + 1) << ' ' << (q->B + 1) << ' ' << (q->C + 1) << ' ' << (q->D + 1) << '\n';
    }

	file.close();
}
