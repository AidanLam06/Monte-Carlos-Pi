#include "Dot.hpp"
#include "Game.hpp"

Dot::Dot(double x_val, double y_val) : x(x_val), y(y_val) {
    double dx = x_val - image_config::xc;
    double dy = y_val - image_config::yc;
    is_inside = (dx * dx + dy * dy) < (image_config::radius * image_config::radius);
}