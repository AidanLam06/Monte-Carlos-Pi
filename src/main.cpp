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
