#include <SDL_pixels.h>
#include <SDL_render.h>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Dot.hpp"
#include "Game.hpp"


Game::Game()
      : title("Open Window") {}

void Game::init() {
    num_dots = 0;
    num_dots_inside = 0;
    // get number of dots from user
    std::string buf;
    std::cout << "Enter number of dots (more dots, less error): ";
    std::getline(std::cin, buf);
    num_dots = stoi(buf);

    // Create font item and font color
    this->font.reset(TTF_OpenFont("font/AllerDisplay.ttf", 16));
    if (!this->font.get()) {
        std::cerr << "TTF_OpenFont error: " << TTF_GetError() << std::endl;
    }

    // initialize window pointer
    this->window.reset(SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, this->width,
                                        this->height, 0));
    if (!this->window) {
        std::ostringstream oss;
        oss << "Error creating window: " << SDL_GetError();
        throw std::runtime_error(oss.str());
    }

    // initialize renderer pointer
    this->renderer.reset(SDL_CreateRenderer(this->window.get(), -1,
                                            SDL_RENDERER_ACCELERATED));
    if (!this->renderer) {
        std::ostringstream oss;
        oss << "Error creating renderer: " << SDL_GetError();
        throw std::runtime_error(oss.str());
    }

    // Create temporary surface pointer
    SDL_Surface* temp_image_surface = IMG_Load("images/circle_and_square.png");
    if (!temp_image_surface) {
        throw std::runtime_error(IMG_GetError());
    }

    // initialize circle_and_square_texture pointer
    this->circle_and_square_texture.reset(SDL_CreateTextureFromSurface(
        this->renderer.get(), temp_image_surface));
    
    if (!this->circle_and_square_texture) {
        std::ostringstream oss;
        oss << "Error creating circle_and_square_texture: " << SDL_GetError();
        throw std::runtime_error(oss.str()); 
    }

    // initialize point_canvas_texture pointer
    this->point_canvas_texture.reset(SDL_CreateTexture(
        this->renderer.get(),
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        image_config::width,
        image_config::height
    ));

    if (!this->point_canvas_texture) {
        std::ostringstream oss;
        oss << "Error creating point_canvas_texture: " << SDL_GetError();
        throw std::runtime_error(oss.str());
    }

    SDL_SetTextureBlendMode(
        this->point_canvas_texture.get(),
        SDL_BLENDMODE_BLEND
    );

    // initialize temporary text surface
    SDL_Surface* temp_text_surface = TTF_RenderText_Solid(this->font.get(), "...", font_color);
    if (!temp_text_surface) {
        throw std::runtime_error(TTF_GetError());
    }

    this->estimate_text.texture.reset(SDL_CreateTextureFromSurface(
        this->renderer.get(),
        temp_text_surface
    ));

    if (!this->estimate_text.texture) {
        std::ostringstream oss;
        oss << "Error creating circle_and_square_texture: " << SDL_GetError();
        throw std::runtime_error(oss.str());
    }
    
    SDL_FreeSurface(temp_image_surface);
    SDL_FreeSurface(temp_text_surface);

    // check if png image exists
    if (!this->circle_and_square_texture) {
        throw std::runtime_error(SDL_GetError());
    }
}

void Game::updateText(TextElement& element, const std::string& message) {
    // 1. Create surface
    SDL_Surface* tempSurf = TTF_RenderText_Solid(this->font.get(), message.c_str(), font_color);
    if (!tempSurf) return;

    // 2. Replace the old texture (using .reset() if you use unique_ptr)
    element.texture.reset(SDL_CreateTextureFromSurface(this->renderer.get(), tempSurf));
    
    // 3. Query the texture for its actual size
    int w, h;
    SDL_QueryTexture(element.texture.get(), NULL, NULL, &w, &h);
    
    // 4. Update the Rect dimensions to prevent stretching
    element.rect = {10, 10, w, h};

    SDL_FreeSurface(tempSurf);
}

void Game::render() {
    SDL_SetRenderDrawColor(
        this->renderer.get(),
        0,
        0,
        0,
        255
    );
    SDL_RenderClear(this->renderer.get());

    SDL_Rect destRect = {
        image_config::x,
        image_config::y,
        image_config::width,
        image_config::height
    };

    SDL_RenderCopy(
        this->renderer.get(),
        this->circle_and_square_texture.get(),
        NULL,
        &destRect
    );

    SDL_RenderCopy(
        this->renderer.get(),
        this->point_canvas_texture.get(),
        NULL,
        &destRect
    );

    SDL_RenderCopy(this->renderer.get(), this->estimate_text.texture.get(), NULL, &this->estimate_text.rect);

    SDL_RenderPresent(this->renderer.get());
}

// debug
int g = 0;

void Game::addPoints(int dots_to_update) {
    SDL_SetRenderTarget(
        this->renderer.get(),
        this->point_canvas_texture.get()
    );

    for (int i = 0; i < dots_to_update; i++) {
        double x = getRandomX();
        double y = getRandomY();
        Dot dot(x, y);

        if (dot.is_inside) {
            SDL_SetRenderDrawColor(this->renderer.get(),83,140,97,255);
            ++num_dots_inside;
        } else {
            SDL_SetRenderDrawColor(this->renderer.get(),163,46,46,255);
        }

        SDL_RenderDrawPoint(this->renderer.get(), dot.x-100, dot.y);

        ++dots_generated;
        
        if (this->dots_generated == this->num_dots) {
            break;
        }
    }

    SDL_SetRenderTarget(this->renderer.get(), NULL);
}

// notes: keep scope as local as possible. Video shows event variable in Game class, but its better to keep it in run() since this is
// the only function that needs it
void Game::run() {
    bool is_running = true;
    bool simulation_complete = false;
    std::chrono::steady_clock::time_point finish;
    SDL_Event event;

    const auto start{std::chrono::steady_clock::now()};

    while(is_running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                if (simulation_complete) {
                    const std::chrono::duration<double> elapsed = finish - start;
                    std::cout << "Simulation Complete. " << dots_generated << "/" << num_dots << std::endl;
                    std::cout << "Time: " << elapsed.count() << " seconds" << std::endl;
                } else {
                    std::cout << "Aborted. Progress: " << dots_generated << "/" << num_dots << " dots" << std::endl;
                }
                
                // Always show the current estimate, even if incomplete
                double final_est = (dots_generated == 0) ? 0 : 4.0 * num_dots_inside / dots_generated;
                std::cout << "Estimate: " << final_est << std::endl;

                is_running = false;
            }
        }
        if (!simulation_complete) {
            addPoints(100);

            double estimate = (num_dots == 0) ? 0 : 4.0 * static_cast<double>(num_dots_inside) / dots_generated;
            updateText(this->estimate_text, std::to_string(estimate));

            if (dots_generated >= num_dots) {
                finish = std::chrono::steady_clock::now();
                simulation_complete = true;
            }
        }
        render();
    }
}
