#include "Utils.h"

using namespace std;

namespace TerGen{

    // Generates a random white noise page.
    vector<Decimal> Generate_White_Noise(int Width, int Height){
        vector<Decimal> White_Noise(Width * Height);

        for(int i = 0; i < Width * Height; i++){
            White_Noise[i] = (Decimal)rand() / (Decimal)RAND_MAX;
        }

        return White_Noise;
    }

    // Generates a perlin noise based page.
    vector<Decimal> Generate_Perlin_Noise(int Width, int Height){

        

    }

}