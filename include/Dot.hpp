#pragma once

#include <cstdint>
#include <cmath>

#define XC (0)
#define YC (0)
#define RADIUS (2)

class Dot {
    public:
        double x, y;
        bool is_inside;

        Dot(double x_val, double y_val);
};