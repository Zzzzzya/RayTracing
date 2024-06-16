#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double d2r(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline int random_int(int a, int b) {
    return std::floor(random_double(a, b + 1));
}

// Common Headers

#include "Color.hpp"
#include "Interval.hpp"
#include "Ray.hpp"
#include "Vector.hpp"
