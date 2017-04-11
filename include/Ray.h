#ifndef RAY_H
#define RAY_H
#include "Vector.h"

class Ray
{
    public:
        Ray();
        virtual ~Ray();

        Vector Ray_Start;
        Vector Ray_End;

    protected:

    private:
};

#endif // RAY_H
