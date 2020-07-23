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
    void Factory();
    void Detect_Chunk(int i) {
        //the idea of going layer by layer like in Evie.
    }
};

#endif