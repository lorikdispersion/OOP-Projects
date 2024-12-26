#pragma once
#include <limits>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;
constexpr float epsilon = 1e-4f;

inline float degreesToRadians(float degrees) {
    return degrees * pi / 180.0f;
}

inline float randomFloat() {
    return static_cast<float>(rand()) / (RAND_MAX + 1.0f);
}

inline float randomFloat(float min, float max) {
    return min + (max - min) * randomFloat();
}