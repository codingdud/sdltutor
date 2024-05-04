#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720
int main(int argc, char** argv){
    //initial steps
    SDL_Event event;
    bool running=true;
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Rect rect={10,10,20,20}; //rectange with center at (320,240)
    SDL_Rect rect2={SCREEN_WIDTH-20,SCREEN_HEIGHT-20,20,20};
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH,SCREEN_HEIGHT,0,&window,&renderer);
    SDL_RenderSetScale(renderer, 1,1);

    int jump=0;
    while(running){
        if(jump>0){rect.y+=1; jump--;}     
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                running=false;
            }
            if(event.type==SDL_KEYDOWN){
                //cout<<"key was pressed!"<<endl;
                switch(event.key.keysym.sym){
                    case SDLK_w: rect.y-=10; break;
                    case SDLK_s: rect.y+=10; break;
                    case SDLK_a: rect.x-=10; break;
                    case SDLK_d: rect.x+=10; break;
                    case SDLK_UP: rect.y-=10; break;
                    case SDLK_DOWN: rect.y+=10; break;
                    case SDLK_RIGHT: rect.x+=10; break;
                    case SDLK_LEFT: rect.x-=10; break;
                    case SDLK_ESCAPE: running=false; break;
                    case SDLK_SPACE:if(jump==0){jump=50;rect.y-=50;} break;
                    default: break;
                }       
            }
            else if(event.type==SDL_KEYUP){
                switch(event.key.keysym.sym){
                    case SDLK_w: rect.y-=20; break;
                    case SDLK_s: rect.y+=20; break;
                    case SDLK_a: rect.x-=20; break;
                    case SDLK_d: rect.x+=20; break;
                    case SDLK_UP: rect.y-=20; break;
                    case SDLK_DOWN: rect.y+=20; break;
                    case SDLK_RIGHT: rect.x+=20; break;
                    case SDLK_LEFT: rect.x-=20; break;
                    default: break;
                }
            }
            else if(event.type==SDL_MOUSEBUTTONDOWN){
                switch(event.button.button){
                    case SDL_BUTTON_LEFT: rect.x=event.button.x; rect.y=event.button.y; break;
                    case SDL_BUTTON_RIGHT: running=false; break;
                    default: break;
                }
            }
            else if(event.type==SDL_MOUSEMOTION){
                SDL_GetMouseState(&rect2.x, &rect2.y);
                // rect.x=event.motion.x;
                // rect.y=event.motion.y;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    return 0;
}