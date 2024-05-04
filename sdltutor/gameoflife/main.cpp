#include "screen.h"
#include<array>

using namespace std;
bool is_alive(array<array<int,SCREEN_HEIGHT>,SCREEN_WIDTH>& display, int x, int y){
    int neighbors=0;
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
            if(i!=0 || j!=0)
                if(x+i>=0 && x+i<SCREEN_WIDTH && y+j>=0 && y+j<SCREEN_HEIGHT)
                neighbors+=display[x+i][y+j];
    if(display[x][y]==1&&neighbors==2) return true;
    return neighbors==3;
}
int main(int argc, char* argv[]) {
    array<array<int,SCREEN_HEIGHT>,SCREEN_WIDTH> display{};
    array<array<int,SCREEN_HEIGHT>,SCREEN_WIDTH> temp{};

    for(auto& row:display)
        generate(row.begin(),row.end(),[](){return rand()%10==0?1:0;});

    Screen screen;
    while (true){
        for (int i = 0; i < SCREEN_WIDTH; i++)
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        temp[i][j]=is_alive(display,i,j)?1:0;
        //drway
        for (int i = 0; i < SCREEN_WIDTH; i++)
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        if(temp[i][j]==1)   screen.pixel(i,j);
        copy(temp.begin(), temp.end(), display.begin());
        //display
        screen.update();
        SDL_Delay(100);
        screen.clear();
        screen.input();
    }
    
    return 0;
}