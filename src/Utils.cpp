#include "Utils.h"
#include "Data.h"
#include "Core.h"

namespace TerGen{
    float Current_Seed = 0;

    Generator::Generator(float freq, float amp, float lac, float per, float sed, float fbm_octaves, float warp_octaves){
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
                WARP_Offsets.push_back((float)rand() / INT32_MAX * 10000);
            }
        }
    }

    std::vector<std::string> Split(const std::string& s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (std::getline(ss, item, delim)) {
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

    int Sign(float x)
    {
        if (x >= 0)
            return 1;
        else
            return -1;
    }

    int Clamp(int x, std::pair<int, int> MinMax) {
        return std::min(std::max(x, MinMax.first), MinMax.second);
    }

    void Init_Utils(float seed = -1){
        srand(time(NULL));
        
        if (seed == -1)
            seed = rand();

        Current_Seed = seed;

        Generators[Layer::GROUND] = {
            Construct_Single_Layer_Continent_Generator(MEGAMETER),
            Construct_Multi_Layer_Continent_Generator(MEGAMETER * 10, 4)
        };

        for (auto& g : Generators[Layer::GROUND]){

            Layers[Layer::GROUND].push_back(
                [=](Vector2 p){
                    Generator* tmp = new Generator(g); 

                    return FBM(p, (Generator*)&g);
                }
            );

        }
    }

    float FBM(Vector2 Position, Generator* generator){
        return generator->Noise->fractal(generator->FBM_Octaves, Position.x, Position.y);
    }

    float Noise(Vector2 Position, Generator* generator){
        return generator->Noise->noise(Position.x, Position.y);
    }

    float Noise(Vector3 Position, Generator* generator){
        return generator->Noise->noise(Position.x, Position.y, Position.z);
    }

    float Warp_Noise(Vector2 Position, Generator* generator) {
        float Result = 0;

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

    // Inits the chunk content.
    void Init(Chunk& new_chunk){

        //Init the childs.
        // for (int x = 0; x < new_chunk.Dimensions.x; x++)
        //     for (int y = 0; y < new_chunk.Dimensions.y; y++)
        //         new_chunk.Childs.push_back(Node(

        //             Warp_Noise({x + new_chunk.Position.x, y + new_chunk.Position.y}, &Layers[Layer::TEMPERATURE]),
        //             Warp_Noise({x + new_chunk.Position.x, y + new_chunk.Position.y}, &Layers[Layer::HUMIDITY]),
        //             Warp_Noise({x + new_chunk.Position.x, y + new_chunk.Position.y}, &Layers[Layer::GROUND])

        //         ));


    }

    Chunk* Get_Chunk(Vector3 Position, Vector2 Dimension){
        //Check if the chunk is already generated.
        if (Chunks.find(Position) != Chunks.end())
            return &Chunks[Position];

        //Create the chunk.
        Chunk chunk(Position, Dimension);

        //Init the chunk.
        Init(chunk);

        //Add the chunk to the chunk list.
        Chunks[Position] = chunk;

        //Return the chunk.
        return &Chunks[Position];
    }

    float Gather_All_Layers(Vector2 position, std::string Layer_Name){
        float Result = 0;

        std::vector<std::function<float(Vector2)>> Current_Layer = Layers[Layer_Name];

        for (auto f : Current_Layer) {
            Result += f(position);
        }

        return Result;
    }

    std::vector<Vector2> Get_Sparsely_Surrounding_Points(Vector2 Position, unsigned int Radius, unsigned int Point_Count){

        // The number of points to generate within the radius.
        const int numPoints = Point_Count;

        std::vector<Vector2> positions;

        // Calculate the spacing between the points.
        float spacing = Radius / std::sqrt(numPoints);

        // Generate the points in a grid pattern.
        for (float i = -Radius; i <= Radius; i += spacing)
        {
            for (float j = -Radius; j <= Radius; j += spacing)
            {
                // Calculate the position of the current point.
                float px = Position.x + i;
                float py = Position.y + j;

                // Calculate the distance between the current point and the origin point.
                float distance = std::sqrt(i * i + j * j);

                // If the distance is within the radius, add the point to the vector.
                if (distance <= Radius)
                {
                    positions.push_back(Vector2(px, py));
                }
            }
        }

        return positions;
    }

}