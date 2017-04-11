#include "Rectangle.h"

Rectangle2D::Rectangle2D()
{
    X = 0;
    Y = 0;
    Width = 0;
    Height = 0;
}

Rectangle2D::Rectangle2D(float x_val, float y_val, float width_val, float height_val)
{
    X = x_val;
    Y = y_val;
    Width = width_val;
    Height = height_val;
}

Rectangle2D::~Rectangle2D()
{
    //dtor
}
