#ifndef UTILITIES_H
#define UTILITIES_H
#include "Vector2.h"

class Utilities
{
    public:
        Utilities();
        virtual ~Utilities();

        static Vector Get_Normal(Vector V1, Vector V2, Vector V3);
        static void Draw_Text();
        static bool line_circle_intersection(Vector2 a, Vector2 b, Vector2 center, float r);
        static float Vector2_Dot(Vector2 a, Vector2 b);

        protected:

    private:
};

#endif // UTILITIES_H
