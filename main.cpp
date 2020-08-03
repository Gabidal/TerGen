#include <vector>
#include <iostream>

#include "Tile/Tile.h"
#include "Tile/Simplex/FastNoise.h"

using namespace std;
TerGen* t;
int Seed;
FastNoise* sm;

int simplex(Chunk&, vector<long> input) {
    int r = sm->GetPerlin(input[0], input[1] / 10.0f, input[2] / 100.0f) * 100;
    //int r = ((sm->noise(input[0] / 10000.0f, input[1] / 10000.0f, input[2] / 10000.0f) ) * 5000);
    return r;
}

/*__declspec(dllexport)
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}*/

int main() {
    sm = new FastNoise;
    t = new TerGen(1, 16);
    t->Add_Function(simplex);
    t->Apply_Functions();

    for (int x = 0; x < t->Chunk_Size; x++) {
        for (int y = 0; y < t->Chunk_Size; y++) {
            for (int z = 0; z < t->Chunk_Size; z++) {
                cout << t->Chunks[0][x + y * t->Chunk_Size + z * t->Chunk_Size * t->Chunk_Size].Type;
            }
            cout << endl;
        }
        cout << endl << endl;
    }
}

//__declspec(dllexport)
int Get_Type(int x, int y, int z) {
    int cx = floor(x / t->Chunk_Size);
    int cy = floor(y / t->Chunk_Size);
    int cz = floor(z / t->Chunk_Size);

    int ix = x % t->Chunk_Size;
    int iy = y % t->Chunk_Size;
    int iz = z % t->Chunk_Size;

    Chunk& c = t->Chunks[cx + cy * t->Scale + cz * t->Scale * t->Scale];
    
    return c[ix + iy * t->Chunk_Size + iz * t->Chunk_Size * t->Chunk_Size].Type;
}

//__declspec(dllexport)
void Generate_Map(int chunk_amount, int chunk_scale, int seed) {
    Seed = seed;
    sm = new FastNoise();
    t = new TerGen(chunk_amount, chunk_scale);
    t->Add_Function(simplex);
    t->Apply_Functions();
}