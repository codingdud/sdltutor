#include <SDL2/SDL.h>
int main(int argc, char** argv){
    //initial steps
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;
    SDL_Init(SDL_INIT_VIDEO);

    //window creation
    SDL_CreateWindowAndRenderer(640,480,0,&window,&renderer);
    //SDL_RenderSetScale(renderer, 4, 4);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Draw point at cetenr of screen
    SDL_RenderDrawPoint(renderer, 320, 240);
    //show to window present
    SDL_RenderPresent(renderer);
    //Update screen
    //delay to stop emidately closing of window
    SDL_Delay(10000);
    //clean up
    return 0;
}