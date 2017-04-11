#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        Vector Position;
        Vector Look_At;
        Vector Up;

        int Projection_Type; //0 = Perspective

        float Near;
        float Far;
        float Aspect_Ratio;
        float Field_Of_View;

    protected:

    private:
};

#endif // CAMERA_H
