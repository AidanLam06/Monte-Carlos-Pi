#ifndef GAME_HPP
#define GAME_HPP

#include <SDL_render.h>
#include <string>
#include <memory>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace image_config {
    inline constexpr int x = 100;
    inline constexpr int y = 0;
    inline constexpr int width = 600;
    inline constexpr int height = width; // needs to be a square, so always width = height
    inline constexpr int radius = width/2;
    inline constexpr int xc = x + radius;
    inline constexpr int yc = y + radius;
}

struct SDL_WindowDeleter {void operator()(SDL_Window * w) const {SDL_DestroyWindow(w);}};
struct SDL_RendererDeleter {void operator()(SDL_Renderer * r) const {SDL_DestroyRenderer(r);}};
struct SDL_TextureDeleter {void operator()(SDL_Texture * t) const {SDL_DestroyTexture(t);}};
struct TTF_FontDeleter {void operator()(TTF_Font * f) const {TTF_CloseFont(f);}};

struct TextElement {
    std::unique_ptr<SDL_Texture, SDL_TextureDeleter> texture;
    SDL_Rect rect{0, 0, 0, 0};
};

class Game {
    public:
        Game();

        void init();
        void render();
        void addPoints(int dots_to_update);
        void updateText(TextElement& element, const std::string& message);
        void run();

        double getRandomX() {
            return dist_x(gen);
        }

        double getRandomY() {
            return dist_y(gen);
        }

        static constexpr int width{800};
        static constexpr int height{600};

    private:
        const std::string title;
        int num_dots;
        int num_dots_inside;
        int dots_generated;

        std::mt19937 gen;
        std::uniform_real_distribution<double> dist_x{
            static_cast<double>(image_config::x),
            static_cast<double>(image_config::width + image_config::x)
        };

        std::uniform_real_distribution<double> dist_y{
            static_cast<double>(image_config::y),
            static_cast<double>(image_config::y + image_config::height)
        };
    
        SDL_Color font_color {240, 240, 240, 255};

        std::unique_ptr<SDL_Window, SDL_WindowDeleter> window;
        std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> renderer;
        std::unique_ptr<SDL_Texture, SDL_TextureDeleter> circle_and_square_texture;
        std::unique_ptr<SDL_Texture, SDL_TextureDeleter> point_canvas_texture;
        std::unique_ptr<TTF_Font, TTF_FontDeleter> font;
        TextElement estimate_text;
};

#endif