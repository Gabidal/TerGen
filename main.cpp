#include <vector>
#include <iostream>
#include <Windows.h>

#include "Tile/Tile.h"
#include "Tile/Simplex/SimplexNoise.h"

using namespace std;
TerGen* t;
float FREQ;
SimplexNoise* sm;

int simplex(Chunk&, vector<long> input) {
    return (sm->noise(input[0] / 1000.0f, input[1] / 1000.0f, input[2] / 1000.0f) + 1) / 2 * 3;
}
__declspec(dllexport)
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

__declspec(dllexport)
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
__declspec(dllexport)
void Generate_Map(int chunk_amount, int chunk_scale, float freq) {
    FREQ = freq;
    sm = new SimplexNoise(FREQ, 0.3f, 0.3f, 0.3f);
    t = new TerGen(chunk_amount, chunk_scale);
    t->Add_Function(simplex);
    t->Apply_Functions();
}