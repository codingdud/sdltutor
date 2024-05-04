#include "screen.h"
#include <cmath>

struct vec3{
    float x, y, z;
    vec3() : x(0), y(0), z(0) {};
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};
};
struct connection{
    int a,b;
    connection() : a(0), b(0) {};
    connection(int a, int b) : a(a), b(b) {};
};
void scale(std::vector<vec3> &poins,int scale){
    for(int i = 0; i < poins.size(); i++){
        poins[i].x+=scale;
        poins[i].y+=scale;
        poins[i].z+=scale;
    }
}
void rotate(vec3& v, vec3 angle){
    float rad=0;
    rad=angle.x;
    v.y=v.y*std::cos(rad)-v.z*std::sin(rad);
    v.z=v.y*std::sin(rad)+v.z*std::cos(rad);
    rad=angle.y;
    v.x=v.x*std::cos(rad)-v.z*std::sin(rad);
    v.z=v.x*std::sin(rad)+v.z*std::cos(rad);
    rad=angle.z;
    v.x=v.x*std::cos(rad)-v.y*std::sin(rad);
    v.y=v.x*std::sin(rad)+v.y*std::cos(rad);
}
void line(Screen& screen,float x1,float y1,float x2,float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = std::max(abs(dx), abs(dy));
    float xinc = dx/steps;
    float yinc = dy/steps;
    float x = x1;
    float y = y1;
    for(int i = 0; i < steps; i++){
        screen.pixel(x, y);
        x += xinc;
        y += yinc;
    }
}
void line2(Screen& screen,float x1,float y1,float x2,float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    float lenght = std::sqrt(dx*dx+dy*dy);
    float angle = std::atan2(dy, dx);
    for(int i = 0; i < lenght; i++){
        screen.pixel(x1+std::cos(angle)*i, y1+std::sin(angle)*i);
    }
}

int main(int argc, char* argv[]) {
    Screen screen;
    std::vector<vec3> points={
        {150,150,150},
        {300,150,150},
        {300,300,150},
        {150,300,150},

        {150,150,300},
        {300,150,300},
        {300,300,300},
        {150,300,300},
    };
    //scale(points, 50);
    std::vector<connection> connections={
        {0,4},
        {1,5},
        {2,6},
        {3,7},

        {0,1},
        {1,2},
        {2,3},
        {3,0},

        {4,5},
        {5,6},
        {6,7},
        {7,4},
    };
    //calulating centoroid
    vec3 c;
    for(auto&p:points){
        c.x+=p.x;
        c.y+=p.y;
        c.z+=p.z;
    }
    c.x/=points.size();
    c.y/=points.size();
    c.z/=points.size();
    while(true){
        for(auto& p : points){
            p.x-=c.x;
            p.y-=c.y;
            p.z-=c.z;
            rotate(p, {0.002,0.001,0.004});
            p.x+=c.x;
            p.y+=c.y;
            p.z+=c.z;
            screen.pixel(p.x, p.y);
        }
        for(auto& c : connections){
            line(screen, points[c.a].x, points[c.a].y, points[c.b].x, points[c.b].y);
        }
        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);
    }
    return 0;
}