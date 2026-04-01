// Current gaps in knowledge ordered based on priority
// 1) how does SDL2 work
// 2) how do you make temporary objects in C++ 

// plan of action
// 1) create a pi estimation simulation without any fancy stuff yet. 
// 2) add some small improvements like a rolling total to the pi estimation
// 3) make a demo animation in SDL2
// 4) Combine pi estimation logic and SDL2 animation together and add final polishing

#include <iostream>
#include <format>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2/SDL.h>

#include "Game.hpp"

void initialize_SDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error(std::format("SDL_Init Error: {}", SDL_GetError()));
    }
    // IMG_Init returns a bitmask of the flags successfully initialized
    int flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags)) {
        throw std::runtime_error(std::format("IMG_Init Error: {}", IMG_GetError()));
    }

    if (TTF_Init() == -1) {
        throw std::runtime_error(std::format("TTF_Init Error: {}", TTF_GetError()));
    }
}

void close() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main() {

    int exit_val = EXIT_SUCCESS;

    try {
        initialize_SDL();
        Game game;
        game.init();
        game.run();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit_val = EXIT_FAILURE;
    }

    close();
    return exit_val;
}