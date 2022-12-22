#ifndef __UTILS_H_
#define __UTILS_H_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>

#include "../Dependencies/Simplex/Simplex.h"

namespace TerGen{
    extern float Current_Seed;

    namespace Layer{

        inline std::string GROUND = "GROUND";           // Height map generation
        inline std::string TEMPERATURE = "TEMPERATURE"; // Temperature map generation
        inline std::string HUMIDITY = "HUMIDITY";       // Humidity map generation

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

        Generator(float freq = 0.1, float amp = 1, float lac = 4, float per = 0.3, float sed = 1, float fbm_octaves = 4, float warp_octaves = 2);
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
    inline std::map<std::string, std::vector<std::function<float(Vector2)>>> Layers;

    std::vector<std::string> Split(const std::string& s, char delim);

    extern unsigned long Rand();

    extern int Sign(float x);

    extern int Clamp(int x, std::pair<int, int> MinMax);

    extern void Init_Utils(float seed = -1);

    extern float FBM(Vector2 Position, Generator* generator);

    extern float Noise(Vector2 Position, Generator* generator);

    extern float Noise(Vector3 Position, Generator* generator);

    extern float Warp_Noise(Vector2 Position, Generator* generator);

    extern class Chunk* Get_Chunk(Vector3 Position, Vector2 Dimension);

    extern float Gather_All_Layers(Vector2, std::string Layer_Name);

    // Returns a list of points that are close to the given origin.
    extern std::vector<Vector2> Get_Sparsely_Surrounding_Points(Vector2 Position, unsigned int Radius, unsigned int Point_Count);

}

#endif