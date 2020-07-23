#ifndef _TERGEN_H_
#define _TERGEN_H_

#include "Components/Chunk.h"
#include "Func/Func.h"

#include <iostream>
#include <vector>

using namespace std;

class TerGen {
private:
    //the smoothness ratio between noise layers
    double Alpha = 0.0;
    //noise functions
    vector<Func*> Functions;
    //the generated terrain
    vector<Chunk> Terrain;
    //Derivative path finding generation scale
    int Derivate_Distance = 0;
public:
    TerGen() {}
    void Add_Function(vector<Func*> f) {
        for (auto i : f)
            Functions.push_back(i);
        return;
    }
    void Use_Functions(Dot Starting_Location, Dot Ending_Location) {
        for (auto f : Functions) {

        }
    }
    void Use_Functions() {
        for (auto f : Functions) {
            for (Chunk* c : Terrain)
                for (Layer* l : c->Chunk)
                    for (auto rows : l->Layer)
                        for (auto tile : rows)
                            tile = f->Function({ tile.X + l->X, tile.Y + l->Y, tile.Z + l->Z, tile.Texture });
        }
        return;
    }
};

#endif