// Current gaps in knowledge ordered based on priority
// 1) how does SDL2 work
// 2) how do you make temporary objects in C++ 

// plan of action
// 1) create a pi estimation simulation without any fancy stuff yet. 
// 2) add some small improvements like a rolling total to the pi estimation
// 3) make a demo animation in SDL2
// 4) Combine pi estimation logic and SDL2 animation together and add final polishing

#include <iostream>
#include <random>
#include <vector>

#include "Dot.hpp"

int main() {
    int num_dots;
    std::string buf;
    std::cout << "Enter number of dots (more dots, less error): ";
    std:getline(std::cin, buf);
    num_dots = stoi(buf);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-RADIUS, RADIUS);

    std::vector<Dot> dots;
    dots.reserve(num_dots);
    double x, y;

    // 1) populate vector
    for (int i = 0; i < num_dots; i++) {
        x = dist(gen), y = dist(gen);
        dots.emplace_back(Dot(x, y));
    }

    int num_dots_inside;

    // 2) display pi estimation
    for (int i = 0; i < num_dots; i++) {
        if (dots.at(i).is_inside) {
            ++num_dots_inside;
        }
        std::cout << "estimate at " << i << " dots: " << num_dots_inside << "/" << i << " " << dots.at(i).x << ", " << dots.at(i).y << "\n";
    }

    // final estimate. Since π/4 = num_dots_inside/num_dots, and we know r, rearrange as π = 4(ndi/nd)
    std::cout << "final estimate is: " << 4 * static_cast<double>(num_dots_inside) / num_dots;

}