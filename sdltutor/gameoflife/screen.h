#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <time.h>  
#include <vector>
#include <tuple>
#include <algorithm>

#pragma once 
using namespace std;

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 480

class Screen{
    SDL_bool done;
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    vector<SDL_FPoint> points;
    vector<SDL_Color> colors;
    public:
    Screen(){
        SDL_Init(SDL_INIT_VIDEO);
        /* window = SDL_CreateWindow("SDL Screen",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);//SDL_WINDOW_SHOWN
        renderer = SDL_CreateRenderer(window,-1,0); */
        SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
    }
    void pixel(int x, int y,uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255){
        SDL_FPoint p;
        p.x = x;
        p.y = y;
        points.emplace_back(p);
        colors.emplace_back(SDL_Color{r,g,b,a});
    }

    void update(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);//draw color black
        SDL_RenderClear(renderer);//clear screan
        
        for(long unsigned int i = 0; i < points.size(); i++)
        {
            SDL_SetRenderDrawColor(renderer,colors[i].r, colors[i].r, colors[i].r, colors[i].r);
            SDL_RenderDrawPointF(renderer, points[i].x, points[i].y);
        }
        SDL_RenderPresent(renderer);
    }
    void input(){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT) exit(0);
        }
    }
    void clear(){
        points.clear();
        colors.clear();
    }
};
