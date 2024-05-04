#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 649
#define SCREEN_HEIGHT 480
int main(int argc, char **argv)
{
    int fontsize = 24;
    int t_width = 0;  // width of the loaded font-texture
    int t_height = 0; // height of the loaded font-texture
    SDL_Color text_color = {0, 0, 0};
    string fontpath = "my font path";
    string text = "text I want to display";

    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("SDL Texture Example",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, 0); // SDL_WINDOW_SHOWN
    auto renderer = SDL_CreateRenderer(window, -1, 0);              // SDL_RENDERER_ACCELERATED

    // creatte textures
    TTF_Font *font = TTF_OpenFont(fontpath.c_str(), fontsize);
    SDL_Texture *ftexture = NULL; // our font-texture

    while (true)
    {
        SDL_SetRenderTarget(renderer, nullptr);
        // present to screen
        SDL_RenderCopy(renderer, red_texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        SDL_RenderCopy(renderer, blue_texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    return 0;
}