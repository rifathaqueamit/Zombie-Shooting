#include "Vector.h"

Vector::Vector()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Vector::Vector(float x_val, float y_val, float z_val)
{
    X = x_val;
    Y = y_val;
    Z = z_val;
}

Vector::~Vector()
{
    //dtor
}
