#include "Core.h"
#include "Data.h"

namespace TerGen{

    // Returns a Generator, with the right options to suite the wanted octave.
    // Octave: 0 = Largest layer, Octave[lim]->inf: finer detail.
    Generator Construct_Single_Layer_Continent_Generator(unsigned int Octave){

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Octave + 1));

        float Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Octave + 1);

        Generator r(Frequency, Amplitude, Lacuranity, Persistence, Current_Seed, 1, 0);

        return r;
    }

    Generator Construct_Multi_Layer_Continent_Generator(unsigned int Start_Octave, unsigned int End_Octave){
        if (End_Octave < Start_Octave){
            End_Octave = Start_Octave + End_Octave;
        }

        unsigned int Octave_Different = End_Octave - Start_Octave;

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Start_Octave + 1));

        float Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Start_Octave + 1);

        Generator r(Frequency, Amplitude, Lacuranity, Persistence, Current_Seed, Octave_Different, 0);

        return r;
    }

    long double Get_Distance_From_Equator(Vector2 Current_Position){
        Vector2 Equator = {Current_Position.x, 0};

        return sqrt(pow(Current_Position.x - Equator.x, 2) + pow(Current_Position.y - Equator.y, 2));
    }

    long double Get_Distance_From_Equator(Vector3 Current_Position){
        Vector3 Equator = {Current_Position.x, 0, Current_Position.z};

        return sqrt(pow(Current_Position.x - Equator.x, 2) + pow(Current_Position.y - Equator.y, 2) + pow(Current_Position.z - Equator.z, 2));
    }

    long double Get_Distance_From_Closest_Body_Of_Water(Vector2 Current_Position){
        // Uses: float derivative = (perlin_noise(x + epsilon, y) - perlin_noise(x, y)) / epsilon;

        for (auto Point : Get_Sparsely_Surrounding_Points(Current_Position, FOR_SURROUNDING_POINT_CHECK_FOR, FOR_SURROUNDING_POINT_REACH)){

        }
    }

}