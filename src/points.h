#ifndef POINTS_H
#define POINTS_H

#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"

class Points {
 public:
    Points(){}
    Points(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
        //m_point = point;
        //m_rectType = block;
        m_color[0] = r;
        m_color[1] = g;
        m_color[2] = b;
        m_color[3] = a;
    }
    // setter & getter
 //private:
    virtual void Print() {
        std::cout << "this is point class\n";
    }
    SDL_Point m_point;
    SDL_Rect m_rectType;
    Uint8 m_color[4];

};

#endif