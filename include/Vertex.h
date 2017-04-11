#ifndef VERTEX_H
#define VERTEX_H

#include "Vector.h"
#include "Color.h"

class Vertex
{
    public:
        Vertex();
        Vertex(Vector pos, Color col, float T_U, float T_V);
        virtual ~Vertex();

        Vector V_Position;
        Color V_Color;
        float U;
        float V;

    protected:

    private:
};

#endif // VERTEX_H
