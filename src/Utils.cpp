#include "Utils.h"
#include "Data.h"
#include "Core.h"

#include <math.h>

using namespace std;

namespace TerGen{
    double Current_Seed = 0;

    Generator::Generator(double freq, double amp, double lac, double per, double sed, double fbm_octaves, double warp_octaves){
        Frequency = freq;
        Amplitude = amp;
        Lacuranity = lac;
        Persistent = per;
        Seed = sed;
        FBM_Octaves = fbm_octaves;
        WARP_Octaves = warp_octaves;

        Noise = new SimplexNoise(Frequency, Amplitude, Lacuranity, Persistent, Seed);

        for (int i = 0; i < WARP_Octaves; i++) {
            for (int j = 0; j < 2 + 2; j++) {
                WARP_Offsets.push_back((double)rand() / INT32_MAX * 10000);
            }
        }
    }

    vector<string> Split(const string& s, char delim) {
        vector<string> result;
        stringstream ss(s);
        string item;

        while (getline(ss, item, delim)) {
            result.push_back(item);
        }

        return result;
    }

    unsigned long Rand() {          //period 2^96-1
        static unsigned long x = 123456789, y = 362436069, z = 521288629;
        unsigned long t;
        x ^= x << 16;
        x ^= x >> 5;
        x ^= x << 1;

        t = x;
        x = y;
        y = z;
        z = t ^ x ^ y;

        return z;
    }

    int Sign(double x)
    {
        if (x >= 0)
            return 1;
        else
            return -1;
    }

    int Clamp(int x, pair<int, int> MinMax) {
        return min(max(x, MinMax.first), MinMax.second);
    }

    void Init_Utils(double seed){
        if (seed == -1)
            srand(time(NULL));
            seed = rand();

        Current_Seed = seed;

        Generators[Layer::GROUND] = {
            Construct_Single_Layer_Continent_Generator(0)
        };

        Construct_Humidity_Generator(MEGAMETER * 10, 1);
        Construct_Temperature_Generator(MEGAMETER * 10, 1);
        Construct_Wind_Generator(MEGAMETER * 10, 1);

        for (auto& g : Generators[Layer::GROUND]){

            Layers[Layer::GROUND].push_back(
                [=](Vector2 p){
                    Generator* tmp = new Generator(g); 

                    return FBM(p, (Generator*)&g);
                }
            );

        }
    }

    double FBM(Vector2 Position, Generator* generator){
        return generator->Noise->fractal(generator->FBM_Octaves, Position.x, Position.y);
    }

    double Noise(Vector2 Position, Generator* generator){
        return generator->Noise->noise(Position.x, Position.y);
    }

    double Noise(Vector3 Position, Generator* generator){
        return generator->Noise->noise(Position.x, Position.y, Position.z);
    }

    double Warp_Noise(Vector2 Position, Generator* generator) {
        double Result = 0;

        const int R1_A_Index = 0;
        const int R1_B_Index = 1;
        const int R2_A_Index = 2;
        const int R2_B_Index = 3;

        const int Index_Page_Size = 4;

        //For every loop we make a new p + fbm(p) to the current value.
        Vector2 Previous_Layer(0, 0);
        for (int i = 0; i < generator->WARP_Octaves; i++) {
            Vector2 R3 = Position + (Previous_Layer * i) + Vector2(generator->WARP_Offsets[i * Index_Page_Size + R1_A_Index], generator->WARP_Offsets[i * Index_Page_Size + R1_B_Index]);
            Vector2 R4 = Position + (Previous_Layer * i) + Vector2(generator->WARP_Offsets[i * Index_Page_Size + R2_A_Index], generator->WARP_Offsets[i * Index_Page_Size + R2_B_Index]);

            Previous_Layer = Vector2(
                
                FBM(R3, generator),
                FBM(R4, generator)

            );
        }

        Vector2 final_Layer = Position + (Previous_Layer * generator->WARP_Octaves);

        Result = FBM(
            final_Layer,
            generator
        );

        return Result;
    }

    // NOTE: This will automatically compute with the stupid mode. 
    Chunk::Chunk(Vector3 position, Vector2 dimensions){
        Position = position;
        Dimensions = dimensions;

        this->Childs.resize(Dimensions.x * Dimensions.y);

        for (int y = 0; y < Dimensions.y; y++) {
            for (int x = 0; x < Dimensions.x; x++) {
                
                this->Childs[x + y * Dimensions.x] = Node(
                    Gather_All_Layers(Vector2(Position.x + x, Position.y + y), Layer::GROUND),
                    Gather_All_Layers(Vector2(Position.x + x, Position.y + y), Layer::HUMIDITY),
                    Gather_All_Layers(Vector2(Position.x + x, Position.y + y), Layer::TEMPERATURE)
                );
            }
        }
    }

    Chunk* Get_Chunk(Vector3 Position, Vector2 Dimension){
        //Check if the chunk is already generated.
        if (Chunks.find(Position) != Chunks.end())
            return &Chunks[Position];

        //Create the chunk.
        Chunk chunk(Position, Dimension);

        //Add the chunk to the chunk list.
        Chunks[Position] = chunk;

        //Return the chunk.
        return &Chunks[Position];
    }

    double Gather_All_Layers(Vector2 position, string Layer_Name){
        double Result = 0;

        vector<function<double(Vector2)>> Current_Layer = Layers[Layer_Name];

        for (auto f : Current_Layer) {
            Result += f(position);
        }

        return Result;
    }

    vector<Vector2> Get_Sparsely_Surrounding_Points(Vector2 Position, int Radius, int Point_Count){

        // The number of points to generate within the radius.
        const int numPoints = Point_Count;

        vector<Vector2> positions;

        // Calculate the spacing between the points.
        double spacing = Radius / sqrt(numPoints);

        // Generate the points in a grid pattern.
        for (double i = -Radius; i <= Radius; i += spacing)
        {
            for (double j = -Radius; j <= Radius; j += spacing)
            {
                // Calculate the position of the current point.
                double px = Position.x + i;
                double py = Position.y + j;

                // Calculate the distance between the current point and the origin point.
                double distance = sqrt(i * i + j * j);

                // If the distance is within the radius, add the point to the vector.
                if (distance <= Radius)
                {
                    positions.push_back(Vector2(px, py));
                }
            }
        }

        return positions;
    }

    bool Approximately(long double A, long double B, long double Range){
        long double relErr = abs((A - B) / B);
        return relErr <= Range;
    }
}