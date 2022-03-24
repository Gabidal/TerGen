#include "MC_Frame.h"

extern Core* core;

vector<char> MC_Frame::Transform_Chunks_To_Space()
{
    vector<char> Result;
    Result.resize(core->World_Size * core->World_Size * CHUNK_SIZE * CHUNK_SIZE * MAX_HEIGHT * core->Resolution);

    for (int C_X = 0; C_X < core->World_Size; C_X++) {
        for (int C_Z = 0; C_Z < core->World_Size; C_Z++) {

            TerGen_Chunk& chunk = *core->At(C_X, C_Z);
            int Chunk_Skipper = CHUNK_SIZE * CHUNK_SIZE * MAX_HEIGHT;
            int Current_Index = (core->World_Size * C_X + C_Z) * Chunk_Skipper;
            
            for (int X = 0; X < CHUNK_SIZE; X++) {
                for (int Z = 0; Z < CHUNK_SIZE; Z++) {
                    int Node_Index = Current_Index + (MAX_HEIGHT * X) + (Z * CHUNK_SIZE * MAX_HEIGHT);
                    //insert color output support here:
                    for (int Y = 0; Y < chunk.At(X, Z)->Y; Y++) {
                        Result[Node_Index + Y] = chunk.At(X, Z)->Color;
                    }

                }
            }
        }
    }
    

    return Result;
}

Node* MC_Frame::Transform_Vertex_To_Node(vector<Vertex> Output)
{
    Node* Result = new Node[CHUNK_SIZE * CHUNK_SIZE];

    

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

MC_Frame::MC_Frame(vector<TerGen_Chunk*> in)
{
    Input = in;

    Space = Transform_Chunks_To_Space();

    dualmc::DualMC<char> builder;

    vector<Vertex> Result_Vertices;
    vector<Quad> Result_Quads;

    int Area = CHUNK_SIZE * CHUNK_SIZE * MAX_HEIGHT;

    int Chunk_Index = 0;

    for (int X = 0; X < core->World_Size; X++) {
        for (int Y = 0; Y < core->World_Size; Y++) {
            vector<Vertex> Vertices;
            vector<Quad> Quads;

            builder.build(Space.data() + Chunk_Index * Area, MAX_HEIGHT, CHUNK_SIZE, CHUNK_SIZE,
                1, true, true, Vertices, Quads);

            for (auto& i : Quads) {
                i.i0 += Result_Vertices.size();
                i.i1 += Result_Vertices.size();
                i.i2 += Result_Vertices.size();
                i.i3 += Result_Vertices.size();
            }

            for (auto& i : Vertices) {
                i.y += CHUNK_SIZE * X;
                i.z += CHUNK_SIZE * Y;

            }

            Result_Vertices.insert(Result_Vertices.end(), Vertices.begin(), Vertices.end());
            Result_Quads.insert(Result_Quads.end(), Quads.begin(), Quads.end());

            Chunk_Index++;
        }
    }

    Output_Node = Result_Vertices;
    Output_Cube = Transform_Quad_To_Cube(Result_Quads);
}
