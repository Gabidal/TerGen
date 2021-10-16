#include "MC_Frame.h"

extern Core* core;

vector<char> MC_Frame::Transform_Node_To_Space()
{
    vector<char> Result;

    Result.resize(core->Width * core->Height * core->Depth);

    for (auto i : Input) {
        Result[(i->X) + (i->Z * core->Width) + (i->Y * core->Width * core->Height)] = 2;
    }

    return Result;
}

vector<Node*> MC_Frame::Transform_Vertex_To_Node(vector<Vertex> Output)
{
    vector<Node*> Result;

    for (auto i : Output) {
        Result.push_back(new Node(i.x, i.y, i.z));
    }

    return Result;
}

vector<Cube*> MC_Frame::Transform_Quad_To_Cube(vector<Quad> Output)
{
    vector<Cube*> Result;

    for (auto i : Output) {
        Result.push_back(new Cube(i.i0, i.i1, i.i2, i.i3));
    }

    return Result;
}

MC_Frame::MC_Frame(vector<Node*> in)
{
    Input = in;

    Space = Transform_Node_To_Space();

    dualmc::DualMC<char> builder;

    vector<Vertex> Vertices;
    vector<Quad> Quads;

    builder.build(Space.data(), core->Width, core->Height, core->Depth,
        1, true, true, Vertices, Quads);

    Output_Node = Transform_Vertex_To_Node(Vertices);
    Output_Cube = Transform_Quad_To_Cube(Quads);
}
