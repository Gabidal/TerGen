#include "Producer.h"
#include "Args.h"

extern Args* CMD;
extern TerGen_Core* core;

Producer::Producer(vector<TerGen_Chunk*> out)
{
	Input = out;

	Factory();
}

void Producer::Factory()
{
    Write_Output_As_Obj();
    Write_Output_As_Raw();
}

void Producer::Write_Output_As_Obj()
{
	if (CMD->Output_Format != Formats::OBJ)
		return;

    MC_Frame Frame_Work(Input);

    Output_Node = Frame_Work.Output_Node;
    Output_Cube = Frame_Work.Output_Cube;

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

void Producer::Write_Output_As_Raw()
{
    if (CMD->Output_Format != Formats::RAW)
        return;

    ofstream file(CMD->Output + ".bin");

    // open output file
    if (!file) {
        std::cout << "Error opening output file" << std::endl;
        return;
    }

    for (int c_x = 0; c_x < core->World_Size; c_x++) {
        for (int c_y = 0; c_y < core->World_Size; c_y++) {

            TerGen_Chunk* chunk = core->At(c_x, c_y);

            for (int x = 0; x < CHUNK_SIZE; x++) {
                for (int y = 0; y < CHUNK_SIZE; y++) {
                    // write vertices
                    file.write((const char*)&chunk->At(x, y)->Y, sizeof(float));
                    file.write((const char*)&chunk->At(x, y)->Color, sizeof(char));
                }
            }

        }
    }

    file.close();
}
