#include "Core.h"
#include "Data.h"

#include <math.h>

using namespace std;

namespace TerGen{

    // Returns a Generator, with the right options to suite the wanted octave.
    // Octave: 0 = Largest layer, Octave[lim]->inf: finer detail.
    Generator Construct_Single_Layer_Continent_Generator(int Octave){

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Octave + 1));

        double Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Octave + 1);

        Generator r(Frequency, Amplitude, Lacuranity, Persistence, Current_Seed, 1, 0);

        return r;
    }

    Generator Construct_Multi_Layer_Continent_Generator(int Start_Octave, int End_Octave){
        if (End_Octave < Start_Octave){
            End_Octave = Start_Octave + End_Octave;
        }

        int Octave_Different = End_Octave - Start_Octave;

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Start_Octave + 1));

        double Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Start_Octave + 1);

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
        // Uses: double derivative = (perlin_noise(x + epsilon, y) - perlin_noise(x, y)) / epsilon;
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

        double Elevation = Gather_All_Layers(Position, Layer::GROUND);

        if (Approximately(Elevation, AVERAGE_SEA_LEVEL, ERROR_RANGE))
            return true;
        
        double Humidity = Gather_All_Layers(Position, Layer::HUMIDITY);

        if (Approximately(Humidity, 1, ERROR_RANGE))
            return true;

        return false;
    }

    double Calculate_Humidity(Vector2 Position){
        long double Distance_Of_Closest_Body_Of_Water = Get_Distance_From_Closest_Body_Of_Water(Position);

        long double Current_Humidity = 1 - tanhl(Distance_Of_Closest_Body_Of_Water / WATER_HUMIDITY_RANGE);

        long double Equator_Distance = Get_Distance_From_Equator(Position);

        long double Equator_Humidity = 1 - tanhl(Equator_Distance / EQUATOR_DRYNESS_REACH);

        long double Final_Humidity = Current_Humidity * Equator_Humidity;

        return Final_Humidity;
    }

    double Calculate_Humidity(Vector2 Position, long double Distance_From_Closest_Body_Of_Water, long double Distance_From_Equator){
        long double Current_Humidity = 1 - tanhl(Distance_From_Closest_Body_Of_Water / WATER_HUMIDITY_RANGE);

        long double Equator_Humidity = 1 - tanhl(Distance_From_Equator / EQUATOR_DRYNESS_REACH);

        long double Final_Humidity = Current_Humidity * Equator_Humidity;

        return Final_Humidity;
    }

    void Construct_Humidity_Generator(int Start_Octave, int End_Octave){
        if (End_Octave < Start_Octave){
            End_Octave = Start_Octave + End_Octave;
        }

        int Octave_Different = End_Octave - Start_Octave;

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Start_Octave + 1));

        double Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Start_Octave + 1);

        // This is used to add some random noise to the final output.
        Generator Climate(Frequency, Amplitude, Lacuranity, Persistence, Current_Seed, Octave_Different, 0);

        Generators[Layer::HUMIDITY].push_back(Climate);

        Layers[Layer::HUMIDITY].push_back(
            [=](Vector2 p){
                // We will first fill the world with random values.
                return FBM(p, &Generators[Layer::HUMIDITY].back());
            }
        );
    }

    double Calculate_Temperature(Vector2 Position){
        long double Distance_From_Equator = Get_Distance_From_Equator(Position);

        long double Current_Heat = EQUATOR_MAX_HEAT - (Distance_From_Equator / EQUATOR_HEAT_RANGE);

        double Current_Elevation = Gather_All_Layers(Position, Layer::GROUND);

        return Current_Heat - Current_Elevation * ELEVATION_EFFECT_ON_TEMPERATURE;
    }

    double Calculate_Temperature(Vector2 Position, long double Distance_From_Equator, double Elevation){
        long double Current_Heat = EQUATOR_MAX_HEAT - (Distance_From_Equator / EQUATOR_HEAT_RANGE);

        return Current_Heat - Elevation * ELEVATION_EFFECT_ON_TEMPERATURE;
    }

    void Construct_Temperature_Generator(int Start_Octave, int End_Octave){
        if (End_Octave < Start_Octave){
            End_Octave = Start_Octave + End_Octave;
        }

        int Octave_Different = End_Octave - Start_Octave;

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Start_Octave + 1));

        double Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Start_Octave + 1);

        // This is used to add some random noise to the final output.
        Generator Climate(Frequency, Amplitude, Lacuranity, Persistence, Current_Seed, Octave_Different, 0);

        Generators[Layer::TEMPERATURE].push_back(Climate);

        Layers[Layer::TEMPERATURE].push_back(
            [=](Vector2 p){
                // We will first fill the world with random values.
                return FBM(p, &Generators[Layer::TEMPERATURE].back());
            }
        );
    }

    Vector2 Get_Wind_Current(Vector2 Position, long double Distance_From_Equator, double Elevation, double Humidity, double Temperature, double Rotation_Speed, Generator* g)
    {
        // Use noise functions to generate patterns of wind speed and direction
        double Wind_Speed = FBM({Position.x, Position.y}, g);
        double Wind_Direction = Wind_Speed;

        // Modify the wind speed and direction based on the distance from the equator and the average elevation of the surrounding nodes
        Wind_Speed *= 1.0f + Distance_From_Equator * 0.1f + Elevation * 0.01f;
        Wind_Direction += Distance_From_Equator * 0.1f + Elevation * 0.01f;

        // Modify the wind speed and direction based on the humidity and temperature of the surrounding area
        Wind_Speed *= 1.0f + Humidity * 0.1f + Temperature * 0.1f;
        Wind_Direction += Humidity * 0.1f + Temperature * 0.1f;

        // Add the rotation of the Earth to the wind direction
        Wind_Direction += Rotation_Speed * Position.y;

        // Convert the wind direction from an angle in radians to a Vector2 representing the wind current
        Vector2 windCurrent;
        windCurrent.x = cos(Wind_Direction);
        windCurrent.y = sin(Wind_Direction);

        // Scale the wind current by the wind speed
        windCurrent *= Wind_Speed;

        return windCurrent;
    }
    
    Vector2 Get_Wind_Current(Vector2 Position){
        return Vector2(
            FBM(Position, &Generators[Layer::WIND].back()),
            FBM(Position, &Generators[Layer::WIND].back())
        );
    }

    void Construct_Wind_Generator(int Start_Octave, int End_Octave){
        if (End_Octave < Start_Octave){
            End_Octave = Start_Octave + End_Octave;
        }

        int Octave_Different = End_Octave - Start_Octave;

        long double Frequency = AVERAGE_CONTINENTAL_AREA / (Cycles * (Start_Octave + 1));

        double Amplitude = AVERAGE_CONTINENTAL_HEIGHT / (Start_Octave + 1);

        // This is used to add some random noise to the final output.
        Generator Climate(Frequency, Amplitude, Lacuranity, Persistence, Current_Seed, Octave_Different, 0);

        Generators[Layer::WIND].push_back(Climate);
    }

    extern void Calculate_Climate(Chunk* c, int Batch_Size){

        int Batch_y = c->Dimensions.x;
        int Batch_x = c->Dimensions.y;

        int Current_Batch_Radius = Batch_Size / 2;
        long double Distance_Of_Closest_Body_Of_Water = Get_Distance_From_Closest_Body_Of_Water({Batch_x, Batch_y});
        Generator* Wind_Generator = &Generators[Layer::WIND].back();


        for (int Batch_y = 0; Batch_y + Batch_Size < c->Dimensions.x; Batch_y += Batch_Size){
            for (int Batch_x = 0; Batch_x + Batch_Size < c->Dimensions.y; Batch_x += Batch_Size){

                // Firstly gather all the average values.
                int Average_X = Batch_x + Current_Batch_Radius + c->Position.x;
                int Average_Y = Batch_y + Current_Batch_Radius + c->Position.y;

                double Average_Elevation = 0;
                double Average_Humidity = 0;
                double Average_Temperature = 0;

                double Average_Distance_From_Equator = Get_Distance_From_Equator({Average_X, Average_Y});

                for (auto p : Get_Sparsely_Surrounding_Points({Average_X, Average_Y}, Current_Batch_Radius, FOR_SURROUNDING_POINT_CHECK_FOR)){

                    Node Current_Node = c->Childs[p.x + p.y * c->Dimensions.x];

                    Average_Elevation += Current_Node.Height;
                    Average_Humidity += Current_Node.Humidity;
                    Average_Temperature += Current_Node.Temperature;

                }

                Average_Elevation /= FOR_SURROUNDING_POINT_CHECK_FOR;
                Average_Humidity /= FOR_SURROUNDING_POINT_CHECK_FOR;
                Average_Temperature /= FOR_SURROUNDING_POINT_CHECK_FOR;

                // Now use the average values to apply them to the nodes.
                for (int Current_Y = Batch_y; Current_Y < Batch_y + Batch_Size; Current_Y++){
                    for (int Current_X = Batch_x; Current_X < Batch_x + Batch_Size; Current_X++){

                        Node* Current_Node = &c->Childs[Current_X + Current_Y * c->Dimensions.x];

                        Current_Node->Humidity += 1.0f * Calculate_Humidity({Current_X, Current_Y}, Distance_Of_Closest_Body_Of_Water, Average_Distance_From_Equator);
                        Current_Node->Temperature += 1.0f * Calculate_Temperature({Current_X, Current_Y}, Average_Distance_From_Equator, Average_Elevation);

                        Current_Node->Wind_Current += Get_Wind_Current(
                            {Current_X, Current_Y},
                            Average_Distance_From_Equator,
                            Current_Node->Height,
                            Current_Node->Humidity,
                            Current_Node->Temperature,
                            GROUND_ROTATION,
                            Wind_Generator
                        ) * 1.0f;
                    }
                }

            }
        }

        // For those that did not fit into the batch size will be computed here:
        if (Batch_y < c->Dimensions.y && Batch_x < c->Dimensions.x){
            Calculate_Climate(c, Batch_Size / 2);
        }
    }

    // Starts to compute the Complex Humidity, Temperature, Pressure, Wind, etc..
    extern void Calculate_Climate(){
        for (auto& c : Chunks){

            Calculate_Climate(&c.second, BATCH_SIZE);

        }
    }

}