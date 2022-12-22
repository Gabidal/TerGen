#ifndef _CORE_H_
#define _CORE_H_

#include <vector>
#include <string>

#include "../Dependencies/Simplex/Simplex.h"
#include "Utils.h"

namespace TerGen{
    // To make cohesive climate with the ground elevation, we can use octave scaling.
    // The slowest changing oscillation could be for an example the weather.

    // The constant namings go like this:
    // Amplitude = a, Frequency = f, Scaler = s
    // a * noise(x/f, x/f) / s
    // Where the noise could be just:
    // noise(x, y) = sin(x) + sin(y)

    // NOTE: value: 1 = 1m (one meter)
    // NOTE: The calculations below DO NOT represent real world directly, but uses them as a reference point.
    // the values concluded from the calculations are manipulated so that the outcome is preferable for terrain generation code.  

    // Calculations for the average continental area:
    // SRC: https://www.enchantedlearning.com/geography/continents/Land.shtml
    // 44,579,000: 30%
    // 30,065,000: 20.3%
    // 24,256,000: 16.3%
    // 17,819,000: 12%
    // 13,209,000: 8.9%
    // 9,938,000: 6.7%
    // 7,687,000: 5.2%
    // So the average would be: 44,579,000 * 0.30 + 30,065,000 * 0.203 + 24,256,000 * 0.163 + 17,819,000 * 0.12 + 13,209,000 * 0.089 + 9,938,000 * 0.067 + 7,687,000 * 0.052
    // 27,810,074 Sq Km
    // NOTE: this is not your typical calculation to calculate the average a.k.a: sum(list of n)/list.size()
    inline const long double AVERAGE_CONTINENTAL_AREA = 27810074;

    // x * Scale cycle = continent, determines how many cycles the algorithm can do in an area.
    inline const unsigned int Cycles = 10; 

    // Now lets calculate the average amplitude.
    // SRC: https://en.wikipedia.org/wiki/Earth
    // Lowest point: -431m
    // Highest point: 8848m
    // Now lets move the values to start from 0:
    // Lowest point: 0m
    // Highest point: 8848m + 431m = 9279m
    // So the average height would simply be: 9279/2 = 4639.5m
    inline const float AVERAGE_CONTINENTAL_HEIGHT = 4639.5f;

    // We can also calculate the average sea level from the lowest point.
    inline const unsigned int AVERAGE_SEA_LEVEL = 431;

    // Lacuranity: how quickly the frequency increases for each successive octave
    // The greater the value, less overall change gradient between octaves.
    // In other words, use big number and the details hop between big and small changes.
    // And use small number and the changes between the big and small is less. 
    inline const float Lacuranity = 0.25f;

    // Persistence: how much each octave contributes to the overall structure of the noise map
    // The greater the value, the more each successive octave will contribute to the overall noise map.
    // In other words, use big number and the details that the later octaves make are more visible.
    // And thus the first octaves contribute almost nothing.
    inline const float Persistence = 0.2f;

    // Useful constants:
    inline const unsigned int GIGAMETER = 1000000000;
    inline const unsigned int MEGAMETER = 1000000;
    inline const unsigned int KILOMETER = 1000;
    inline const unsigned int METER = 1;

    // INTERNAL:
    unsigned int FOR_SURROUNDING_POINT_CHECK_FOR = 50;
    unsigned int FOR_SURROUNDING_POINT_REACH = KILOMETER;

    extern Generator Construct_Single_Layer_Continent_Generator(unsigned int Octave);
    
    extern Generator Construct_Multi_Layer_Continent_Generator(unsigned int Start_Octave, unsigned int End_Octave);

    // Now we will start to calculate the right constants for climate.
    // The Equators center is where ever the Y coordinate is 0. This will make a infinite line of equator.
    extern long double Get_Distance_From_Equator(Vector2 Current_Position);
    extern long double Get_Distance_From_Equator(Vector3 Current_Position);

    extern long double Get_Distance_From_Closest_Body_Of_Water(Vector2 Current_Position);

    extern Generator Construct_Multi_Layer_Climate_Generator(unsigned int Start_Octave, unsigned int End_Octave);

}

#endif