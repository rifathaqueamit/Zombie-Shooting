#include "Camera.h"

Camera::Camera()
{
    Position = Vector(0,0,0);
    Look_At = Vector(0,0,1);
    Up = Vector(0,1,0);
    Near = 0.01;
    Far = 1000;
    Field_Of_View = 60;
    Aspect_Ratio = 1;
    Projection_Type = 0;
}

Camera::~Camera()
{
    //dtor
}
