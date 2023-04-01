#ifndef _TERGEN_H_
#define _TERGEN_H_

#include <vector>
#include <string>
#include <map>
#include <functional>

#include "../Dependencies/Simplex/Simplex.h"

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
    inline const int Cycles = 10; 

    // Now lets calculate the average amplitude.
    // SRC: https://en.wikipedia.org/wiki/Earth
    // Lowest point: -431m
    // Highest point: 8848m
    // Now lets move the values to start from 0:
    // Lowest point: 0m
    // Highest point: 8848m + 431m = 9279m
    // So the average height would simply be: 9279/2 = 4639.5m
    inline const double AVERAGE_CONTINENTAL_HEIGHT = 4639.5f;

    // We can also calculate the average sea level from the lowest point.
    inline const int AVERAGE_SEA_LEVEL = 431;

    // Lacuranity: how quickly the frequency increases for each successive octave
    // The greater the value, less overall change gradient between octaves.
    // In other words, use big number and the details hop between big and small changes.
    // And use small number and the changes between the big and small is less. 
    inline const double Lacuranity = 0.25f;

    // Persistence: how much each octave contributes to the overall structure of the noise map
    // The greater the value, the more each successive octave will contribute to the overall noise map.
    // In other words, use big number and the details that the later octaves make are more visible.
    // And thus the first octaves contribute almost nothing.
    inline const double Persistence = 0.2f;

    // Useful constants:
    inline const int GIGAMETER = 1000000000;
    inline const int MEGAMETER = 1000000;
    inline const int KILOMETER = 1000;
    inline const int METER = 1;

    // INTERNAL:
    inline int FOR_SURROUNDING_POINT_CHECK_FOR = 50;
    inline int FOR_SURROUNDING_POINT_REACH = KILOMETER;

    // Close by half of the values of A & B.
    inline long double ERROR_RANGE = 0.5f; 

    // The range in which the sea/lakes reach their humidity to.
    inline const int WATER_HUMIDITY_RANGE = 150 * KILOMETER;
    inline const int EQUATOR_DRYNESS_REACH = 1500 * KILOMETER;

    inline const int EQUATOR_HEAT_RANGE = 8500 * KILOMETER;
    inline const int EQUATOR_MAX_HEAT = 100; 
    inline const double ELEVATION_EFFECT_ON_TEMPERATURE = 0.5f; 

    // The constants for the wind current clalculations.
    inline const double GROUND_ROTATION = 1670 * KILOMETER;

    
    extern double Current_Seed;

    namespace Layer{

        inline std::string GROUND = "GROUND";           // Height map generation
        inline std::string TEMPERATURE = "TEMPERATURE"; // Temperature map generation
        inline std::string HUMIDITY = "HUMIDITY";       // Humidity map generation
        inline std::string WIND = "WIND";               // Wind map generation

    }

    class Generator{
    public:
        SimplexNoise* Noise;

        double Frequency;
        double Amplitude;
        double Lacuranity;
        double Persistent;
        double Seed;
        double FBM_Octaves;
        double WARP_Octaves;
        
        std::vector<double> WARP_Offsets;

        Generator(double freq = 0.1, double amp = 1, double lac = 4, double per = 0.3, double sed = 1, double fbm_octaves = 4, double warp_octaves = 2);
    };

    class Vector2{
    public:
        int x;
        int y;

        Vector2(int x, int y) {
            this->x = x;
            this->y = y;
        }

        Vector2() {
            this->x = 0;
            this->y = 0;
        }

        Vector2 operator+(const Vector2& v) {
            return Vector2(x + v.x, y + v.y);
        }

        Vector2 operator-(const Vector2& v) {
            return Vector2(x - v.x, y - v.y);
        }

        Vector2 operator*(const Vector2& v) {
            return Vector2(x * v.x, y * v.y);
        }

        Vector2 operator/(const Vector2& v) {
            return Vector2(x / v.x, y / v.y);
        }

        Vector2 operator+(const int& f) {
            return Vector2(x + f, y + f);
        }

        Vector2 operator-(const int& f) {
            return Vector2(x - f, y - f);
        }

        Vector2 operator*(const int& f) {
            return Vector2(x * f, y * f);
        }

        Vector2 operator/(const int& f) {
            return Vector2(x / f, y / f);
        }

        Vector2& operator+=(const Vector2& v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vector2& operator*=(const Vector2& v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        Vector2& operator/=(const Vector2& v) {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        Vector2& operator+=(const int& f) {
            x += f;
            y += f;
            return *this;
        }

        Vector2& operator-=(const int& f) {
            x -= f;
            y -= f;
            return *this;
        }

        Vector2& operator*=(const int& f) {
            x *= f;
            y *= f;
            return *this;
        }

        Vector2& operator/=(const int& f) {
            x /= f;
            y /= f;
            return *this;
        }

        bool operator==(const Vector2& v) {
            return x == v.x && y == v.y;
        }

        bool operator!=(const Vector2& v) {
            return x != v.x || y != v.y;
        }

        bool operator<(const Vector2& v) {
            return x < v.x && y < v.y;
        }

        bool operator>(const Vector2& v) {
            return x > v.x && y > v.y;
        }

    };

    class Vector3{
    public:
        int x;
        int y;
        int z;

        Vector3(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vector3() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }

        Vector3 operator+(const Vector3& v) {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        Vector3 operator-(const Vector3& v) {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        Vector3 operator*(const Vector3& v) {
            return Vector3(x * v.x, y * v.y, z * v.z);
        }

        Vector3 operator/(const Vector3& v) {
            return Vector3(x / v.x, y / v.y, z / v.z);
        }

        Vector3 operator+(const int& f) {
            return Vector3(x + f, y + f, z + f);
        }

        Vector3 operator-(const int& f) {
            return Vector3(x - f, y - f, z - f);
        }

        Vector3 operator*(const int& f) {
            return Vector3(x * f, y * f, z * f);
        }

        Vector3 operator/(const int& f) {
            return Vector3(x / f, y / f, z / f);
        }

        Vector3& operator+=(const Vector3& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vector3& operator-=(const Vector3& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        Vector3& operator*=(const Vector3& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        Vector3& operator/=(const Vector3& v) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        Vector3& operator+=(const int& f) {
            x += f;
            y += f;
            z += f;
            return *this;
        }

        Vector3& operator-=(const int& f) {
            x -= f;
            y -= f;
            z -= f;
            return *this;
        }

        Vector3& operator*=(const int& f) {
            x *= f;
            y *= f;
            z *= f;
            return *this;
        }

        Vector3& operator/=(const int& f) {
            x /= f;
            y /= f;
            z /= f;
            return *this;
        }
    
        bool operator==(const Vector3& v) {
            return x == v.x && y == v.y && z == v.z;
        }

        bool operator!=(const Vector3& v) {
            return x != v.x || y != v.y || z != v.z;
        }

        bool operator<(const Vector3& v) {
            return x < v.x && y < v.y && z < v.z;
        }

        bool operator>(const Vector3& v) {
            return x > v.x && y > v.y && z > v.z;
        }

        friend bool operator==(const Vector3& v, const Vector3& v2) {
            return v.x == v2.x && v.y == v2.y && v.z == v2.z;
        }

        friend bool operator!=(const Vector3& v, const Vector3& v2) {
            return v.x != v2.x || v.y != v2.y || v.z != v2.z;
        }

        friend bool operator<(const Vector3& v, const Vector3& v2) {
            return v.x < v2.x && v.y < v2.y && v.z < v2.z;
        }

        friend bool operator>(const Vector3& v, const Vector3& v2) {
            return v.x > v2.x && v.y > v2.y && v.z > v2.z;
        }

    };

    inline std::map<std::string, std::vector<Generator>> Generators;
    inline std::map<std::string, std::vector<std::function<double(Vector2)>>> Layers;

    // This hold all the data.
    class Node{
    public:
        double Temperature;
        double Humidity;         // When humidity is 1, then water.
        Vector2 Wind_Current;

        double Height;

        Node(){}

        Node(double height, double humidity, double temperature){
            Height = height;
            Humidity = humidity;
            Temperature = temperature;
            Wind_Current = Vector2(0, 0);
        }

    };

    class Chunk{
    public:
        Vector3 Position;
        Vector2 Dimensions;

        std::vector<Node> Childs;
        
        Chunk(){}

        // NOTE: This automatically setups the elevation for its contents.
        Chunk(Vector3 position, Vector2 dimensions);
    };

    inline std::map<Vector3, Chunk> Chunks;

    std::vector<std::string> Split(const std::string& s, char delim);

    extern unsigned long Rand();

    extern int Sign(double x);

    extern int Clamp(int x, std::pair<int, int> MinMax);

    extern void Init_Utils(double seed = -1);

    extern double FBM(Vector2 Position, Generator* generator);

    extern double Noise(Vector2 Position, Generator* generator);

    extern double Noise(Vector3 Position, Generator* generator);

    extern double Warp_Noise(Vector2 Position, Generator* generator);

    extern class Chunk* Get_Chunk(Vector3 Position, Vector2 Dimension);

    extern double Gather_All_Layers(Vector2, std::string Layer_Name);

    // Returns a list of points that are close to the given origin.
    extern std::vector<Vector2> Get_Sparsely_Surrounding_Points(Vector2 Position, int Radius, int Point_Count);
    
    extern bool Approximately(long double A, long double B, long double Range);

    extern Generator Construct_Single_Layer_Continent_Generator(int Octave);
    
    extern Generator Construct_Multi_Layer_Continent_Generator(int Start_Octave, int End_Octave);

    // Now we will start to calculate the right constants for climate.
    // The Equators center is where ever the Y coordinate is 0. This will make a infinite line of equator.
    extern long double Get_Distance_From_Equator(Vector2 Current_Position);
    extern long double Get_Distance_From_Equator(Vector3 Current_Position);

    extern long double Get_Distance_From_Closest_Body_Of_Water(Vector2 Current_Position);

    // Conditions to return true:
    // - If the GROUND generator gives an elevation of AVERAGE_SEA_LEVEL or lower.
    // - If the HUMIDITY generator gives a value of 1.
    extern bool Is_Water(Vector2 Position);

    extern double Calculate_Humidity(Vector2 Position);
    extern double Calculate_Humidity(Vector2 Position, long double Distance_From_Closest_Body_Of_Water, long double Distance_From_Equator);

    extern void Construct_Humidity_Generator(int Start_Octave, int End_Octave);

    extern double Calculate_Temperature(Vector2 Position);
    extern double Calculate_Temperature(Vector2 Position, long double Distance_From_Equator, double Elevation);

    extern void Construct_Temperature_Generator(int Start_Octave, int End_Octave);

    extern Vector2 Get_Wind_Current(Vector2 Position, long double Distance_From_Equator, double Elevation, double Humidity, double Temperature, double Rotation_Speed, Generator* g);


    extern Vector2 Get_Wind_Current(Vector2 Position);
    extern void Construct_Wind_Generator(int Start_Octave, int End_Octave);

    // For complex CLIMATE:
    inline int BATCH_SIZE = 10;    // The lower the value the more accurate simulation. 10 = 10x10 area.

    // Starts to compute the Complex Humidity, Temperature, Pressure, Wind, etc..
    extern void Calculate_Climate(Chunk* c, int Batch_Size);
    extern void Calculate_Climate();

}

#endif