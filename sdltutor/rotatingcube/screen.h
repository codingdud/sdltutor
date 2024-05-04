#include <SDL2/SDL.h>
#include<vector>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480

class Screen{
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;
    public:
    Screen(){
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("SDL Screen",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);//SDL_WINDOW_SHOWN
        renderer = SDL_CreateRenderer(window,-1,0);
        SDL_RenderSetScale(renderer, 1, 1);
    }
    void pixel(float x, float y){
        SDL_FPoint p;
        p.x = x;
        p.y = y;
        points.emplace_back(SDL_FPoint{x,y});
    }
    void show(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//draw color black
        SDL_RenderClear(renderer);//clear screan
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//color to white before drawing points
        for(auto p:points) SDL_RenderDrawPointF(renderer, p.x, p.y);
        SDL_RenderPresent(renderer);
    }
    void input(){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT) exit(0);
        }
    }
    void clear(){
        points.clear();
    }
};
