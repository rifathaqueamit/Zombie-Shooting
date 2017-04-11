#include "Vertex.h"
#include "Color.h"
#include "Vector.h"

Vertex::Vertex()
{
    V_Position = Vector(0,0,0);
    V_Color = Color(0,0,0,0);
    U = 0;
    V = 0;
}

Vertex::Vertex(Vector pos, Color col, float T_U, float T_V)
{
    V_Position = Vector(pos.X, pos.Y, pos.Z);
    V_Color = Color(col.R, col.G, col.B, col.A);
    U = T_U;
    V = T_V;
}

Vertex::~Vertex()
{
    //dtor
}
