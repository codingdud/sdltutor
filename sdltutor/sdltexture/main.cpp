#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 649 
#define SCREEN_HEIGHT 480
int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("SDL Texture Example", 
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 
    SCREEN_WIDTH, SCREEN_HEIGHT, 0);//SDL_WINDOW_SHOWN
    auto renderer = SDL_CreateRenderer(window,-1,0);//SDL_RENDERER_ACCELERATED
    
    //creatte textures
    auto red_texture = SDL_CreateTexture(renderer, 
    SDL_PIXELFORMAT_RGBA8888, 
    SDL_TEXTUREACCESS_TARGET, 
    SCREEN_WIDTH, 
    SCREEN_HEIGHT);

    //creatre blue_texture
    auto blue_texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET,
    SCREEN_WIDTH,
    SCREEN_HEIGHT);
    
    //Draw to texture
    SDL_SetRenderTarget(renderer, red_texture);
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderTarget(renderer, blue_texture);
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, nullptr);
    //present to screen
    SDL_RenderCopy(renderer, red_texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_RenderCopy(renderer, blue_texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    return 0;
}