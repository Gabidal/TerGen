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
    vector<Func*> Applied_Layers;
    //the generated terrain
    vector<vector<vector<Chunk>>> Terrain;
public:
    TerGen() {}
    void Add_Function(vector<Func*> f) {
        for (auto i : f)
            Applied_Layers.push_back(i);
        return;
    }
    void Smooth_Terrain(double alpha = 0.0) {
        if (alpha != 0.0)
            Alpha = alpha;
        for (auto f : Applied_Layers)
            for (auto cx : Terrain)
                for (auto cy : cx)
                    for (auto cz : cy)
                        for (auto tx : cz.Tiles)
                            for (auto ty : tx)
                                for (auto tz : ty) {

                                }

    }
};

#endif