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
        long double Closest_Distance = INT32_MAX;

        for (auto Point : Get_Sparsely_Surrounding_Points(Current_Position, FOR_SURROUNDING_POINT_CHECK_FOR, FOR_SURROUNDING_POINT_REACH)){

            if (Is_Water(Point)){
                if (sqrt(pow(Point.x - Current_Position.x, 2) + pow(Point.y - Current_Position.y, 2)) < Closest_Distance){
                    Closest_Distance = sqrt(pow(Point.x - Current_Position.x, 2) + pow(Point.y - Current_Position.y, 2));
                }
            }

        }

        return Closest_Distance;
    }

    bool Is_Water(Vector2 Position){

        float Elevation = Gather_All_Layers(Position, Layer::GROUND);

        if (Approximately(Elevation, AVERAGE_SEA_LEVEL, ERROR_RANGE))
            return true;
        
        float Humidity = Gather_All_Layers(Position, Layer::HUMIDITY);

        if (Approximately(Humidity, 1, ERROR_RANGE))
            return true;

        return false;
    }

    float Calculate_Humidity(Vector2 Position, Generator* g){
        long double Distance_Of_Closest_Body_Of_Water = Get_Distance_From_Closest_Body_Of_Water(Position);

        long double Current_Humidity = 1 - tanhl(Distance_Of_Closest_Body_Of_Water / WATER_HUMIDITY_RANGE);

        long double Equator_Distance = Get_Distance_From_Equator(Position);

        long double Equator_Humidity = 1 - tanhl(Equator_Distance / EQUATOR_DRYNESS_REACH);

        long double Final_Humidity = Current_Humidity * Equator_Humidity;

        return Final_Humidity;
    }

    void Construct_Humidity_Generator(unsigned int Start_Octave, unsigned int End_Octave){
        if (End_Octave < Start_Octave){
            End_Octave = Start_Octave + End_Octave;
        }

        unsigned int Octave_Different = End_Octave - Start_Octave;

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Start_Octave + 1));

        float Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Start_Octave + 1);

        // This is used to add some random noise to the final output.
        Generator Climate(Frequency, Amplitude, Lacuranity, Persistence, Current_Seed, Octave_Different, 0);

        Generators[Layer::HUMIDITY].push_back(Climate);

        Layers[Layer::HUMIDITY].push_back(
            [=](Vector2 p){
                return Calculate_Humidity(p, &Generators[Layer::HUMIDITY].back());
            }
        );

    }

    float Calculate_Temperature(Vector2 Position, Generator* g){
        long double Distance_From_Equator = Get_Distance_From_Equator(Position);

        long double Current_Heat = EQUATOR_MAX_HEAT - (Distance_From_Equator / EQUATOR_HEAT_RANGE);

        float Current_Elevation = Gather_All_Layers(Position, Layer::GROUND);

        return Current_Heat - Current_Elevation * ELEVATION_EFFECT_ON_TEMPERATURE;
    }

    void Construct_Temperature_Generator(unsigned int Start_Octave, unsigned int End_Octave){
        if (End_Octave < Start_Octave){
            End_Octave = Start_Octave + End_Octave;
        }

        unsigned int Octave_Different = End_Octave - Start_Octave;

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Start_Octave + 1));

        float Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Start_Octave + 1);

        // This is used to add some random noise to the final output.
        Generator Climate(Frequency, Amplitude, Lacuranity, Persistence, Current_Seed, Octave_Different, 0);

        Generators[Layer::TEMPERATURE].push_back(Climate);

        Layers[Layer::TEMPERATURE].push_back(
            [=](Vector2 p){
                return Calculate_Temperature(p, &Generators[Layer::TEMPERATURE].back());
            }
        );
    }

}