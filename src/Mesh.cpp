#include "Mesh.h"
#include "Vertex.h"
#include <GL/glut.h>
#include "Utilities.h"

Mesh::Mesh()
{
    Primitive_Type = GL_TRIANGLES;
    Face_Count = 0;
}



void Mesh::Add_Quad(Vertex v1, Vertex v2, Vertex v3, Vertex v4, int Texture_ID)
{
    int i0 = Add_Vertex(v1);
    int i1 = Add_Vertex(v2);
    int i2 = Add_Vertex(v3);
    int i3 = Add_Vertex(v4);

    Add_Index(i0);
    Add_Index(i1);
    Add_Index(i2);

    Add_Index(i2);
    Add_Index(i3);
    Add_Index(i0);

    Vector N;
    N = Utilities::Get_Normal(v1.V_Position, v2.V_Position, v3.V_Position);

    Add_Normal(N);
    Add_Normal(N);
    Add_Normal(N);
    Add_Normal(N);

    Add_Texture(Texture_ID);
    Add_Texture(Texture_ID);
}

void Mesh::Create_Box(float size_x, float size_y, float size_z, Color c,int Texture_ID)
{
    float x1,y1,z1;
    float x2,y2,z2;
    float x3,y3,z3;
    float x4,y4,z4;

    x1 = -size_x/2;
    y1 = -size_y/2;
    z1 = -size_z/2;

    x2 = size_x/2;
    y2 = -size_y/2;
    z2 = -size_z/2;

    x3 = size_x/2;
    y3 = -size_y/2;
    z3 = size_z/2;

    x4 = -size_x/2;
    y4 = -size_y/2;
    z4 = size_z/2;

    float x5,y5,z5;
    float x6,y6,z6;
    float x7,y7,z7;
    float x8,y8,z8;

    x5 = -size_x/2;
    y5 = size_y/2;
    z5 = -size_z/2;

    x6 = size_x/2;
    y6 = size_y/2;
    z6 = -size_z/2;

    x7 = size_x/2;
    y7 = size_y/2;
    z7 = size_z/2;

    x8 = -size_x/2;
    y8 = size_y/2;
    z8 = size_z/2;

    Add_Quad(Vertex(Vector(x1,y1,z1),c,0,0),
             Vertex(Vector(x2,y2,z2),c,1,0),
             Vertex(Vector(x3,y3,z3),c,1,1),
             Vertex(Vector(x4,y4,z4),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x8,y8,z8),c,0,0),
             Vertex(Vector(x7,y7,z7),c,1,0),
             Vertex(Vector(x6,y6,z6),c,1,1),
             Vertex(Vector(x5,y5,z5),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x5,y5,z5),c,0,0),
             Vertex(Vector(x6,y6,z6),c,1,0),
             Vertex(Vector(x2,y2,z2),c,1,1),
             Vertex(Vector(x1,y1,z1),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x7,y7,z7),c,0,0),
             Vertex(Vector(x8,y8,z8),c,1,0),
             Vertex(Vector(x4,y4,z4),c,1,1),
             Vertex(Vector(x3,y3,z3),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x6,y6,z6),c,0,0),
             Vertex(Vector(x7,y7,z7),c,1,0),
             Vertex(Vector(x3,y3,z3),c,1,1),
             Vertex(Vector(x2,y2,z2),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x1,y1,z1),c,0,0),
             Vertex(Vector(x4,y4,z4),c,1,0),
             Vertex(Vector(x8,y8,z8),c,1,1),
             Vertex(Vector(x5,y5,z5),c,0,1),Texture_ID);

}

void Mesh::Create_Cube(float size, Color c,int Texture_ID)
{
    float x1,y1,z1;
    float x2,y2,z2;
    float x3,y3,z3;
    float x4,y4,z4;

    x1 = -size/2;
    y1 = -size/2;
    z1 = -size/2;

    x2 = size/2;
    y2 = -size/2;
    z2 = -size/2;

    x3 = size/2;
    y3 = -size/2;
    z3 = size/2;

    x4 = -size/2;
    y4 = -size/2;
    z4 = size/2;

    float x5,y5,z5;
    float x6,y6,z6;
    float x7,y7,z7;
    float x8,y8,z8;

    x5 = -size/2;
    y5 = size/2;
    z5 = -size/2;

    x6 = size/2;
    y6 = size/2;
    z6 = -size/2;

    x7 = size/2;
    y7 = size/2;
    z7 = size/2;

    x8 = -size/2;
    y8 = size/2;
    z8 = size/2;

    Add_Quad(Vertex(Vector(x1,y1,z1),c,0,0),
             Vertex(Vector(x2,y2,z2),c,1,0),
             Vertex(Vector(x3,y3,z3),c,1,1),
             Vertex(Vector(x4,y4,z4),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x8,y8,z8),c,0,0),
             Vertex(Vector(x7,y7,z7),c,1,0),
             Vertex(Vector(x6,y6,z6),c,1,1),
             Vertex(Vector(x5,y5,z5),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x5,y5,z5),c,0,0),
             Vertex(Vector(x6,y6,z6),c,1,0),
             Vertex(Vector(x2,y2,z2),c,1,1),
             Vertex(Vector(x1,y1,z1),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x7,y7,z7),c,0,0),
             Vertex(Vector(x8,y8,z8),c,1,0),
             Vertex(Vector(x4,y4,z4),c,1,1),
             Vertex(Vector(x3,y3,z3),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x6,y6,z6),c,0,0),
             Vertex(Vector(x7,y7,z7),c,1,0),
             Vertex(Vector(x3,y3,z3),c,1,1),
             Vertex(Vector(x2,y2,z2),c,0,1),Texture_ID);

    Add_Quad(Vertex(Vector(x1,y1,z1),c,0,0),
             Vertex(Vector(x4,y4,z4),c,1,0),
             Vertex(Vector(x8,y8,z8),c,1,1),
             Vertex(Vector(x5,y5,z5),c,0,1),Texture_ID);

}

int Mesh::Add_Vertex(Vertex v)
{
    Mesh_Vertices.push_back(v);
    return Mesh_Vertices.size() - 1;
}

int Mesh::Add_Texture(int ID)
{
    Mesh_Textures.push_back(ID);
    return Mesh_Textures.size() - 1;
}

int Mesh::Add_Index(int ID)
{
    Mesh_Indices.push_back(ID);
    if (Primitive_Type == GL_TRIANGLES)
    {
        Face_Count = (int)(Mesh_Indices.size() / 3);
    }
    return Mesh_Indices.size() - 1;
}

int Mesh::Add_Normal(Vector v)
{
    Mesh_Normals.push_back(v);
    return Mesh_Normals.size() - 1;
}

Mesh::~Mesh()
{
    //dtor
}
