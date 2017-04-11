#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H
#include "Vector.h"
#include "Vector2.h"

struct Collision2D_Result
{
    bool Collision;
    int Line_Index;
    Vector2 L1;
    Vector2 L2;
    Vector2 Out_Normal;
};

class Bounding_Box
{
    public:
        Bounding_Box();
        Bounding_Box(Vector Min_V, Vector Max_V);
        bool Check_Collision(Bounding_Box B2);
        Collision2D_Result Circle_Collision(Vector2 Circle_Center_Old, Vector2 Circle_Center_New, float Circle_Radius);
        virtual ~Bounding_Box();

        Vector Min;
        Vector Max;

        //Tranformation
        Vector Position;
        Vector Rotation;
        Vector Scale;

        bool OBB = false;
    protected:

    private:
};

#endif // BOUNDING_BOX_H
