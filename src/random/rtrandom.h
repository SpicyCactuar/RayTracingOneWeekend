#ifndef RAYTRACINGONEWEEKEND_RTRANDOM_H
#define RAYTRACINGONEWEEKEND_RTRANDOM_H

#include <random>

inline double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min,max)
    return min + (max - min) * randomDouble();
}

#endif //RAYTRACINGONEWEEKEND_RTRANDOM_H
