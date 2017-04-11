#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"
#include "Vector.h"

using namespace std;

class Mesh
{
    public:
        Mesh();
        virtual ~Mesh();

        vector<Vertex> Mesh_Vertices;
        vector<int> Mesh_Indices;
        vector<Vector> Mesh_Normals;
        vector<int> Mesh_Textures;

        int Add_Vertex(Vertex v);
        int Add_Index(int ID);
        int Add_Normal(Vector v);
        int Add_Texture(int ID);
        void Add_Quad(Vertex v1, Vertex v2, Vertex v3, Vertex v4, int Texture_ID);
        void Create_Cube(float size, Color c,int Texture_ID);
        void Create_Box(float size_x, float size_y, float size_z, Color c,int Texture_ID);

        unsigned int Primitive_Type;
        int Face_Count;

    protected:

    private:
};

#endif // MESH_H
