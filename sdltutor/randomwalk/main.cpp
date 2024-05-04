#include <SDL2/SDL.h>
#include <iostream>
#include<random>

using namespace std;
#define SCALE 10
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 50
int main(int argc, char** argv){
    SDL_Event event;
    int running=true;
    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Random walk", 
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 
    SCREEN_WIDTH*SCALE, SCREEN_HEIGHT*SCALE, 0);//SDL_WINDOW_SHOWN
    auto renderer = SDL_CreateRenderer(window,-1,0);//SDL_RENDERER_ACCELERATED
    SDL_RenderSetScale(renderer, SCALE,SCALE);

    int x = SCREEN_WIDTH/2,y=SCREEN_HEIGHT/2;
    random_device rdev;
    uniform_int_distribution<uint8_t> nd(0,4);

    while (running){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){ running=false; }
            if(event.type==SDL_KEYDOWN){
                if(event.key.keysym.sym==SDLK_ESCAPE){ running=false; }
            }
        }  
        uint8_t dir =nd(rdev);
        switch (dir){
        case 0: x-=1; y-=1; break;
        case 1: x+=1; y-=1; break;
        case 2: x+=1; y+=1; break;
        case 3: x-=1; y+=1; break;
        default:break;
        }
        SDL_SetRenderDrawColor(renderer, 60*dir%255, 60*dir%255,60*dir%255,255);
        SDL_RenderDrawPoint(renderer, x, y);
        SDL_RenderPresent(renderer);
        if(x<0||y<0||x>SCREEN_WIDTH||y>SCREEN_HEIGHT)
        x=SCREEN_WIDTH/2,y=SCREEN_HEIGHT/2;
        SDL_Delay(100);
    }
    
    return 0;
}