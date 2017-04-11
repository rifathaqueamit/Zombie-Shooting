#include "Color.h"

Color::Color()
{
    R = 0;
    G = 0;
    B = 0;
    A = 0;
}

Color::~Color()
{
    //dtor
}

Color::Color(float r, float g, float b, float a)
{
    R = r;
    G = g;
    B = b;
    A = a;
}
