#ifndef NODE_H
#define NODE_H

#include "Sprite_Mesh.h"

#include "Vector.h"
#include "Mesh.h"
#include <vector>
#include "Texture_Manager.h"
#include "Bounding_Box.h"

class Node
{
    public:
        Node();
        virtual ~Node();

        Vector Position;
        Vector Rotation;
        Vector Scale;
        void Set_Position(Vector V);

        vector<Mesh> Attached_Meshes;
        vector<Vector> Attached_Mesh_Position;
        vector<Vector> Attached_Mesh_Rotation;
        vector<Vector> Attached_Mesh_Scaling;

        vector<Sprite_Mesh> Attached_Sprites;

        vector<Vector> Sprite_Position;
        vector<Vector> Sprite_Rotation;
        vector<Vector> Sprite_Scaling;

        void Add_Mesh(Mesh m, Vector Pos, Vector Rot, Vector Scl);
        void Add_Sprite(Sprite_Mesh m, Vector Pos, Vector Rot, Vector Scl);
        void Render(Texture_Manager& Tex_Man, float elapsed_time);

        void (*anim_end_callback) (int) = NULL;
        void Set_Sprite_Animation_End_Callback(void (*callback) (int));

        int Tag_ID;
        int Tag_Int_1;
        int Tag_Int_2;
        float Tag_Float_1;
        bool Enable_Texturing;
        bool Enable_Culling;
        bool Enable_Depth_Check;
        int Render_Level;

        int Collision_Shape = 0; //0 = Bounding Box
        Bounding_Box Collision_Box;
        bool Update_Bounding_Box = true;

    protected:

    private:
        int Mesh_Count;
        int Sprites_Count;
};

#endif // NODE_H
