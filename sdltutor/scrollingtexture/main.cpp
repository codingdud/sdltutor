#include <SDL2/SDL.h>
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define TEXTURE_W 720
#define TEXTURE_H 720
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 480

int main(int argc, char** argv){
    //init
    SDL_Event event;
    SDL_Rect source{0,0,SCREEN_WIDTH/5,SCREEN_HEIGHT/5};
    SDL_Rect dest{2,2,SCREEN_WIDTH-4,SCREEN_HEIGHT-4};
    SDL_Init(SDL_INIT_EVERYTHING);

    auto window = SDL_CreateWindow("SDL Scrolling Texture", 
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 
    SCREEN_WIDTH, SCREEN_HEIGHT, 0);//SDL_WINDOW_SHOWN
    auto renderer = SDL_CreateRenderer(window,-1,0);//SDL_RENDERER_ACCELERATED
    
    //creatte textures
    auto texture = SDL_CreateTexture(renderer, 
    SDL_PIXELFORMAT_RGBA8888, 
    SDL_TEXTUREACCESS_TARGET, 
    TEXTURE_W, 
    TEXTURE_H);

    SDL_Point point;
    vector<SDL_Point> pv;
    for(int i=0; i<SCREEN_WIDTH; i++){ 
        point.x=rand()%TEXTURE_W;
        point.y=rand()%TEXTURE_H;
        pv.emplace_back(point);
    }
    auto running=true;
    int jump=0;
    while(running){
        if(jump>0){source.y+=1; jump--;}     
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){   running=false;}
            if(event.type==SDL_KEYDOWN){
                //cout<<"key was pressed!"<<endl;
                switch(event.key.keysym.sym){
                    case SDLK_w: source.y-=3; break;
                    case SDLK_s: source.y+=3; break;
                    case SDLK_a: source.x-=3; break;
                    case SDLK_d: source.x+=3; break;
                    case SDLK_UP: source.y-=3; break;
                    case SDLK_DOWN: source.y+=3; break;
                    case SDLK_RIGHT: source.x+=3; break;
                    case SDLK_LEFT: source.x-=3; break;
                    case SDLK_ESCAPE: running=false; break;
                    case SDLK_SPACE:if(jump==0){jump=10;source.y-=10;} break;
                    case SDLK_1: source.w*=2; source.h*=2; break;
                    case SDLK_2: source.w/=2; source.h/=2; break;
                    default: break;
                }       
            }
        }
        //clear texture
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);
        // move position of dots arround
        for(auto& p: pv){    p.x+=rand()%3-1;  p.y+=rand()%3-1;}
        //draw dots and screen
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderDrawPoints(renderer, pv.data(), pv.size());
        
        SDL_SetRenderTarget(renderer, nullptr);
        //present
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,texture, &source, &dest);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    return 0;
}