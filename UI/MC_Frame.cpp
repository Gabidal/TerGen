#include "MC_Frame.h"

extern Core* core;

vector<char> MC_Frame::Transform_Chunks_To_Space()
{
    vector<char> Result;

    for (int C_X = 0; C_X < core->Chunk_Count; C_X++) {
        for (int C_Z = 0; C_Z < core->Chunk_Count; C_Z++)
            for (int C_Y = 0; C_Y < core->Chunk_Count; C_Y++) {
                Chunk* Current_Chunk = Input[(C_Y * core->Chunk_Count * core->Chunk_Count) + (C_Z * core->Chunk_Count) + C_X];
                
                Result.resize(Result.size() + core->Resolution * core->Resolution * core->Resolution);

                for (int N_X = 0; N_X < core->Resolution; N_X++) {
                    for (int N_Z = 0; N_Z < core->Resolution; N_Z++) {
                        for (int N_Y = 0; N_Y < core->Resolution; N_Y++) {
                            char Color = 0;
                            long Index = (N_Y * core->Resolution * core->Resolution) + (N_Z * core->Resolution) + N_X;
                            if (N_Y <= Current_Chunk->Max_Height) {
                                Color = Current_Chunk->Nodes[Index];
                            }
                            Result[Index] = Color;
                        }
                    }
                }
            }
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

MC_Frame::MC_Frame(vector<Chunk*> in)
{
    Input = in;

    Space = Transform_Chunks_To_Space();

    dualmc::DualMC<char> builder;

    vector<Vertex> Vertices;
    vector<Quad> Quads;

    int Area = core->Chunk_Count * (core->Resolution * core->Resolution * core->Resolution);

    int Side = cbrt(Area);

    builder.build(Space.data(), Side, Side, Side,
        1, true, true, Vertices, Quads);

    Output_Node = Transform_Vertex_To_Node(Vertices);
    Output_Cube = Transform_Quad_To_Cube(Quads);
}
