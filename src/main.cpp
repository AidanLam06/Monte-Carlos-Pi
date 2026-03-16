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
#include <chrono>

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

    double x, y;
    int num_dots_inside;

    const auto start{std::chrono::steady_clock::now()};

    for (int i = 0; i < num_dots; i++) {
        x = dist(gen), y = dist(gen);
        Dot dot(x, y);
        if (dot.is_inside) {
            ++num_dots_inside;
        }
        if ((i+1) % 100000 == 0) {
            std::cout << 4 * static_cast<double>(num_dots_inside) / i << "\n";
        }
    }

    const auto finish{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{finish - start};

    // final estimate. Since π/4 = num_dots_inside/num_dots, and we know r, rearrange as π = 4(ndi/nd)
    std::cout << "\nfinal estimate is: " 
              << 4 * static_cast<double>(num_dots_inside) / num_dots 
              << "\nTook " << elapsed_seconds.count() << " seconds";

}