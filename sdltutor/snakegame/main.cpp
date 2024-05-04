#include <SDL2/SDL.h>
#include <iostream>
#include <deque>
#include<algorithm>

using namespace std;

#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 420

enum Direction{
    DOWN,LEFT,RIGHT,UP
};

int main(int argc, char** argv){
    //initial steps
    SDL_Event event;
    bool running=true;
    SDL_Rect food={rand()%(SCREEN_WIDTH/10)*10,rand()%(SCREEN_HEIGHT/10)*10,10,10}; //rectange with center at (320,240)
    SDL_Rect head={SCREEN_WIDTH/2,SCREEN_HEIGHT/2,10,10};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window=SDL_CreateWindow("Snakei",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, 
    SCREEN_HEIGHT, 0);//SDL_WINDOW_SHOWN
    SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,0);
    SDL_RenderSetScale(renderer, 1,1);

    deque<SDL_Rect> body;
    int size=1;
    deque<SDL_Rect> apples;
    for(int i=0;i<100;i++) apples.push_back({rand()%100*10,rand()%100*10,10,10});

    int dir=-1;
    while(running){  
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                running=false;
            }
            if(event.type==SDL_KEYDOWN){
                //cout<<"key was pressed!"<<endl;
                switch(event.key.keysym.sym){
                    case SDLK_w: if(dir!=DOWN)dir=UP; break;
                    case SDLK_s: if(dir!=UP)dir=DOWN; break;
                    case SDLK_a: if(dir!=RIGHT)dir=LEFT; break;
                    case SDLK_d: if(dir!=LEFT)dir=RIGHT; break;
                    case SDLK_UP: if(dir!=DOWN)dir=UP; break;
                    case SDLK_DOWN: if(dir!=UP)dir=DOWN; break;
                    case SDLK_RIGHT: if(dir!=LEFT)dir=RIGHT; break;
                    case SDLK_LEFT:  if(dir!=RIGHT)dir=LEFT; break;
                    case SDLK_ESCAPE: running=false; break;
                    case SDLK_SPACE: break;
                    default: break;
                }   
                
            }  
        }
        //moves 
        switch(dir){
        case UP: head.y-=10;  break;
        case DOWN: head.y+=10; break;
        case LEFT: head.x-=10;  break;
        case RIGHT: head.x+=10;  break;
        default: break;
        }  
        //collesion detection
        for_each(apples.begin(), apples.end(), [&](SDL_Rect& apple){
            if(head.x==apple.x&&head.y==apple.y){
                size+=10;
                apple.x=-10;
                apple.y=-10;
            }
        });
        //collsion self
        for_each(body.begin(), body.end(), [&](SDL_Rect& rect){
            if(head.x==rect.x&&head.y==rect.y){
                size=1+size/2;
            }
        });

        body.push_front(head);
        while(body.size()>size){
            body.pop_back();
        }
        /* if(food.x-10<=head.x&&food.x+10>=head.x&&food.y-10<=head.y&&food.y+10>=head.y){
            size+=20;
            food.x=rand()%30*10;
            food.y=rand()%30*10;
        } */
        if(food.x==head.x&&food.y==head.y){
            size+=20;
            food.x=rand()%(SCREEN_WIDTH/10)*10;
            food.y=rand()%(SCREEN_HEIGHT/10)*10;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        //draw body
        for_each(body.begin(), body.end(), [&](SDL_Rect& segment){
            if(segment.x==body.front().x&&segment.y==body.front().y) SDL_SetRenderDrawColor(renderer, 165, 122, 233, 255);
            else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &segment);
        });
        //draw apples
        for_each(apples.begin(), apples.end(), [&](SDL_Rect& apple){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &apple);
        });
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        //SDL_RenderFillRect(renderer, &head);
        SDL_RenderFillRect(renderer, &food);
        SDL_RenderPresent(renderer);
        SDL_Delay(70);

    }
    return 0;
}