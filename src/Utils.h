#ifndef __UTILS_H_
#define __UTILS_H_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

#include "../Dependencies/Simplex/Simplex.h"

namespace TerGen{

    namespace Layer{

        inline std::string GROUND = "GROUND";           // Height map generation
        inline std::string TEMPERATURE = "TEMPERATURE"; // Temperature map generation
        inline std::string HUMIDITY = "HUMIDITY";       // Humidity map generation
        inline std::string BIOME = "BIOME";             // Biome map generation
        inline std::string EROSION = "EROSION";         // Erosion map generation

    }

    class Generator{
    public:
        SimplexNoise* Noise;

        float Frequency;
        float Amplitude;
        float Lacuranity;
        float Persistent;
        float Seed;
        float FBM_Octaves;
        float WARP_Octaves;
        
        std::vector<float> WARP_Offsets;

        Generator(float freq = 0.1, float amp = 1, float lac = 4, float per = 0.3, float sed = 1, float fbm_octaves = 4, float warp_octaves = 2){
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
    };

    inline std::map<std::string, Generator> Layers;

    std::vector<std::string> Split(const std::string& s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (std::getline(ss, item, delim)) {
            result.push_back(item);
        }

        return result;
    }

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
    };

    static unsigned long x = 123456789, y = 362436069, z = 521288629;

    unsigned long Rand() {          //period 2^96-1
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

    void Init_Utils(std::map<std::string, Generator> layers){
        Layers = layers;
    }

    float FBM(Vector2 Position, Generator* generator){
        return generator->Noise->fractal(generator->FBM_Octaves, Position.x, Position.y);
    }

    float Noise(Vector2 Position, Generator* generator){
        return generator->Noise->noise(Position.x, Position.y);
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

}

#endif