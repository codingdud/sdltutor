#include <SDL2/SDL.h>
#include <iostream>
#include<numeric>
#include<complex>
#include <cmath>

using namespace std;

#define CONSTANT 640
#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 640

double lerp(double start, double end, double factor) {
    return start + factor * (end - start);
}


int is_in_set(complex<double> c){
    complex<double> z(0,0);
    for(int i=0;i<250;i++){
        z=pow(z,2)+c;
        if(norm(z)>10) return i;
    }
    return 0;
}

int main(int argc, char** argv){
    //initial steps
    SDL_Event event;
    bool running=true;
   
    SDL_Init(SDL_INIT_EVENTS);
    SDL_Window* window=SDL_CreateWindow("Snakei",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, 
    SCREEN_HEIGHT, 0);//SDL_WINDOW_SHOWN
    SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,0);
    SDL_RenderSetScale(renderer, 1,1);

    for (double x = 0.0; x < 1.0; x+=0.001){
        for (double y = 0.0; y < 1.0; y+=0.001){
            double point_x=lerp(-2.0, 2.0,x);
            double point_y=lerp(-2.0, 2.0,y);
            int iter=is_in_set(complex<double>(point_x, point_y));
            if(iter==0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawPointF(renderer,x*CONSTANT,y*CONSTANT); 
            }else{
                SDL_SetRenderDrawColor(renderer, 
                13*iter%255,
                13*iter%255, 
                13*iter%255, 
                 255);
                SDL_RenderDrawPointF(renderer, x*CONSTANT,y*CONSTANT);
            }
            }
    } 
    

    while(running){  
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){ running=false; }
            if(event.type==SDL_KEYDOWN){
                if(event.key.keysym.sym==SDLK_ESCAPE){ running=false; }
            }
        }  
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    return 0;
}