#include <SDL2/SDL.h>
#include <bits/stdc++.h>
using namespace std;
#define SCALE 5
#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 100

void draw_state(vector<int> &v, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < v.size() - 1; i++)
    {
        SDL_RenderDrawLine(renderer, i, v[i], i, v[i]);
    }
}
void draw_state2(vector<int> &v, SDL_Renderer *renderer,int red,int blue)
{
    for (int i = 0; i < v.size() - 1; i++){
        if (i == red) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (i == blue) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, i, v[i], i, v[i]);
    }
}

int main(int argc, char **argv)
{
    SDL_Event event;
    random_device rd;
    uniform_int_distribution<int> dist(1, 99);
    vector<int> v;
    for (int i = 1; i < 99; i++)
    {
        v.push_back(dist(rd));
    }

    // sort algorithm
    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("SDL Texture Example",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, 0); // SDL_WINDOW_SHOWN
    auto renderer = SDL_CreateRenderer(window, -1, 0);                              // SDL_RENDERER_ACCELERATED
    SDL_RenderSetScale(renderer, SCALE, SCALE);
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[i] > v[j])
                swap(v[i], v[j]);
            // clear
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state2(v, renderer,i-1,j);

            // present
            // for (int i : v)cout << i << " ";
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
        }
    }
    v.clear();
    for (int i = 1; i < 99; i++)
    {
        v.push_back(dist(rd));
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_state(v, renderer);

    // present
    // for (int i : v)cout << i << " ";
    SDL_RenderPresent(renderer);
    for (int i = v.size() - 1; i >0; i--)
    {
        for (int j = 0; j <  i - 1; j++)
        {
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
            // clear
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state2(v, renderer,i,j);

            // present
            // for (int i : v)cout << i << " ";
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }
    for (int i : v)
        cout << i << " ";

    // creatte textures

    return 0;
}