/**
 * @file    SimplexNoise.h
 * @brief   A Perlin Simplex Noise C++ Implementation (1D, 2D, 3D).
 *
 * Copyright (c) 2014-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <cstddef>  // size_t

 /**
  * @brief A Perlin Simplex Noise C++ Implementation (1D, 2D, 3D, 4D).
  */
class SimplexNoise {
public:
    // 1D Perlin simplex noise
    static double noise(double x);
    // 2D Perlin simplex noise
    static double noise(double x, double y);
    // 3D Perlin simplex noise
    static double noise(double x, double y, double z);

    // Fractal/Fractional Brownian Motion (fBm) noise summation
    double fractal(size_t octaves, double x) const;
    double fractal(size_t octaves, double x, double y) const;
    double fractal(size_t octaves, double x, double y, double z) const;

    /**
     * Constructor of to initialize a fractal noise summation
     *
     * @param[in] frequency    Frequency ("width") of the first octave of noise (default to 1.0)
     * @param[in] amplitude    Amplitude ("height") of the first octave of noise (default to 1.0)
     * @param[in] lacunarity   Lacunarity specifies the frequency multiplier between successive octaves (default to 2.0).
     * @param[in] persistence  Persistence is the loss of amplitude between successive octaves (usually 1/lacunarity)
     */
    explicit SimplexNoise(double frequency = 1.0f,
        double amplitude = 1.0f,
        double lacunarity = 2.0f,
        double persistence = 0.5f,
        double seed = 0) :
        mFrequency(frequency),
        mAmplitude(amplitude),
        mLacunarity(lacunarity),
        mPersistence(persistence), 
        Seed(seed) {
    }

private:
    // Parameters of Fractional Brownian Motion (fBm) : sum of N "octaves" of noise
    double mFrequency;   ///< Frequency ("width") of the first octave of noise (default to 1.0)
    double mAmplitude;   ///< Amplitude ("height") of the first octave of noise (default to 1.0)
    double mLacunarity;  ///< Lacunarity specifies the frequency multiplier between successive octaves (default to 2.0).
    double mPersistence; ///< Persistence is the loss of amplitude between successive octaves (usually 1/lacunarity)
    double Seed;

};