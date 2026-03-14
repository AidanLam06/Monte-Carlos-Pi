#include "Dot.hpp"

Dot::Dot(double x_val, double y_val) : x(x_val), y(y_val) {
    double dx = x_val - XC;
    double dy = y_val - YC;
    is_inside = (dx * dx + dy * dy) < (RADIUS * RADIUS);
}